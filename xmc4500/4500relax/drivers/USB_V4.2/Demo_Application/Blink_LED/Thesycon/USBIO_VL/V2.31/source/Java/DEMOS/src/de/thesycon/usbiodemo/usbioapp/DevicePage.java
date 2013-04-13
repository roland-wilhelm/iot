package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

import de.thesycon.usbio.UsbIo;
import de.thesycon.usbio.UsbIoInterface;
import de.thesycon.usbio.structs.USBIO_DEVICE_PARAMETERS;
import de.thesycon.usbio.structs.USBIO_DRIVER_INFO;
import de.thesycon.usbio.structs.USB_DEVICE_DESCRIPTOR;

public class DevicePage extends PanelPage {

	public String getPageName() { return "Device"; };

	protected Vector DevList;
	protected Vector DevListNumber;

	protected UsbIoApp mainFrame;

	protected JButton mScanButton;
	protected JButton mOpenButton;
	protected JButton mCloseButton;
	protected JButton mAcquireButton;
	protected JButton mReleaseButton;
	protected JList mDeviceList;

	protected JLabel mDriverVersionInfo;

	protected JCheckBox mResetOnClose;
	protected JCheckBox mEnableWakeup;
	protected JCheckBox mUnconfigureOnClose;
	protected JLabel mRequestTimeoutLabel;
	protected JTextField mRequestTimeoutTF;
	protected JButton mGetDeviceParametersButton;
	protected JButton mSetDeviceParametersButton;

	protected JPanel mAvailableDevices;
	protected JPanel mDeviceParameters;
	protected JPanel mCurrentVersion;
	protected GridBagLayout mAvailableDevicesLayout;
	protected GridBagLayout mDeviceParametersLayout;
	protected GridBagLayout mCurrentVersionLayout;

