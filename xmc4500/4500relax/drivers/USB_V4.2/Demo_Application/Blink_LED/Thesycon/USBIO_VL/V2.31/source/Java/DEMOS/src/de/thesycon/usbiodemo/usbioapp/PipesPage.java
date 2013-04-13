package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.event.AncestorEvent;
import javax.swing.event.AncestorListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import de.thesycon.usbio.structs.USBIO_CONFIGURATION_INFO;

public class PipesPage extends PanelPage {

	public String getPageName() { return "Pipes"; };

	protected UsbIoApp mainFrame;

	protected Vector eplist;

	protected int mEndpointAddr;


	protected JButton mGetConfigurationInfoButton;
	protected JButton mReadToOutputWindowButton;
	protected JButton mReadToFileButton;
	protected JButton mReadFromFileButton;

	protected JLabel mConfigurationLabel;
	protected JLabel mActiveEndpointsLabel;
	protected JLabel mOpenPipeLabel;
	protected JList mEndpointList;

	protected JPanel mPipePanel;

	protected GridBagLayout mPipePanelLayout;


	public PipesPage(UsbIoApp Frame) {
		mainFrame = Frame;
		this.addAncestorListener(new ShowListener());
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mGetConfigurationInfoButton);
		ret.addElement(mReadToOutputWindowButton);
		ret.addElement(mReadToFileButton);
		ret.addElement(mReadFromFileButton);
		ret.addElement(mEndpointList);
		return ret;
	}

	public class ShowListener implements AncestorListener {
		public void ancestorAdded(AncestorEvent ev) {
			updateEndpointList();
			updateEndpointSelection();
		}
		public void ancestorRemoved(AncestorEvent ev) {
			updateEndpointList();
			updateEndpointSelection();
		}
		public void ancestorMoved(AncestorEvent ev) {
			updateEndpointList();
			updateEndpointSelection();
		}
	}

	public void initGUIelements() {
		mPipePanelLayout = new GridBagLayout();
		mPipePanel = new JPanel(mPipePanelLayout,true);
		mPipePanel.setBorder(BorderFactory.createTitledBorder("Pipes"));

		mGetConfigurationInfoButton = new JButton("Get Configuration Info");
		mGetConfigurationInfoButton.addActionListener(new OnGetConfigurationInfoButton());
		mReadToOutputWindowButton = new JButton("Read from Pipe and Write to Output Window");
		mReadToOutputWindowButton.addActionListener(new OnToWindow());
		mReadToFileButton = new JButton("Read from Pipe and Write to File");
		mReadToFileButton.addActionListener(new OnToFile());
		mReadFromFileButton = new JButton("Read from File and Write to Pipe");
		mReadFromFileButton.addActionListener(new OnFromFile());

		mConfigurationLabel = new JLabel("");
		mActiveEndpointsLabel = new JLabel("Active Endpoints:");
		mOpenPipeLabel = new JLabel("OpenPipe:");
		mEndpointList = new JList();
		mEndpointList.addListSelectionListener(new ListSelListener());

		mPipePanelLayout.setConstraints(mActiveEndpointsLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipePanel.add(mActiveEndpointsLabel);

		mPipePanelLayout.setConstraints(mOpenPipeLabel, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipePanel.add(mOpenPipeLabel);

		mEndpointList.setFixedCellWidth(1);
		JScrollPane mEndpointListScrollPane = new JScrollPane(mEndpointList);
		mPipePanelLayout.setConstraints(mEndpointListScrollPane, makegbc(0, 1, 1, 3,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		mPipePanel.add(mEndpointListScrollPane);

		mPipePanelLayout.setConstraints(mReadToOutputWindowButton, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipePanel.add(mReadToOutputWindowButton);

		mPipePanelLayout.setConstraints(mReadToFileButton, makegbc(1, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipePanel.add(mReadToFileButton);

		mPipePanelLayout.setConstraints(mReadFromFileButton, makegbc(1, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipePanel.add(mReadFromFileButton);

		layout.setConstraints(mGetConfigurationInfoButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mGetConfigurationInfoButton);

		layout.setConstraints(mConfigurationLabel, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mConfigurationLabel);

		layout.setConstraints(mPipePanel, makegbc(0, 1, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mPipePanel);
	}

	public class ListSelListener implements ListSelectionListener {
		public void valueChanged(ListSelectionEvent e) {
			updateEndpointSelection();
		}
	}

	void
	dumpConfigInfo(
	USBIO_CONFIGURATION_INFO Info
	)
	{
		int i;

		mainFrame.printOutput("\n");
		mainFrame.printOutput("Configuration Information:\n\n");
		mainFrame.printOutput("NbOfInterfaces        :   " + Info.NbOfInterfaces + "\n\n");
		for (i=0;i<Info.NbOfInterfaces;i++) {
			mainFrame.printOutput("Interface " + i +" Information:   \n");
			mainFrame.printOutput("InterfaceNumber     :   " + Info.InterfaceInfo[i].InterfaceNumber + "\n");
			mainFrame.printOutput("AlternateSetting    :   " + Info.InterfaceInfo[i].AlternateSetting + "\n");
			mainFrame.printOutput("Class               :   " + Info.InterfaceInfo[i]._Class + "\n");
			mainFrame.printOutput("SubClass            :   " + Info.InterfaceInfo[i].SubClass + "\n");
			mainFrame.printOutput("Protocol            :   " + Info.InterfaceInfo[i].Protocol + "\n");
			mainFrame.printOutput("NumberOfPipes       :   " + Info.InterfaceInfo[i].NumberOfPipes + "\n");
		}
		mainFrame.printOutput("\n\nNbOfPipes           :   " + Info.NbOfPipes + "\n");
		for (i=0;i<Info.NbOfPipes;i++) {
			mainFrame.printOutput("\nPipe " + i + " Information:   " + "\n");
			mainFrame.printOutput("MaximumPacketSize   :   " + Info.PipeInfo[i].MaximumPacketSize + "\n");
			mainFrame.printOutput("EndpointAddress     : 0x" + UsbIoApp.byteToString(Info.PipeInfo[i].EndpointAddress) + "\n");
			mainFrame.printOutput("Interval            :   " + Info.PipeInfo[i].Interval + "\n");
			mainFrame.printOutput("MaximumTransferSize :   " + Info.PipeInfo[i].MaximumTransferSize + "\n");
			mainFrame.printOutput("PipeType            : 0x" + UsbIoApp.byteToString((byte)Info.PipeInfo[i].PipeType) + "\n");
			mainFrame.printOutput("InterfaceNumber     : 0x" + UsbIoApp.byteToString(Info.PipeInfo[i].InterfaceNumber) + "\n");
		}

	}

	void updateEndpointList()
	{
		String str;

		// clear endpoint list
		mConfigurationLabel.setText("Device is not configured");
		mEndpointList.setListData(new Vector());
		eplist = new Vector();


		// get info on current configuration from driver
		USBIO_CONFIGURATION_INFO Info = new USBIO_CONFIGURATION_INFO();
		int err = mainFrame.gUsbIo.getConfigurationInfo(Info);
		if ( err == 0 ) {
			Vector list = new Vector();
			// fill list box with active endpoints
			for ( int i=0; i<Info.NbOfPipes; i++ ) {
				byte ep = Info.PipeInfo[i].EndpointAddress;
				int type = Info.PipeInfo[i].PipeType;
				str = "0x" + UsbIoApp.byteToString(ep) + "  " + mainFrame.pipeTypeStr(type) + " " + mainFrame.endpointDirectionStr(ep);
				list.add(str);
				eplist.add(new Byte(ep));
			}
			mEndpointList.setListData(list);
			if ( Info.NbOfPipes > 0 ) {
				// there are active pipes, the device is configured
				mConfigurationLabel.setText("");
				// select first endpoint
				mEndpointList.setSelectedIndex(0);
			}
		}
	}

	void updateEndpointSelection()
	{
		// no selection
		mEndpointAddr = -1;
		// disable all buttons
		mReadToOutputWindowButton.setEnabled(false);
		mReadToFileButton.setEnabled(false);
		mReadFromFileButton.setEnabled(false);

		int index = mEndpointList.getSelectedIndex();
		if ( index >= 0 ) {
			mEndpointAddr = ((Byte)(eplist.elementAt(index))).intValue();
			if ( (mEndpointAddr & 0x80) != 0 ) {
				// IN endpoint
				mReadToOutputWindowButton.setEnabled(true);
				mReadToFileButton.setEnabled(true);
			} else {
				// OUT endpoint
				mReadFromFileButton.setEnabled(true);
			}
		} else {
			// no selection
		}
	}

	void openPipe(int Purpose)
	{
		int err;

		PipeDialog dlg = null;

		switch ( Purpose ) {
		case 0:
			dlg = new PipeDlgToWin(mainFrame);
		break;
		case 1:
			dlg = new PipeDlgToFile(mainFrame);//PipeDlgToFile(mainFrame);
		break;
		case 2:
			dlg = new PipeDlgFromFile(mainFrame);//PipeDlgFromFile(mainFrame);
		break;
		default:
		break;
		}

		if ( dlg != null ) {
			// bind the pipe
			err = dlg.bindPipe(mainFrame.gDeviceNumber,mEndpointAddr);
			if ( err != 0 ) {
				// bind failed, destroy the window
				//dlg->DestroyWindow();
				dlg.dispose();
				// display error
				mainFrame.printError("Bind Pipe: ",err);
			} else {
				// add dialog to list
				//g_PipeDialogList.AddTail(dlg);
				// show the new dialog on screen
				dlg.setVisible(true);
			}
		}
	}

	public class OnToWindow implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			openPipe(0);
		}
	}

	public class OnToFile implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			openPipe(1);
		}
	}

	public class OnFromFile implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			openPipe(2);
		}
	}

	public class OnGetConfigurationInfoButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			USBIO_CONFIGURATION_INFO Info = new USBIO_CONFIGURATION_INFO();

			// send the command to the driver
			err= mainFrame.gUsbIo.getConfigurationInfo(Info);
			if (err != 0) {
				mainFrame.printError("",err);
			} else {
				if ( Info.NbOfInterfaces==0 ) {
					// device is not configured
					mainFrame.printOutput("The device is not configured.\n");
					mainFrame.printOutput("Use the button Set Configuration on the Configuration page first.\n");
				} else {
					// display the information
					dumpConfigInfo(Info);

				}
			}
		}
	}
}