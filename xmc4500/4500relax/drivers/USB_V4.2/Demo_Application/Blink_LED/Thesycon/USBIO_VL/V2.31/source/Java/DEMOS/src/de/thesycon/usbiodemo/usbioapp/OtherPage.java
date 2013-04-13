package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class OtherPage extends PanelPage {

	public String getPageName() { return "Other"; };

	protected UsbIoApp mainFrame;


	protected JButton mGetCurrentFrameNumberButton;
	protected JButton mResetDeviceButton;
	protected JButton mCyclePortButton;
	protected JButton mGetStatusButton;
	protected JButton mSetPowerStateButton;
	protected JButton mGetPowerStateButton;

	protected JLabel mRecipientLabel;
	protected JLabel mIndexLabel;
	protected JLabel mPowerStateLabel;
	protected JComboBox mRecipientCombo;
	protected JComboBox mPowerStateCombo;
	protected JTextField mIndexTF;

	protected JPanel mGetStatusPanel;
	protected JPanel mDevicePowerStatePanel;

	protected GridBagLayout mGetStatusPanelLayout;
	protected GridBagLayout mDevicePowerStatePanelLayout;

	public OtherPage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mGetCurrentFrameNumberButton);
		ret.addElement(mResetDeviceButton);
		ret.addElement(mCyclePortButton);
		ret.addElement(mGetStatusButton);
		ret.addElement(mSetPowerStateButton);
		ret.addElement(mGetPowerStateButton);
		ret.addElement(mRecipientCombo);
		ret.addElement(mPowerStateCombo);
		ret.addElement(mIndexTF);
		return ret;
	}

	public void initGUIelements() {
		mGetStatusPanelLayout = new GridBagLayout();
		mDevicePowerStatePanelLayout = new GridBagLayout();

		mGetStatusPanel = new JPanel(mGetStatusPanelLayout,true);
		mDevicePowerStatePanel = new JPanel(mDevicePowerStatePanelLayout,true);

		mGetStatusPanel.setBorder(BorderFactory.createTitledBorder("Get Status"));
		mDevicePowerStatePanel.setBorder(BorderFactory.createTitledBorder("Device Power State"));

		mGetCurrentFrameNumberButton = new JButton("Get Current Frame Number");
		mGetCurrentFrameNumberButton.addActionListener(new OnGetCurrentFrameNumberButton());
		mResetDeviceButton = new JButton("Reset Device");
		mResetDeviceButton.addActionListener(new OnResetDeviceButton());
		mCyclePortButton = new JButton("Cycle Port");
		mCyclePortButton.addActionListener(new OnCyclePortButton());
		mGetStatusButton = new JButton("Get Status");
		mGetStatusButton.addActionListener(new OnGetStatusButton());
		mSetPowerStateButton = new JButton("Set Power State");
		mSetPowerStateButton.addActionListener(new OnSetPowerStateButton());
		mGetPowerStateButton = new JButton("Get Power State");
		mGetPowerStateButton.addActionListener(new OnGetPowerStateButton());

		mRecipientLabel = new JLabel("Recipient:");
		mIndexLabel = new JLabel("Index:");
		mPowerStateLabel = new JLabel("Power State:");

		mIndexTF = new JTextField("0x00");

		Object[] RecipientData = {"Device","Interface","Endpoint","Other"};
		mRecipientCombo = new JComboBox(RecipientData);

		Object[] PowerStateData = {"DevicePowerD0","DevicePowerD1","DevicePowerD2","DevicePowerD3"};
		mPowerStateCombo = new JComboBox(PowerStateData);

		mGetStatusPanelLayout.setConstraints(mGetStatusButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mGetStatusPanel.add(mGetStatusButton);

		mGetStatusPanelLayout.setConstraints(mRecipientLabel, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mGetStatusPanel.add(mRecipientLabel);

		mGetStatusPanelLayout.setConstraints(mRecipientCombo, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mGetStatusPanel.add(mRecipientCombo);

		mGetStatusPanelLayout.setConstraints(mIndexLabel, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mGetStatusPanel.add(mIndexLabel);

		mGetStatusPanelLayout.setConstraints(mIndexTF, makegbc(4, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mGetStatusPanel.add(mIndexTF);

		mDevicePowerStatePanelLayout.setConstraints(mSetPowerStateButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mDevicePowerStatePanel.add(mSetPowerStateButton);

		mDevicePowerStatePanelLayout.setConstraints(mPowerStateLabel, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mDevicePowerStatePanel.add(mPowerStateLabel);

		mDevicePowerStatePanelLayout.setConstraints(mPowerStateCombo, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mDevicePowerStatePanel.add(mPowerStateCombo);

		mDevicePowerStatePanelLayout.setConstraints(mGetPowerStateButton, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mDevicePowerStatePanel.add(mGetPowerStateButton);

		layout.setConstraints(mGetCurrentFrameNumberButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mGetCurrentFrameNumberButton);

		layout.setConstraints(mResetDeviceButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mResetDeviceButton);

		layout.setConstraints(mCyclePortButton, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mCyclePortButton);

		layout.setConstraints(mGetStatusPanel, makegbc(0, 1, 3, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mGetStatusPanel);

		layout.setConstraints(mDevicePowerStatePanel, makegbc(0, 2, 3, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mDevicePowerStatePanel);
	}

	public class OnCyclePortButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;

			err = mainFrame.gUsbIo.cyclePort();
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Cycle Port was successful.\n");
			}
		}
	}

	public class OnResetDeviceButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;

			err = mainFrame.gUsbIo.resetDevice();
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Reset Device was successful.\n");
			}
		}
	}

	public class OnGetCurrentFrameNumberButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			int[] frame = new int[1];

			err = mainFrame.gUsbIo.getCurrentFrameNumber(frame);
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Current Frame Number is 0x" + UsbIoApp.intToString(frame[0]) + ".\n");
			}
		}
	}

	public class OnGetPowerStateButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			int[] powerstate = new int[1];

			err = mainFrame.gUsbIo.getDevicePowerState(powerstate);
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Current Power State is D" + powerstate[0] + ".\n");
				mPowerStateCombo.setSelectedIndex(powerstate[0]);
			}
		}
	}

	public class OnSetPowerStateButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			mainFrame.printOutput("Setting PowerState " + mPowerStateCombo.getSelectedIndex() + ".\n");
			err = mainFrame.gUsbIo.setDevicePowerState(mPowerStateCombo.getSelectedIndex());
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			}
		}
	}

	public class OnGetStatusButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err;
			short[] Status = new short[1];
			int Index = Integer.decode(mIndexTF.getText()).intValue();
			err = mainFrame.gUsbIo.getStatus(Status,mRecipientCombo.getSelectedIndex(),(short)Index);
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				mainFrame.printOutput("Status: 0x" + UsbIoApp.shortToString(Status[0]) + "\n");
			}
		}
	}
}