	public DevicePage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mCloseButton);
		ret.addElement(mResetOnClose);
		ret.addElement(mEnableWakeup);
		ret.addElement(mUnconfigureOnClose);
		ret.addElement(mGetDeviceParametersButton);
		ret.addElement(mSetDeviceParametersButton);
		ret.addElement(mRequestTimeoutTF);
		return ret;
	}

	public void updateDeviceList(boolean PrintInfo) {
		int Status;
		USB_DEVICE_DESCRIPTOR Desc;

		DevList = new Vector();
		DevListNumber = new Vector();

		UsbIo.destroyDeviceList(mainFrame.gDevList);
		mainFrame.gDevList = UsbIo.createDeviceList(UsbIoApp.guid);
		if (PrintInfo) {
			mainFrame.printOutput("\nScanning for attached USB devices:\n\n");
		}
		for (int i = 0; i < 128; i++) {
			Status = mainFrame.gUsbIo.open(i, mainFrame.gDevList, UsbIoApp.guid);
			if (Status == 0) {
				DevListNumber.add(Integer.toString(i));
				if (PrintInfo) {
					mainFrame.printOutput("USBIO Device" + i + ": ");
					Desc = new USB_DEVICE_DESCRIPTOR();
					mainFrame.gUsbIo.getDeviceDescriptor(Desc);
					mainFrame.printOutput("VendorID:0x" + UsbIoApp.shortToString((short)Desc.idVendor) + "  ProductID:0x" + UsbIoApp.shortToString((short)Desc.idProduct) + "\n");
					DevList.add("Device" + i + " VID:0x" + UsbIoApp.shortToString((short)Desc.idVendor) + " PID:0x" + UsbIoApp.shortToString((short)Desc.idProduct));
				} else {
					DevList.add("Device" + i);
				}
			}
			mainFrame.gUsbIo.close();
		}
		mDeviceList.setListData(DevList);
		if (DevList.size() == 0) {
			mainFrame.printOutput("There are no USB devices attached to the USBIO driver.\n");
			if ( !mainFrame.gUsbIo.isOpen() ) {
				mOpenButton.setEnabled(false);
				mCloseButton.setEnabled(false);
				mAcquireButton.setEnabled(false);
				mReleaseButton.setEnabled(false);
			}
		} else {
			if ( !mainFrame.gUsbIo.isOpen() ) {
				mOpenButton.setEnabled(true);
				mCloseButton.setEnabled(false);
				mAcquireButton.setEnabled(false);
				mReleaseButton.setEnabled(false);
			}
			mDeviceList.setSelectedIndex(0);
		}

	}

	public void initGUIelements() {
		mScanButton = new JButton("Scan for USBIO devices");
		mScanButton.addActionListener(new OnScanButton());
		mOpenButton = new JButton("Open");
		mOpenButton.addActionListener(new OnOpenButton());
		mCloseButton = new JButton("Close");
		mCloseButton.addActionListener(new OnCloseButton());
		mAcquireButton = new JButton("Acquire");
		mAcquireButton.addActionListener(new OnAcquireButton());
		mReleaseButton = new JButton("Release");
		mReleaseButton.addActionListener(new OnReleaseButton());

		mDeviceList = new JList();

		mDriverVersionInfo = new JLabel(" ");

		mResetOnClose = new JCheckBox("ResetOnClose");
		mEnableWakeup = new JCheckBox("Enable Remote Wackeup");
		mUnconfigureOnClose = new JCheckBox("Unconfigure on close");
		mRequestTimeoutLabel = new JLabel("Request Timeout:");
		mRequestTimeoutTF = new JTextField(8);
		mGetDeviceParametersButton = new JButton("Get");
		mGetDeviceParametersButton.addActionListener(new OnGetDeviceParameters());
		mSetDeviceParametersButton = new JButton("Set");
		mSetDeviceParametersButton.addActionListener(new OnSetDeviceParameters());

		mOpenButton.setEnabled(false);
		mCloseButton.setEnabled(false);
		mAcquireButton.setEnabled(false);
		mReleaseButton.setEnabled(false);

		mAvailableDevicesLayout = new GridBagLayout();
		mDeviceParametersLayout = new GridBagLayout();
		mCurrentVersionLayout = new GridBagLayout();

		mAvailableDevices = new JPanel(mAvailableDevicesLayout,true);
		mAvailableDevices.setBorder(BorderFactory.createTitledBorder("Available Devices"));
		mDeviceParameters = new JPanel(mDeviceParametersLayout,true);
		mDeviceParameters.setBorder(BorderFactory.createTitledBorder("Device Parameters"));
		mCurrentVersion = new JPanel(mCurrentVersionLayout,true);
		mCurrentVersion.setBorder(BorderFactory.createTitledBorder("Current Version"));


		mAvailableDevicesLayout.setConstraints(mScanButton, makegbc(0, 0, 4, 1,100,0,GridBagConstraints.HORIZONTAL,GridBagConstraints.WEST));
		mAvailableDevices.add(mScanButton);

		mDeviceList.setFixedCellWidth(1);
		JScrollPane mDeviceListScrollPane = new JScrollPane(mDeviceList);
		mAvailableDevicesLayout.setConstraints(mDeviceListScrollPane, makegbc(0, 1, 4, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		mAvailableDevices.add(mDeviceListScrollPane);

		mAvailableDevicesLayout.setConstraints(mOpenButton, makegbc(0, 2, 1, 1,100,0,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mAvailableDevices.add(mOpenButton);

		mAvailableDevicesLayout.setConstraints(mCloseButton, makegbc(1, 2, 1, 1,100,0,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mAvailableDevices.add(mCloseButton);

		mAvailableDevicesLayout.setConstraints(mAcquireButton, makegbc(2, 2, 1, 1,100,0,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mAvailableDevices.add(mAcquireButton);

		mAvailableDevicesLayout.setConstraints(mReleaseButton, makegbc(3, 2, 1, 1,100,0,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mAvailableDevices.add(mReleaseButton);

		mCurrentVersionLayout.setConstraints(mDriverVersionInfo, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		mCurrentVersion.add(mDriverVersionInfo);

		mDeviceParametersLayout.setConstraints(mUnconfigureOnClose, makegbc(0, 0, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		mDeviceParameters.add(mUnconfigureOnClose);

		mDeviceParametersLayout.setConstraints(mResetOnClose, makegbc(0, 1, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		mDeviceParameters.add(mResetOnClose);

		mDeviceParametersLayout.setConstraints(mEnableWakeup, makegbc(0, 2, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		mDeviceParameters.add(mEnableWakeup);

		mDeviceParametersLayout.setConstraints(mRequestTimeoutLabel, makegbc(0, 3, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		mDeviceParameters.add(mRequestTimeoutLabel);

		mDeviceParametersLayout.setConstraints(mRequestTimeoutTF, makegbc(1, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mDeviceParameters.add(mRequestTimeoutTF);

		mDeviceParametersLayout.setConstraints(mGetDeviceParametersButton, makegbc(0, 4, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mDeviceParameters.add(mGetDeviceParametersButton);

		mDeviceParametersLayout.setConstraints(mSetDeviceParametersButton, makegbc(1, 4, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mDeviceParameters.add(mSetDeviceParametersButton);

		layout.setConstraints(mAvailableDevices, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		this.add(mAvailableDevices);
		layout.setConstraints(mDeviceParameters, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		this.add(mDeviceParameters);
		layout.setConstraints(mCurrentVersion, makegbc(0, 1, 2, 1,100,0,GridBagConstraints.HORIZONTAL,GridBagConstraints.WEST));
		this.add(mCurrentVersion);

	}

	public void getDeviceParameters() {
		int Status;
		USBIO_DEVICE_PARAMETERS DevParam = new USBIO_DEVICE_PARAMETERS();
		Status = mainFrame.gUsbIo.getDeviceParameters(DevParam);
		if (Status == 0) {
			// update display
			mRequestTimeoutTF.setText(Integer.toString(DevParam.RequestTimeout));

			if ((DevParam.Options & UsbIoInterface.USBIO_RESET_DEVICE_ON_CLOSE) != 0){
				mResetOnClose.setSelected(true);
			} else {
				mResetOnClose.setSelected(false);
			}
			if ((DevParam.Options & UsbIoInterface.USBIO_UNCONFIGURE_ON_CLOSE) != 0){
				mUnconfigureOnClose.setSelected(true);
			} else {
				mUnconfigureOnClose.setSelected(false);
			}
			if ((DevParam.Options & UsbIoInterface.USBIO_ENABLE_REMOTE_WAKEUP) != 0){
				mEnableWakeup.setSelected(true);
			} else {
				mEnableWakeup.setSelected(false);
			}

			mainFrame.printOutput("Get current device parameters was successful.\n");
		} else {
			mainFrame.printError("",Status);
		}
	}

	public void setDeviceParameters() {
		int Status;
		USBIO_DEVICE_PARAMETERS DevParam = new USBIO_DEVICE_PARAMETERS();
		if (mResetOnClose.isSelected()) {
			DevParam.Options |= UsbIoInterface.USBIO_RESET_DEVICE_ON_CLOSE;
		}
		if (mUnconfigureOnClose.isSelected()) {
			DevParam.Options |= UsbIoInterface.USBIO_UNCONFIGURE_ON_CLOSE;
		}
		if (mEnableWakeup.isSelected()) {
			DevParam.Options |= UsbIoInterface.USBIO_ENABLE_REMOTE_WAKEUP;
		}
		DevParam.RequestTimeout = Integer.parseInt(mRequestTimeoutTF.getText());
		Status = mainFrame.gUsbIo.setDeviceParameters(DevParam);
		if (Status == 0) {
			mainFrame.printOutput("Set new device parameters was successful.\n");
		} else {
			mainFrame.printError("",Status);
		}
	}

	public class OnGetDeviceParameters implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			getDeviceParameters();
		}
	}

	public class OnSetDeviceParameters implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			setDeviceParameters();
		}
	}

	public class OnScanButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			updateDeviceList(true);
		}
	}

	public class OnOpenButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int Status;

			if ( mainFrame.gUsbIo.isOpen() ) {
				mainFrame.printOutput("A device is already opened.\n");
				return;
			}
			int index = mDeviceList.getSelectedIndex();
			if (index > -1) {
				mainFrame.gDeviceNumber = Integer.parseInt(DevListNumber.elementAt(index).toString());
				UsbIo.destroyDeviceList(mainFrame.gDevList);
				mainFrame.gDevList = UsbIo.createDeviceList(UsbIoApp.guid);
				Status = mainFrame.gUsbIo.open(mainFrame.gDeviceNumber,mainFrame.gDevList,UsbIoApp.guid);
				if (Status != 0) {
					mainFrame.printError("",Status);
					mainFrame.gUsbIo.close();
				} else {
					mainFrame.printOutput("Device" + mainFrame.gDeviceNumber + " successfully opened.\n");
					mOpenButton.setEnabled(false);
					mCloseButton.setEnabled(true);
					mAcquireButton.setEnabled(true);
					mReleaseButton.setEnabled(true);


					USBIO_DRIVER_INFO DriverInfo = new USBIO_DRIVER_INFO();
					if (mainFrame.gUsbIo.getDriverInfo(DriverInfo) != 0) {
						mainFrame.printOutput("GetDriverInfo failed..\n");
					} else {
						String checked;
						if ((DriverInfo.Flags & UsbIoInterface.USBIO_INFOFLAG_CHECKED_BUILD) != 0) {
							checked = "debug";
						} else {
							checked = "release";
						}
						String add = "";
						if ((int)(DriverInfo.DriverVersion & 0xff) < 10) {
							add = "0";
						}
						String DrvInfostr = "USBIO Driver Version " +
							(int)(DriverInfo.DriverVersion >> 8) + "." + add +
							(int)(DriverInfo.DriverVersion & 0xff) + " Build " +
							DriverInfo.DriverBuildNumber + " (" + checked + "), API Version " +
							Integer.toHexString((int)(DriverInfo.APIVersion >> 8)) + "." +
							UsbIoApp.byteToString((byte)(DriverInfo.APIVersion & 0xff))
							;
						if (( DriverInfo.Flags & UsbIoInterface.USBIO_INFOFLAG_DEMO_VERSION ) != 0) {
							DrvInfostr += ", demo version";
						} else {
							if (( DriverInfo.Flags & UsbIoInterface.USBIO_INFOFLAG_LIGHT_VERSION ) != 0) {
								if (( DriverInfo.Flags & UsbIoInterface.USBIO_INFOFLAG_VS_LIGHT_VERSION ) != 0) {
									DrvInfostr += ", vendor-specific light version";
								} else {
									DrvInfostr += ", light version";
								}
							}
						}
						mDriverVersionInfo.setText(DrvInfostr);
						getDeviceParameters();
					}
				}
			} else {
				mainFrame.printOutput("No device selected. Select a device instance to open!.\n");
			}
			mainFrame.updateStateOfControls();
		}
	}

	public class OnCloseButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			mainFrame.gUsbIo.close();
			mOpenButton.setEnabled(true);
			mCloseButton.setEnabled(false);
			mAcquireButton.setEnabled(false);
			mReleaseButton.setEnabled(false);

			mainFrame.printOutput("Device" + mainFrame.gDeviceNumber + " closed.\n");
			mainFrame.gDeviceNumber = -1;
			mainFrame.updateStateOfControls();
		}
	}
	
	public class OnAcquireButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int Status;
			Status = mainFrame.gUsbIo.acquireDevice();
			if (Status == 0) {
				mainFrame.printOutput("Device" + mainFrame.gDeviceNumber + " acquired successful.\n");
			} else {
				mainFrame.printError("Acquire failed: ",Status);
			}
		}
	}

	public class OnReleaseButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int Status;
			Status = mainFrame.gUsbIo.releaseDevice();
			if (Status == 0) {
				mainFrame.printOutput("Device" + mainFrame.gDeviceNumber + " released successful.\n");
			} else {
				mainFrame.printError("Release failed: ",Status);
			}
		}
	}

}