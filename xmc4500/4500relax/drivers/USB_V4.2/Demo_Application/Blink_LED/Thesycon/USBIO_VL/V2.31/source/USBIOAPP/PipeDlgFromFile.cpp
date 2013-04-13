
#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDlgFromFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CUsbIoWr::CUsbIoWr()
{
  m_PipeDialog = NULL;
  file = NULL;
  IsoRest = 0;
}

CUsbIoWr::~CUsbIoWr()
{
  CloseFile();
}


//
// derived special class from CUsbIoWriter
//

BOOL CUsbIoWr::OpenFile(const char *Filename)
{
  BOOL succ = FALSE;

  if ( file == NULL ) {
    file = fopen(Filename,"rb");
    if ( file != NULL ) {
      succ = TRUE;
    }
  }
  return succ;
}
  

void CUsbIoWr::CloseFile()
{
  if ( file!=NULL ) {
    fclose(file);
    file = NULL;
  }
}


void CUsbIoWr::BufErrorHandler(CUsbIoBuf *Buf)
{
  if ( Buf->Status != USBIO_ERR_SUCCESS ) {
    // print error
	  // suppress CANCELED because it is caused by ABORT_PIPE
		if ( Buf->Status != USBIO_ERR_CANCELED ) {
	    PrintError(Buf->Status, E_ERROR, m_PipeDialog->Prefix());
		}
  }
}


// overloaded process data function
void CUsbIoWr::ProcessBuffer(CUsbIoBuf *Buf)
{
  USBIO_ISO_TRANSFER_HEADER *Header;
  USBIO_ISO_PACKET *Packet;
  DWORD i;
  DWORD ofs;

  if (file) {

    if ((m_PipeDialog->m_PipeInfo.PipeType & 3) == 1) {
      // iso transfer
      // used for data sinks with adaptive synchronisation
      DWORD IsoHeaderSize = m_PipeDialog->m_IsoHeaderSize;
      DWORD NbOfPackets = m_PipeDialog->m_NumberOfIsoPackets;
      DWORD IsoPacketSize = m_PipeDialog->m_PipeInfo.MaximumPacketSize;
      DWORD SampleRate = m_PipeDialog->m_SampleRate;
      DWORD SampleSize = m_PipeDialog->m_SampleSize;
      DWORD BufferCount,BufferCountGot;
      UCHAR *buffer;

      Buf->NumberOfBytesToTransfer = IsoHeaderSize;
      // init the header
      Header=(USBIO_ISO_TRANSFER_HEADER *)Buf->Buffer();
      Header->IsoTransfer.NumberOfPackets = NbOfPackets;
      Header->IsoTransfer.Flags = USBIO_START_TRANSFER_ASAP;
      Header->IsoTransfer.StartFrame = 0;
      Header->IsoTransfer.ErrorCount = 0;
      // init a iso packet pointer
      Packet = Header->IsoPacket;
      ofs = IsoHeaderSize;
      buffer = (UCHAR*) Header;
      buffer += IsoHeaderSize;
      for (i=0;i<NbOfPackets;i++) {
        // calc the size of the Buffer
        // use the rest of last transfer
        IsoRest += SampleRate; // samples per second
        BufferCount = IsoRest / 1000;
        BufferCount *= SampleSize;
        // check Buffer Size
        if (BufferCount > IsoPacketSize) BufferCount=IsoPacketSize;
        // check file position
        // read the buffer from file
        BufferCountGot = fread(buffer, 1, BufferCount, file);
        if ( /*feof(file) ||*/ ( BufferCountGot == 0 ) ) {
          // the last read failed because eof
          if ( m_PipeDialog->m_AutoRepeat ) {
            // restart
            rewind(file);
            BufferCountGot = fread(buffer, 1, BufferCount, file);
          } else {
            // eof
            Header->IsoTransfer.NumberOfPackets = i;
            break;
          } 
        }     
        Packet->Offset = ofs;
        Packet->Length = BufferCountGot;
        Packet->Status = 0;

        Buf->NumberOfBytesToTransfer += BufferCountGot; 
        // claculate Iso rest for next buffer
        IsoRest -= BufferCountGot * 1000 / SampleSize;
        Packet++;
        // calculate new offset inside the buffer
        ofs += BufferCountGot; 
        // calculate new buffer pointer
        buffer += BufferCountGot;
      }
      if (Buf->NumberOfBytesToTransfer <= IsoHeaderSize ) {
        Buf->OperationFinished = true;
      } else {
        Buf->OperationFinished = false;
      }
      ASSERT(ofs<=Buf->Size());   
    } else {
      // bulk or interrupt ...
      if ( feof(file) ) {
        if ( m_PipeDialog->m_AutoRepeat ) {
          // restart
          rewind(file);
        } else {
          // eof
          Buf->NumberOfBytesToTransfer = 0;
          Buf->OperationFinished = true;
          return;
        }
      }
      Buf->NumberOfBytesToTransfer = fread(Buf->Buffer(), 1, Buf->Size(), file);
      Buf->OperationFinished = false;
    }   
  }
}


