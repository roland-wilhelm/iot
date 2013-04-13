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
import javax.swing.JPanel;
import javax.swing.JTextField;

import de.thesycon.usbio.structs.USBIO_BANDWIDTH_INFO;
import de.thesycon.usbio.structs.USBIO_SET_CONFIGURATION;

public class ConfigurationPage extends PanelPage {

	public String getPageName() { return "Configuration"; };

	protected UsbIoApp mainFrame;

	protected JPanel SetConfigurationPanel;
	protected JPanel InterfaceListPanel;
	protected JPanel GetConfigurationPanel;
	protected JPanel UnconfigureDevicePanel;
	protected JPanel BandwidthInfoPanel;

	protected GridBagLayout SetConfigurationPanelLayout;
	protected GridBagLayout InterfaceListPanelLayout;
	protected GridBagLayout GetConfigurationPanelLayout;
	protected GridBagLayout UnconfigureDevicePanelLayout;
	protected GridBagLayout BandwidthInfoPanelLayout;


	protected JButton mSetConfigurationButton;
	protected JButton mGetConfigurationButton;
	protected JButton mUnconfigureDeviceButton;
	protected JButton mBandwidthInfoButton;

	protected JLabel mConfDescIndexLabel;
	protected JLabel mInterfaceLabel;
	protected JLabel mAltSettingLabel;
	protected JLabel mMaxTransferLabel;

	protected JTextField mConfDescIndexTF;
	protected JTextField mInterface0TF;
	protected JTextField mInterface1TF;
	protected JTextField mInterface2TF;
	protected JTextField mInterface3TF;
	protected JTextField mAltSetting0TF;
	protected JTextField mAltSetting1TF;
	protected JTextField mAltSetting2TF;
	protected JTextField mAltSetting3TF;
	protected JTextField mMaxTransfer0TF;
	protected JTextField mMaxTransfer1TF;
	protected JTextField mMaxTransfer2TF;
	protected JTextField mMaxTransfer3TF;

	protected JCheckBox mInterface0Check;
	protected JCheckBox mInterface1Check;
	protected JCheckBox mInterface2Check;
	protected JCheckBox mInterface3Check;

