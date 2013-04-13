package de.thesycon.usbiodemo.usbioapp;

public class PipeDlgFromFile extends PipeDialog {

	protected ReadFromFilePage mReadFromFilePage;
	protected UsbIoWr mUsbIoWr;

	public PipeDlgFromFile(UsbIoApp Frame) {
		super(Frame);
		mUsbIoWr = new UsbIoWr(this);
		mPipe = mUsbIoWr;
		mReadFromFilePage = new ReadFromFilePage(this);
		PipeDlgTab.addTab(mReadFromFilePage.getPageName(),null,mReadFromFilePage,mReadFromFilePage.getPageName());
	}

	public boolean start() {
		int BufferSize;
		if (mUsbIoWr.openFile(mReadFromFilePage.mDestFileTF.getText())) {
			mReadFromFilePage.mStartButton.setEnabled(false);
			startStatisticsTimer();
			mUsbIoWr.freeBuffers();
			BufferSize = (Integer.valueOf(mBufferPage.mSizeOfBufferTF.getText())).intValue();
			if ((mPipeInfo.PipeType & 3) == 1) {
				mIsoHeaderSize = 16 + Integer.parseInt(mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText()) * 12;
				BufferSize = (mIsoHeaderSize + Integer.parseInt(mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText()) * (mPipeInfo.MaximumPacketSize));
			}
			mUsbIoWr.allocateBuffers(BufferSize,(Integer.valueOf(mBufferPage.mNumberOfBuffersTF.getText())).intValue());
			mUsbIoWr.startThread(Integer.valueOf(mBufferPage.mMaxErrorCountTF.getText()).intValue());
		} else {
			mainFrame.printOutput("Unable to open file.\n");
		}
		return true;
	}

	public void stop() {
		mReadFromFilePage.mStartButton.setEnabled(true);
		mUsbIoWr.shutdownThread();
		stopStatisticsTimer();
		updatePipeStatistics();
	}

	public void onThreadExit() {
		mReadFromFilePage.mStartButton.setEnabled(true);
	}
}