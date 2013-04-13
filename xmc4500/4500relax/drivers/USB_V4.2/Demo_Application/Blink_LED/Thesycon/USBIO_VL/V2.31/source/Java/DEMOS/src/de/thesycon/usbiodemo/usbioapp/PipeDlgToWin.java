package de.thesycon.usbiodemo.usbioapp;

public class PipeDlgToWin extends PipeDialog {

	protected UsbIoDump mDump;
	protected ReadToWinPage mReadToWinPage;

	public PipeDlgToWin(UsbIoApp Frame) {
		super(Frame);
		mDump = new UsbIoDump(this);
		mPipe = mDump;
		mReadToWinPage = new ReadToWinPage(this);
		PipeDlgTab.addTab(mReadToWinPage.getPageName(),null,mReadToWinPage,mReadToWinPage.getPageName());
	}

	public boolean start() {
		int BufferSize;
		mReadToWinPage.mStartButton.setEnabled(false);
		startStatisticsTimer();
		mDump.freeBuffers();
		BufferSize = (Integer.valueOf(mBufferPage.mSizeOfBufferTF.getText())).intValue();
		if ((mPipeInfo.PipeType & 3) == 1) {
			mIsoHeaderSize = 16 + Integer.parseInt(mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText()) * 12;
			BufferSize = (mIsoHeaderSize + Integer.parseInt(mBufferPage.mNumberOfIsoPacketsPerBufferTF.getText()) * (mPipeInfo.MaximumPacketSize));
		}

		mDump.allocateBuffers(BufferSize,(Integer.valueOf(mBufferPage.mNumberOfBuffersTF.getText())).intValue());
		mDump.print = mReadToWinPage.mPrintToWindowCheck.isSelected();
		mDump.startThread(Integer.valueOf(mBufferPage.mMaxErrorCountTF.getText()).intValue());
		return true;
	}

	public void stop() {
		mReadToWinPage.mStartButton.setEnabled(true);
		mDump.shutdownThread();
		stopStatisticsTimer();
		updatePipeStatistics();
	}

	public void onThreadExit() {
		mReadToWinPage.mStartButton.setEnabled(true);
	}
}