	public ConfigurationPage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mSetConfigurationButton);
		ret.addElement(mGetConfigurationButton);
		ret.addElement(mUnconfigureDeviceButton);
		ret.addElement(mBandwidthInfoButton);
		ret.addElement(mInterface0Check);
		ret.addElement(mInterface1Check);
		ret.addElement(mInterface2Check);
		ret.addElement(mInterface3Check);
		ret.addElement(mConfDescIndexTF);
		ret.addElement(mInterface0TF);
		ret.addElement(mInterface1TF);
		ret.addElement(mInterface2TF);
		ret.addElement(mInterface3TF);
		ret.addElement(mAltSetting0TF);
		ret.addElement(mAltSetting1TF);
		ret.addElement(mAltSetting2TF);
		ret.addElement(mAltSetting3TF);
		ret.addElement(mMaxTransfer0TF);
		ret.addElement(mMaxTransfer1TF);
		ret.addElement(mMaxTransfer2TF);
		ret.addElement(mMaxTransfer3TF);
		return ret;
	}

	public void initGUIelements() {
		mSetConfigurationButton = new JButton("Set Configuration");
		mSetConfigurationButton.addActionListener(new OnSetConfigurationButton());
		mGetConfigurationButton = new JButton("Get Configuration");
		mGetConfigurationButton.addActionListener(new OnGetConfigurationButton());
		mUnconfigureDeviceButton = new JButton("Unconfigure Device");
		mUnconfigureDeviceButton.addActionListener(new OnUnconfigureDeviceButton());
		mBandwidthInfoButton = new JButton("Get Bandwidth Info");
		mBandwidthInfoButton.addActionListener(new OnBandwidthInfoButton());

		SetConfigurationPanelLayout = new GridBagLayout();
		InterfaceListPanelLayout = new GridBagLayout();
		GetConfigurationPanelLayout = new GridBagLayout();
		UnconfigureDevicePanelLayout = new GridBagLayout();
		BandwidthInfoPanelLayout = new GridBagLayout();

		SetConfigurationPanel = new JPanel(SetConfigurationPanelLayout,true);
		SetConfigurationPanel.setBorder(BorderFactory.createTitledBorder("Set Configuration"));
		InterfaceListPanel = new JPanel(InterfaceListPanelLayout,true);
		InterfaceListPanel.setBorder(BorderFactory.createTitledBorder("Interface List"));
		GetConfigurationPanel = new JPanel(GetConfigurationPanelLayout,true);
		GetConfigurationPanel.setBorder(BorderFactory.createTitledBorder("Get Configuration"));
		UnconfigureDevicePanel = new JPanel(UnconfigureDevicePanelLayout,true);
		UnconfigureDevicePanel.setBorder(BorderFactory.createTitledBorder("Unconfigure Device"));
		BandwidthInfoPanel = new JPanel(BandwidthInfoPanelLayout,true);
		BandwidthInfoPanel.setBorder(BorderFactory.createTitledBorder("Get Bandwidth Info"));

		mInterface0Check = new JCheckBox("",true);
		mInterface1Check = new JCheckBox("",false);
		mInterface2Check = new JCheckBox("",false);
		mInterface3Check = new JCheckBox("",false);

		mConfDescIndexLabel = new JLabel("Conf. Desc. Index:");
		mInterfaceLabel = new JLabel("Interface:");
		mAltSettingLabel = new JLabel("Alt. Setting:");
		mMaxTransferLabel = new JLabel("Max Transfer:");

		mConfDescIndexTF = new JTextField("0",5);
		mInterface0TF = new JTextField("0",5);
		mInterface1TF = new JTextField("1",5);
		mInterface2TF = new JTextField("2",5);
		mInterface3TF = new JTextField("3",5);
		mAltSetting0TF = new JTextField("0",5);
		mAltSetting1TF = new JTextField("0",5);
		mAltSetting2TF = new JTextField("0",5);
		mAltSetting3TF = new JTextField("0",5);
		mMaxTransfer0TF = new JTextField("65536",5);
		mMaxTransfer1TF = new JTextField("65536",5);
		mMaxTransfer2TF = new JTextField("65536",5);
		mMaxTransfer3TF = new JTextField("65536",5);

		SetConfigurationPanelLayout.setConstraints(mConfDescIndexLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		SetConfigurationPanel.add(mConfDescIndexLabel);

		SetConfigurationPanelLayout.setConstraints(mConfDescIndexTF, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		SetConfigurationPanel.add(mConfDescIndexTF);

		SetConfigurationPanelLayout.setConstraints(mSetConfigurationButton, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		SetConfigurationPanel.add(mSetConfigurationButton);

		InterfaceListPanelLayout.setConstraints(mInterface0Check, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface0Check);

		InterfaceListPanelLayout.setConstraints(mInterface1Check, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface1Check);

		InterfaceListPanelLayout.setConstraints(mInterface2Check, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface2Check);

		InterfaceListPanelLayout.setConstraints(mInterface3Check, makegbc(4, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface3Check);

		InterfaceListPanelLayout.setConstraints(mInterfaceLabel, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		InterfaceListPanel.add(mInterfaceLabel);

		InterfaceListPanelLayout.setConstraints(mInterface0TF, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface0TF);

		InterfaceListPanelLayout.setConstraints(mInterface1TF, makegbc(2, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface1TF);

		InterfaceListPanelLayout.setConstraints(mInterface2TF, makegbc(3, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface2TF);

		InterfaceListPanelLayout.setConstraints(mInterface3TF, makegbc(4, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mInterface3TF);

		InterfaceListPanelLayout.setConstraints(mAltSettingLabel, makegbc(0, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		InterfaceListPanel.add(mAltSettingLabel);

		InterfaceListPanelLayout.setConstraints(mAltSetting0TF, makegbc(1, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mAltSetting0TF);

		InterfaceListPanelLayout.setConstraints(mAltSetting1TF, makegbc(2, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mAltSetting1TF);

		InterfaceListPanelLayout.setConstraints(mAltSetting2TF, makegbc(3, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mAltSetting2TF);

		InterfaceListPanelLayout.setConstraints(mAltSetting3TF, makegbc(4, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mAltSetting3TF);

		InterfaceListPanelLayout.setConstraints(mMaxTransferLabel, makegbc(0, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		InterfaceListPanel.add(mMaxTransferLabel);

		InterfaceListPanelLayout.setConstraints(mMaxTransfer0TF, makegbc(1, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mMaxTransfer0TF);

		InterfaceListPanelLayout.setConstraints(mMaxTransfer1TF, makegbc(2, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mMaxTransfer1TF);

		InterfaceListPanelLayout.setConstraints(mMaxTransfer2TF, makegbc(3, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mMaxTransfer2TF);

		InterfaceListPanelLayout.setConstraints(mMaxTransfer3TF, makegbc(4, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		InterfaceListPanel.add(mMaxTransfer3TF);

		GetConfigurationPanelLayout.setConstraints(mGetConfigurationButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		GetConfigurationPanel.add(mGetConfigurationButton);

		UnconfigureDevicePanelLayout.setConstraints(mUnconfigureDeviceButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		UnconfigureDevicePanel.add(mUnconfigureDeviceButton);

		BandwidthInfoPanelLayout.setConstraints(mBandwidthInfoButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		BandwidthInfoPanel.add(mBandwidthInfoButton);

		layout.setConstraints(SetConfigurationPanel, makegbc(0, 0, 2, 1,200,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(SetConfigurationPanel);

		layout.setConstraints(InterfaceListPanel, makegbc(0, 1, 2, 2,200,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(InterfaceListPanel);

		layout.setConstraints(GetConfigurationPanel, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(GetConfigurationPanel);

		layout.setConstraints(UnconfigureDevicePanel, makegbc(2, 1, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(UnconfigureDevicePanel);

		layout.setConstraints(BandwidthInfoPanel, makegbc(2, 2, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(BandwidthInfoPanel);


	}

	public class OnUnconfigureDeviceButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;

			err= mainFrame.gUsbIo.unconfigureDevice();
			if (err != 0) {
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Device is unconfigured.\n");
			}
		}
	}

	public class OnBandwidthInfoButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			USBIO_BANDWIDTH_INFO BandwidthInfo = new USBIO_BANDWIDTH_INFO();

			err= mainFrame.gUsbIo.getBandwidthInfo(BandwidthInfo);
			if (err != 0) {
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Total Bandwidth   : " + BandwidthInfo.TotalBandwidth + " kbps\n");
				mainFrame.printOutput("Consumed Bandwidth: " + BandwidthInfo.ConsumedBandwidth + " kbps\n");
			}
		}
	}

	public class OnGetConfigurationButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			byte[] ConfigurationValue = new byte[1];

			err= mainFrame.gUsbIo.getConfiguration(ConfigurationValue);
			if (err != 0) {
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Current Configuration Value is " + ConfigurationValue[0] + ".\n");
				if (ConfigurationValue[0] == 0) {
					mainFrame.printOutput("  Device is not configured.\n");
				}
			}
		}
	}

	public class OnSetConfigurationButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int err;
				USBIO_SET_CONFIGURATION Conf = new USBIO_SET_CONFIGURATION();
				Conf.ConfigurationIndex = (short)Integer.decode(mConfDescIndexTF.getText()).intValue();
				Conf.NbOfInterfaces = 0;

				if (mInterface0Check.isSelected()) {
					Conf.InterfaceList[Conf.NbOfInterfaces].InterfaceIndex = (short)Integer.decode(mInterface0TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].AlternateSettingIndex = (short)Integer.decode(mAltSetting0TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].MaximumTransferSize = (int)Integer.decode(mMaxTransfer0TF.getText()).intValue();
					Conf.NbOfInterfaces++;
				}
				if (mInterface1Check.isSelected()) {
					Conf.InterfaceList[Conf.NbOfInterfaces].InterfaceIndex = (short)Integer.decode(mInterface1TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].AlternateSettingIndex = (short)Integer.decode(mAltSetting1TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].MaximumTransferSize = (int)Integer.decode(mMaxTransfer1TF.getText()).intValue();
					Conf.NbOfInterfaces++;
				}
				if (mInterface2Check.isSelected()) {
					Conf.InterfaceList[Conf.NbOfInterfaces].InterfaceIndex = (short)Integer.decode(mInterface2TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].AlternateSettingIndex = (short)Integer.decode(mAltSetting2TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].MaximumTransferSize = (int)Integer.decode(mMaxTransfer2TF.getText()).intValue();
					Conf.NbOfInterfaces++;
				}
				if (mInterface3Check.isSelected()) {
					Conf.InterfaceList[Conf.NbOfInterfaces].InterfaceIndex = (short)Integer.decode(mInterface3TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].AlternateSettingIndex = (short)Integer.decode(mAltSetting3TF.getText()).intValue();
					Conf.InterfaceList[Conf.NbOfInterfaces].MaximumTransferSize = (int)Integer.decode(mMaxTransfer3TF.getText()).intValue();
					Conf.NbOfInterfaces++;
				}

				err= mainFrame.gUsbIo.setConfiguration(Conf);
				if (err != 0) {
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("The configuration has been successfully set.\n");
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}
}