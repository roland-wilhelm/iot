package de.thesycon.usbiodemo.usbioapp;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.TimerTask;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import de.thesycon.usbio.UsbIoPipe;
import de.thesycon.usbio.structs.USBIO_CONFIGURATION_INFO;
import de.thesycon.usbio.structs.USBIO_PIPE_CONFIGURATION_INFO;
import de.thesycon.usbio.structs.USBIO_PIPE_STATISTICS;

public abstract class PipeDialog extends JFrame {

	protected UsbIoApp mainFrame;

	protected int width = 350;
	protected int height = 350;

	protected UsbIoPipe mPipe;
	protected USBIO_PIPE_CONFIGURATION_INFO mPipeInfo;

	protected JTabbedPane PipeDlgTab;
	protected JButton mResetStatisticsButton;
	protected JButton mCloseButton;

	protected JPanel mPipeStatPanel;
	protected GridBagLayout mPipeStatPanelLayout;

	protected BufferPage mBufferPage;
	protected PipePage mPipePage;
	protected PipeStatisticsPanel mPipeStatisticsPanel;

	protected java.util.Timer StatisticsTimer;

	public abstract boolean start();
	public abstract void stop();
	public abstract void onThreadExit();

	public int mIsoHeaderSize;

	public PipeDialog(UsbIoApp Frame) {
		mainFrame = Frame;

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				close();
			}
		});

		mPipe = new UsbIoPipe();
		mPipeInfo = new USBIO_PIPE_CONFIGURATION_INFO();

		mBufferPage = new BufferPage(this);
		mPipePage = new PipePage(this);
		mPipeStatisticsPanel = new PipeStatisticsPanel();

		mResetStatisticsButton = new JButton("Reset Statistics");
		mResetStatisticsButton.addActionListener(new OnResetStatisticsButton());
		mCloseButton = new JButton("Close");
		mCloseButton.addActionListener(new OnCloseButton());

		mPipeStatPanelLayout = new GridBagLayout();
		mPipeStatPanel = new JPanel(mPipeStatPanelLayout,true);

		mPipeStatPanelLayout.setConstraints(mPipeStatisticsPanel, UsbIoApp.makegbc(0, 0, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		mPipeStatPanel.add(mPipeStatisticsPanel);

		mPipeStatPanelLayout.setConstraints(mResetStatisticsButton, UsbIoApp.makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipeStatPanel.add(mResetStatisticsButton);

		mPipeStatPanelLayout.setConstraints(mCloseButton, UsbIoApp.makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipeStatPanel.add(mCloseButton);

		PipeDlgTab = new JTabbedPane();
		PipeDlgTab.addTab(mPipePage.getPageName(),null,mPipePage,mPipePage.getPageName());
		PipeDlgTab.addTab(mBufferPage.getPageName(),null,mBufferPage,mBufferPage.getPageName());

		getContentPane().setLayout(new BorderLayout(2,1));
		getContentPane().add(PipeDlgTab,BorderLayout.CENTER);
		getContentPane().add(mPipeStatPanel,BorderLayout.SOUTH);
		Dimension scr= Toolkit.getDefaultToolkit().getScreenSize();
		this.setSize(width,height);
		this.setBounds((scr.width-width)/2,(scr.height-(height))/2,
                 width,height);
	}

	public int bindPipe(int DeviceNumber, int EndpointAddr) {
		USBIO_CONFIGURATION_INFO Info = new USBIO_CONFIGURATION_INFO();
		int err;

		err = mPipe.bind(DeviceNumber,(byte)EndpointAddr,mainFrame.gDevList,UsbIoApp.guid);
		if (err == 0) {
			// get Pipe Info
			err = mainFrame.gUsbIo.getConfigurationInfo(Info);
			if ( err != 0 ) {
			  // failed
			  // display error
			  mainFrame.printError("",err);
			  mPipe.unbind();
			} else {

			  // find pipe info
			  for (int i=0;i<Info.NbOfPipes;i++) {
				if (Info.PipeInfo[i].EndpointAddress == EndpointAddr) {
				  mPipeInfo = Info.PipeInfo[i]; // struct copy
				  break;
				}
			  }

			  //m_DlgPgBuffer.m_EditIsoPacketCount.EnableWindow(FALSE);

			  // pipe type
			  switch ( mPipeInfo.PipeType ) {
			  case 0:
				break;
			  case 1:
				  mBufferPage.mNumberOfIsoPacketsPerBufferTF.setEnabled(true);
				break;
			  case 2:
				break;
			  case 3:
				break;
			  default:
				mainFrame.printOutput("FATAL: unknown pipe type: 0x" + UsbIoApp.byteToString((byte)mPipeInfo.PipeType) + "\n");
				  mPipe.unbind();
						return 1;
					}

					// set default buffer parameters
					//SetBufferDefaults();
					mBufferPage.setDefaults();
					// load recent parameters from registry
					//LoadRecentSettings();
					//UpdateAllData(FALSE);

			  // set dialog titel
			  String txt;
				txt = "USBIOAPP - " + mainFrame.pipeTypeStr(mPipeInfo.PipeType) + " " + mainFrame.endpointDirectionStr((byte)EndpointAddr) + " Pipe 0x" + UsbIoApp.byteToString((byte)EndpointAddr);

			  this.setTitle(txt);
			  // set error prefix
			  //m_PipePrefix.Format("Pipe%02X", EndpointAddress);

					// update pipe params
					mPipePage.GetPipeParams();

					// update statistics display
					updatePipeStatistics();
			}
		}
		return err;
	}

	// update pipe statistics display
	void updatePipeStatistics()
	{
		if ( mPipe == null ) {
			return;
		}

		USBIO_PIPE_STATISTICS stats = new USBIO_PIPE_STATISTICS();
		int err = mPipe.queryPipeStatistics(stats,0);
		if ( err != 0 ) {
			// failed
			return;
		}
		mPipeStatisticsPanel.setStatistics(stats);

	}//UpdatePipeStatistics

	public void startStatisticsTimer() {
		StatisticsTimer = new java.util.Timer();
		mPipe.resetPipeStatistics();
		mPipe.setupPipeStatistics(1000);
		StatisticsTimer.schedule(new StatisticsTask(),0,500);
	}

	public void stopStatisticsTimer() {
		if (StatisticsTimer != null) {
			StatisticsTimer.cancel();
		}
		if ( mPipe != null ) {
			// disable average rate calculation
			mPipe.setupPipeStatistics(0);
		}
	}

	public class StatisticsTask extends TimerTask {
		public void run() {
			USBIO_PIPE_STATISTICS stat = new USBIO_PIPE_STATISTICS();
			mPipe.queryPipeStatistics(stat,0);
			mPipeStatisticsPanel.setStatistics(stat);
		}
	}

	public class OnResetStatisticsButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			if ( mPipe != null ) {
				// reset counters
				mPipe.resetPipeStatistics();
				updatePipeStatistics();
			}
		}
	}

	public class OnCloseButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			close();
		}
	}

	public void close() {
		stop();

		int err = mPipe.unbind();
		if (err != 0) {
			mainFrame.printError("Unbind: ",err);
		}
		mPipe.close();
		mPipe = null;
		dispose();
	}
}