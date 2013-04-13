
#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDlgToFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CUsbIoRd::CUsbIoRd() {
  m_PipeDialog=NULL;
  file=NULL;
}

CUsbIoRd::~CUsbIoRd() {
  CloseFile();
}


//
// derived special class from CUsbIoReader
//

BOOL CUsbIoRd::OpenFile(const char *Filename)
{
  BOOL succ = FALSE;

  if ( file == NULL ) {
    file = fopen(Filename,"wb");
    if ( file != NULL ) {
      succ = TRUE;
    }
  }
  return succ;
}
  

void CUsbIoRd::CloseFile()
{
  if ( file!=NULL ) { 
    fclose(file);
    file = NULL;
  }
}




void CUsbIoRd::BufErrorHandler(CUsbIoBuf *Buf)
{
  if ( Buf->Status != USBIO_ERR_SUCCESS ) {
    // print error
	  // suppress CANCELED because it is caused by ABORT_PIPE
		if ( Buf->Status != USBIO_ERR_CANCELED ) {
	    PrintError(Buf->Status, E_ERROR, m_PipeDialog->Prefix());
		}
  }
}


// overloaded process buffer function
void CUsbIoRd::ProcessBuffer(CUsbIoBuf *Buf)
{
  USBIO_ISO_TRANSFER_HEADER *Header;
  USBIO_ISO_PACKET *Packet;
  DWORD i;
  DWORD ofs;

  FillMemory(Buf->Buffer(),Buf->Size(),0x00);
  Buf->NumberOfBytesToTransfer=Buf->Size();
  Buf->BytesTransferred=0;
  Buf->OperationFinished = false;

  if ((m_PipeDialog->m_PipeInfo.PipeType & 3) == 1) {
    // iso transfer
    // used for Asynchronous data sources
    DWORD IsoHeaderSize = m_PipeDialog->m_IsoHeaderSize;
    DWORD NbOfPackets = m_PipeDialog->m_NumberOfIsoPackets;
    DWORD IsoPacketSize = m_PipeDialog->m_PipeInfo.MaximumPacketSize;
    // the first part of the buffer is a special header
    Header=(USBIO_ISO_TRANSFER_HEADER *)Buf->Buffer();
    // fill in the header
    Header->IsoTransfer.NumberOfPackets=NbOfPackets;
    Header->IsoTransfer.Flags=
        USBIO_SHORT_TRANSFER_OK  |
        USBIO_START_TRANSFER_ASAP;
    Header->IsoTransfer.StartFrame=0;
    Header->IsoTransfer.ErrorCount=0;
    // get the pointer to the iso packets
    Packet = Header->IsoPacket;
    ofs = IsoHeaderSize;
    // fill in the offsets and the length for all buffer pices
    for (i=0;i<NbOfPackets;i++) {
      Packet->Offset = ofs;
      Packet->Length = IsoPacketSize;
      Packet->Status = 0;
      Packet++;
      ofs += IsoPacketSize;
    }
    ASSERT(ofs<=Buf->Size());   
  } else {
    // bulk or interrupt ...
    // buffer is set to zero
  }
}

// overloaded process data function
void CUsbIoRd::ProcessData(CUsbIoBuf *Buf)
{
  DWORD nb;
  USBIO_ISO_TRANSFER_HEADER *Header;
  USBIO_ISO_PACKET *Packet;
  DWORD i;
  UCHAR *ptr;

  if ( Buf->Status != USBIO_ERR_SUCCESS ) {
    return;
  }

  if ((m_PipeDialog->m_PipeInfo.PipeType & 3 ) == 1) {
    // iso transfer
    // get the header back
    Header=(USBIO_ISO_TRANSFER_HEADER *)Buf->Buffer();
    ptr=(UCHAR*)Buf->Buffer();
    Packet = Header->IsoPacket;
    // for all packets
    for (i=0;i<Header->IsoTransfer.NumberOfPackets;i++) {
      if ( Packet->Status==USBIO_ERR_SUCCESS ) {
        // write the data pieces to file
        nb = fwrite(ptr+Packet->Offset, 1, Packet->Length, file);
        if ( nb != Packet->Length ) {
          // error
          PrintOut("Error during write file."NL);
        }
      } else {
        // print error
        PrintError(Packet->Status,E_ERROR,"Packet Error");
      }
      Packet++;
    }   

  } else {

    // bulk or interrupt ...
    if ( Buf->Status == USBIO_ERR_SUCCESS ) {
      if (  Buf->BytesTransferred ) {
        if (file) {
          nb = fwrite(Buf->Buffer(), 1, Buf->BytesTransferred, file);
          if ( nb != Buf->BytesTransferred ) {
            // error
            PrintOut("Error during write file"NL);
          }
        }
      } else {
        // 0 packet
      }
    }
  }
}

