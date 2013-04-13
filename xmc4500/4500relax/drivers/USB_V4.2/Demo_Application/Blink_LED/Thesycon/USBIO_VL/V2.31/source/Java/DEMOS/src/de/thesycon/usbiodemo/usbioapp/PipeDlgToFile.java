package de.thesycon.usbiodemo.usbioapp;

public class PipeDlgToFile extends PipeDialog {

	protected ReadToFilePage mReadToFilePage;
	protected UsbIoRd mUsbIoRd;

	public PipeDlgToFile(UsbIoApp Frame) {
		super(Frame);
		mUsbIoRd = new UsbIoRd(this);
		mPipe = mUsbIoRd;
		mReadToFilePage = new ReadToFilePage(this);
		PipeDlgTab.addTab(mReadToFilePage.getPageName(),null,mReadToFilePage,mReadToFilePage.getPageName());
	}

	public boolean start() {
		int BufferSize;
		if (mUsbIoRd.openFile(mReadToFilePage.mDestFileTF.getText())) {
			mReadToFilePage.mStartButton.setEnabled(false);
			startStatisticsTimer();
			mUsbIoRd.freeBuffers();
			BufferSize = (Integer.valueOf(mBufferPage.mSizeOfBufferTF.getText())).intValue();
			if ((mPipeInfo.PipeType & 3) == 1) {
				mIsoHeaderSize = 16 + Integer.parseInt(mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText()) * 12;
				BufferSize = (mIsoHeaderSize + Integer.parseInt(mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText()) * (mPipeInfo.MaximumPacketSize));
			}
			mUsbIoRd.allocateBuffers(BufferSize,(Integer.valueOf(mBufferPage.mNumberOfBuffersTF.getText())).intValue());
			mUsbIoRd.startThread(Integer.valueOf(mBufferPage.mMaxErrorCountTF.getText()).intValue());
		} else {
			mainFrame.printOutput("Unable to open file.\n");
		}
		return true;
	}

	public void stop() {
		mReadToFilePage.mStartButton.setEnabled(true);
		mUsbIoRd.shutdownThread();
		stopStatisticsTimer();
		updatePipeStatistics();
	}

	public void onThreadExit() {
		mReadToFilePage.mStartButton.setEnabled(true);
	}
}