void CUsbIoWr::TerminateThread() {
  // fix a bug in open host controller driver
  // Abort pipe in iso transfer leads to a page fault
  if ((m_PipeDialog->m_PipeInfo.PipeType & 0x3) == 0x1) {
    // nothing
  } else {
    AbortPipe();
  }
}


// virtual function, called in the context of worker thread
void CUsbIoWr::OnThreadExit()
{
  PrintOut("Worker-thread terminated."NL);
  // close file
  CloseFile();
	IsoRest = 0;
  // notify owning dialog, should be the last call
  m_PipeDialog->OnThreadExit();
}



/////////////////////////////////////////////////////////////////////////////
// CPipeDlgFromFile dialog


CPipeDlgFromFile::CPipeDlgFromFile(CWnd* pParent /*=NULL*/)
  : CPipeDialog(pParent)
{
  
  // init members
  
  // set pointer in base class to our member
  m_Pipe = &m_Wr;
  m_Wr.m_PipeDialog = this;

  // create the window
  VERIFY( Create(IDD,pParent) );

}

CPipeDlgFromFile::~CPipeDlgFromFile()
{
}



BOOL CPipeDlgFromFile::OnInitDialog() 
{
  CPipeDialog::OnInitDialog();
  

  // create all dialog page instances
  VERIFY( m_DlgPgFromFile.Create(this,&m_TabControl) );
  // register our dialog page instances with the tab control
  m_TabControl.AddDialogPage(&m_DlgPgFromFile,IDS_PDIALOGPAGE_WRITEFROMFILE);
  m_TabControl.UpdatePageSelection();

	// define registry subkey where recent settings for this dialog will be stored
	m_DlgSubKey = "PipeDlgFromFile";

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}



BOOL CPipeDlgFromFile::OnStart()
{
  BOOLEAN succ;

  if ( !m_Running ) {

    if ( UpdateAllData(TRUE) ) {

      if (m_FileName.GetLength() == 0) {
        DisplayMessageBox("Invalid file name.");
      } else {
        succ = m_Wr.OpenFile(m_FileName);
        if ( !succ ) {
          DisplayMessageBox("Unable to open file '%s'.",(const char*)m_FileName);
        } else {    
        
          m_Wr.FreeBuffers();
          if ((m_PipeInfo.PipeType & 3) == 1) {
            // iso
            m_IsoHeaderSize = sizeof(USBIO_ISO_TRANSFER) + m_NumberOfIsoPackets*sizeof(USBIO_ISO_PACKET);
            m_SizeOfBuffer = m_IsoHeaderSize + m_NumberOfIsoPackets*m_PipeInfo.MaximumPacketSize;
         } 
          succ = m_Wr.AllocateBuffers(m_SizeOfBuffer, m_NumberOfBuffers);
          if (succ) {
            succ = m_Wr.StartThread(m_MaxErrorCount);
            if (!succ) {
              PrintOut("Cannot start thread."NL);
            } else {
              // success
              m_Running = TRUE;
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


void CPipeDlgFromFile::OnStop()
{
  // shutdown thread, wait until it is terminated
  if ( !m_Wr.ShutdownThread() ) {
    PrintOut("Cannot shutdown thread."NL);
  }
}


// handler for WM_USER_THREAD_TERMINATED, called in the context of main thread
void CPipeDlgFromFile::OnThreadExitMessage()
{
  // call the dialog page to enable the buttons
  m_DlgPgFromFile.EnableStartButton();

}


