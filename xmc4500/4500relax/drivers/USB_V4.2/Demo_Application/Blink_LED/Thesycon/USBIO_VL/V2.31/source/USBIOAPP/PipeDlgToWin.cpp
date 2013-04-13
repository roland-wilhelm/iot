
#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDlgToWin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//
// derived special class from CUsbIoReader
//

CUsbIoDump::CUsbIoDump()
{
  m_PipeDialog=NULL;
  m_PrintPos=0;
}


CUsbIoDump::~CUsbIoDump()
{
}


void
CUsbIoDump::Init(CPipeDlgToWin *ptr, HWND Hwnd)
{
  m_PipeDialog=ptr;
  m_hwnd=Hwnd;
}


// virtual function, called in the context of worker thread
void CUsbIoDump::OnThreadExit()
{
  PrintOut("Worker-thread terminated."NL);
  // notify owning dialog, should be the last call
  m_PipeDialog->OnThreadExit();
}


void CUsbIoDump::BufErrorHandler(CUsbIoBuf *Buf)
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
void CUsbIoDump::ProcessBuffer(CUsbIoBuf *Buf)
{
  USBIO_ISO_TRANSFER_HEADER *Header;
  USBIO_ISO_PACKET *Packet;
  DWORD ofs;
  DWORD i;

  ZeroMemory(Buf->Buffer(),Buf->Size());
  Buf->NumberOfBytesToTransfer=Buf->Size();
  Buf->BytesTransferred=0;
  Buf->OperationFinished = false;

  if ((m_PipeDialog->m_PipeInfo.PipeType & 3) == 1) {
    // iso
    DWORD IsoHeaderSize = m_PipeDialog->m_IsoHeaderSize;
    DWORD NbOfPackets = m_PipeDialog->m_NumberOfIsoPackets;
    DWORD IsoPacketSize = m_PipeDialog->m_PipeInfo.MaximumPacketSize;
    Header=(USBIO_ISO_TRANSFER_HEADER *)Buf->Buffer();
    Header->IsoTransfer.NumberOfPackets=NbOfPackets;
    Header->IsoTransfer.Flags=
        USBIO_SHORT_TRANSFER_OK  |
        USBIO_START_TRANSFER_ASAP;
    Header->IsoTransfer.StartFrame=0;
    Header->IsoTransfer.ErrorCount=0;
    Packet = Header->IsoPacket;
    ofs = IsoHeaderSize;
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

  }
}

// overloaded process data function
void CUsbIoDump::ProcessData(CUsbIoBuf *Buf)
{
  USBIO_ISO_TRANSFER_HEADER *Header;
  USBIO_ISO_PACKET *Packet;
  DWORD i;
  UCHAR *ptr;


  if ( m_PipeDialog->m_EnablePrint ) {
    if ((m_PipeDialog->m_PipeInfo.PipeType & 3 ) == 1) {
      // iso
      if (Buf->Status == USBIO_ERR_SUCCESS ) {
        PrintOut("*");
        m_PrintPos++;
        if (m_PrintPos >= 32) {
          PrintOut(NL);
          m_PrintPos=0;
        }
      }
      Header=(USBIO_ISO_TRANSFER_HEADER *)Buf->Buffer();
      ptr=(UCHAR*)Buf->Buffer();
      Packet = Header->IsoPacket;
      for (i=0;i<Header->IsoTransfer.NumberOfPackets;i++) {
        if (Packet->Status != USBIO_ERR_SUCCESS) {
          PrintError(Packet->Status);
        } else {
          // DumpHex(ptr+Packet->Offset, Packet->Length);
        }
        Packet++;
      }   
    } else {
      // bulk or interrupt ...  
      if ( Buf->Status == USBIO_ERR_SUCCESS ) {
        PrintOut("%s: %d bytes transferred:"NL, m_PipeDialog->Prefix(), Buf->BytesTransferred);
				if ( Buf->BytesTransferred > 64 ) {
	        DumpHex(Buf->Buffer(), 64);
	        PrintOut("..."NL"The dump is truncated to 64 bytes!"NL);
				}
				else {
	        DumpHex(Buf->Buffer(), Buf->BytesTransferred);
				}
      }
    }
  } 
}



/////////////////////////////////////////////////////////////////////////////
// CPipeDlgToWin dialog


CPipeDlgToWin::CPipeDlgToWin(CWnd* pParent /*=NULL*/)
  : CPipeDialog(pParent)
{
  
  // init members
  
  // set pointer in base class to our member
  m_Dump.Init(this, m_hWnd);
  m_Pipe = &m_Dump;


  // create the window
  VERIFY( Create(IDD,pParent) );

}

CPipeDlgToWin::~CPipeDlgToWin()
{
}



BOOL CPipeDlgToWin::OnInitDialog() 
{
  CPipeDialog::OnInitDialog();
  

  // create all dialog page instances
  VERIFY( m_DlgPgToWin.Create(this,&m_TabControl) );
  // register our dialog page instances with the tab control
  m_TabControl.AddDialogPage(&m_DlgPgToWin,IDS_PDIALOGPAGE_READTOWIN);
  m_TabControl.UpdatePageSelection();

	// define registry subkey where recent settings for this dialog will be stored
	m_DlgSubKey = "PipeDlgToWin";
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}



BOOL CPipeDlgToWin::OnStart()
{
  BOOLEAN succ;

  if ( !m_Running ) {

    if ( UpdateAllData(TRUE) ) {
      
      m_Dump.FreeBuffers();
      if ((m_PipeInfo.PipeType & 3) == 1) {
        // iso
        m_IsoHeaderSize = sizeof(USBIO_ISO_TRANSFER) + m_NumberOfIsoPackets*sizeof(USBIO_ISO_PACKET);
        m_SizeOfBuffer = m_IsoHeaderSize + m_NumberOfIsoPackets*m_PipeInfo.MaximumPacketSize;
      } 
      succ = m_Dump.AllocateBuffers(m_SizeOfBuffer, m_NumberOfBuffers);
      if (succ) {
        succ = m_Dump.StartThread(m_MaxErrorCount);
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

  return m_Running;
}


void CPipeDlgToWin::OnStop()
{
  // shutdown thread, wait until it is terminated
  if ( !m_Dump.ShutdownThread() ) {
    PrintOut("Cannot shutdown thread."NL);
  }
}


// handler for WM_USER_THREAD_TERMINATED, called in the context of main thread
void CPipeDlgToWin::OnThreadExitMessage()
{
  m_DlgPgToWin.EnableStartButton();
}