void CUsbIoRd::TerminateThread() {
  // fix a bug in open host controller driver
  // Abort pipe in iso transfer leads to a page fault
  if ((m_PipeDialog->m_PipeInfo.PipeType & 3) == 1) {
    // nothing
  } else {
    AbortPipe();
  }
}


// virtual function, called in the context of worker thread
void CUsbIoRd::OnThreadExit()
{
  PrintOut("Worker-thread terminated."NL);
  CloseFile();
  // notify owning dialog, should be the last call
  m_PipeDialog->OnThreadExit();
}


/////////////////////////////////////////////////////////////////////////////
// CPipeDlgToFile dialog


CPipeDlgToFile::CPipeDlgToFile(CWnd* pParent /*=NULL*/)
  : CPipeDialog(pParent)
{
  
  // init members
  
  // set pointer in base class to our member
  m_Pipe = &m_Rd;
  m_Rd.m_PipeDialog=this;


  // create the window
  VERIFY( Create(IDD,pParent) );

}

CPipeDlgToFile::~CPipeDlgToFile()
{
}



BOOL CPipeDlgToFile::OnInitDialog() 
{
  CPipeDialog::OnInitDialog();
  

  // create all dialog page instances
  VERIFY( m_DlgPgToFile.Create(this,&m_TabControl) );
  // register our dialog page instances with the tab control
  m_TabControl.AddDialogPage(&m_DlgPgToFile,IDS_PDIALOGPAGE_READTOFILE);
  m_TabControl.UpdatePageSelection();

	// define registry subkey where recent settings for this dialog will be stored
	m_DlgSubKey = "PipeDlgToFile";
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}



BOOL CPipeDlgToFile::OnStart()
{
  BOOLEAN succ;

  if ( !m_Running ) {

    if ( UpdateAllData(TRUE) ) {

      if (m_FileName.GetLength() == 0) {
        DisplayMessageBox("Invalid file name.");
      } else {
        succ = m_Rd.OpenFile(m_FileName);
        if ( !succ ) {
          DisplayMessageBox("Unable to open file '%s'.",(const char*)m_FileName);
        } else {    
          m_Rd.FreeBuffers();
          if ((m_PipeInfo.PipeType & 3) == 1) {
            // iso
            m_IsoHeaderSize = sizeof(USBIO_ISO_TRANSFER) + m_NumberOfIsoPackets*sizeof(USBIO_ISO_PACKET);
            m_SizeOfBuffer = m_IsoHeaderSize + m_NumberOfIsoPackets*m_PipeInfo.MaximumPacketSize;
          } 
          succ = m_Rd.AllocateBuffers(m_SizeOfBuffer, m_NumberOfBuffers);

          if (succ) {
            succ = m_Rd.StartThread(m_MaxErrorCount);
            if (!succ) {
              PrintOut("Cannot start thread."NL);
            } else {
              // success
              m_Running = TRUE;
              UpdateAllData(FALSE);
            }
          } else {
            PrintOut("Cannot allocate buffers."NL);
          }
        }
      }
    } 
  }
  return m_Running;
}


void CPipeDlgToFile::OnStop()
{
  // shutdown thread, wait until it is terminated
  if ( !m_Rd.ShutdownThread() ) {
    PrintOut("Cannot shutdown thread."NL);
  }
}


// handler for WM_USER_THREAD_TERMINATED, called in the context of main thread
void CPipeDlgToFile::OnThreadExitMessage()
{
  m_DlgPgToFile.EnableStartButton();
}


