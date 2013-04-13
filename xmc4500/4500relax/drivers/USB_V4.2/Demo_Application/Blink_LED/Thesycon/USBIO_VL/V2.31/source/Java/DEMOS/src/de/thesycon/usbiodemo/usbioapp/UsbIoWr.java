package de.thesycon.usbiodemo.usbioapp;
import java.io.FileInputStream;
import java.io.IOException;

import de.thesycon.usbio.UsbIoBuf;
import de.thesycon.usbio.UsbIoWriter;
import de.thesycon.usbio.structs.USBIO_ISO_PACKET;
import de.thesycon.usbio.structs.USBIO_ISO_TRANSFER;

public class UsbIoWr extends UsbIoWriter {

	protected PipeDialog mainFrame;
	public boolean print = true;
	protected FileInputStream file;

	int PrintPos = 0;


	public UsbIoWr(PipeDialog mainFrame) {
		super();
		this.mainFrame = mainFrame;
	}

	public boolean openFile(String Filename)
	{
		boolean succ = false;
		try {
			if ( file == null ) {
				file = new FileInputStream(Filename);
				if ( file != null ) {
					succ = true;
				}
			}
		}
		catch (IOException ex) {
			mainFrame.mainFrame.printOutput("Error open file\n");
		}
		return succ;
	}

	public void closeFile()
	{
		try {
			if ( file!=null ) {
				file.close();
				file = null;
			}
		}
		catch (IOException ex) {
			mainFrame.mainFrame.printOutput("Error close file\n");
		}
	}

	public void processBuffer(UsbIoBuf Buf) {
		Buf.NumberOfBytesToTransfer = Buf.Size;
		Buf.BytesTransferred = 0;
		Buf.OperationFinished = false;

		try {
			if (file != null) {
				if ((mainFrame.mPipeInfo.PipeType & 3) == 1) {
					// iso
					int IsoHeaderSize = mainFrame.mIsoHeaderSize;
					int NbOfPackets = Integer.parseInt(mainFrame.mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText());
					int IsoPacketSize = mainFrame.mPipeInfo.MaximumPacketSize;

					USBIO_ISO_TRANSFER iostrans = new USBIO_ISO_TRANSFER();

					iostrans.NumberOfPackets = NbOfPackets;
					iostrans.Flags= 0x30000;
					iostrans.StartFrame=0;
					iostrans.ErrorCount=0;
					System.arraycopy(iostrans.buildByteArray(),0,Buf.BufferMem,0,USBIO_ISO_TRANSFER.SIZE);
					USBIO_ISO_PACKET Packet = new USBIO_ISO_PACKET();
					int ofs = IsoHeaderSize;
					int pos = USBIO_ISO_TRANSFER.SIZE;

					for (int i=0;i<NbOfPackets;i++) {
						Packet.Offset = ofs;
						Packet.Length = IsoPacketSize;
						Packet.Status = 0;
						System.arraycopy(Packet.buildByteArray(),0,Buf.BufferMem,pos,USBIO_ISO_PACKET.SIZE);
						file.read(Buf.BufferMem, Packet.Offset, Packet.Length);
						pos += USBIO_ISO_PACKET.SIZE;
						ofs += IsoPacketSize;
					}
				} else {
					// bulk or interrupt ...
					file.read(Buf.BufferMem,0,Buf.Size);
					Buf.NumberOfBytesToTransfer = Buf.Size;
				}
			}
		}
		catch (IOException ex) {
			mainFrame.mainFrame.printOutput("Error read file\n");
		}
	}

	public void bufErrorHandler(UsbIoBuf Buf) {
		if ( Buf.Status != USBIO_ERR_SUCCESS ) {
			// print error
			// suppress CANCELED because it is caused by ABORT_PIPE
			if ( Buf.Status != USBIO_ERR_CANCELED ) {
				mainFrame.mainFrame.printError("Buf Error: ",Buf.Status);
			}
		}
	}

	// virtual function, called in the context of worker thread
	public void onThreadExit()
	{
		mainFrame.mainFrame.printOutput("Worker-thread terminated.\n");
		closeFile();
		// notify owning dialog, should be the last call
		mainFrame.onThreadExit();
	}
}