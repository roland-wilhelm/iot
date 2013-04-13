package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import de.thesycon.usbio.structs.USBIO_INTERFACE_SETTING;

public class InterfacePage extends PanelPage {

	public String getPageName() { return "Interface"; };

	protected UsbIoApp mainFrame;

	protected JPanel mSetInterfacePanel;
	protected JPanel mGetInterfacePanel;

	protected JLabel mInterfaceLabel;
	protected JTextField mInterfaceTF;

	protected JButton mGetInterfaceButton;
	protected JButton mSetInterfaceButton;

	protected JLabel mAltSettingLabel;
	protected JTextField mAltSettingTF;
	protected JLabel mMaxTransferLabel;
	protected JTextField mMaxTransferTF;


	protected GridBagLayout mSetInterfacePanelLayout;
	protected GridBagLayout mGetInterfacePanelLayout;

	public InterfacePage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mInterfaceTF);
		ret.addElement(mAltSettingTF);
		ret.addElement(mMaxTransferTF);
		ret.addElement(mGetInterfaceButton);
		ret.addElement(mSetInterfaceButton);
		return ret;
	}

	public void initGUIelements() {
		mInterfaceLabel = new JLabel("Interface:");
		mInterfaceTF = new JTextField("0",5);

		mGetInterfacePanelLayout = new GridBagLayout();
		mSetInterfacePanelLayout = new GridBagLayout();

		mSetInterfacePanel = new JPanel(mSetInterfacePanelLayout,true);
		mSetInterfacePanel.setBorder(BorderFactory.createTitledBorder("Set Interface"));
		mGetInterfacePanel = new JPanel(mGetInterfacePanelLayout,true);
		mGetInterfacePanel.setBorder(BorderFactory.createTitledBorder("Get Interface"));

		mGetInterfaceButton = new JButton("Get Interface");
		mGetInterfaceButton.addActionListener(new OnGetInterfaceButton());
		mSetInterfaceButton = new JButton("Set Interface");
		mSetInterfaceButton.addActionListener(new OnSetInterfaceButton());

		mAltSettingLabel = new JLabel("Alt. Setting:");
		mAltSettingTF = new JTextField("0",5);
		mMaxTransferLabel = new JLabel("Max Transfer:");
		mMaxTransferTF = new JTextField("65536",5);

		mGetInterfacePanelLayout.setConstraints(mGetInterfaceButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mGetInterfacePanel.add(mGetInterfaceButton);

		mSetInterfacePanelLayout.setConstraints(mAltSettingLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mSetInterfacePanel.add(mAltSettingLabel);

		mSetInterfacePanelLayout.setConstraints(mAltSettingTF, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mSetInterfacePanel.add(mAltSettingTF);

		mSetInterfacePanelLayout.setConstraints(mMaxTransferLabel, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mSetInterfacePanel.add(mMaxTransferLabel);

		mSetInterfacePanelLayout.setConstraints(mMaxTransferTF, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mSetInterfacePanel.add(mMaxTransferTF);

		mSetInterfacePanelLayout.setConstraints(mSetInterfaceButton, makegbc(0, 2, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mSetInterfacePanel.add(mSetInterfaceButton);

		layout.setConstraints(mInterfaceLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mInterfaceLabel);
		layout.setConstraints(mInterfaceTF, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mInterfaceTF);
		layout.setConstraints(mSetInterfacePanel, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mSetInterfacePanel);
		layout.setConstraints(mGetInterfacePanel, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mGetInterfacePanel);
	}

	public class OnGetInterfaceButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int m_Interface = Integer.decode(mInterfaceTF.getText()).intValue();
				int err;
				byte[] AlternateSetting = new byte[1];
				// send the command to the driver
				err= mainFrame.gUsbIo.getInterface(AlternateSetting, (short)m_Interface );
				if (err != 0) {
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("Current Alternate Setting for Interface " + m_Interface + " is " + AlternateSetting[0] + ".\n");
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}

	public class OnSetInterfaceButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				USBIO_INTERFACE_SETTING InterfaceSettings = new USBIO_INTERFACE_SETTING();
				InterfaceSettings.InterfaceIndex = (short)Integer.decode(mInterfaceTF.getText()).intValue();
				InterfaceSettings.AlternateSettingIndex = (short)Integer.decode(mAltSettingTF.getText()).intValue();
				InterfaceSettings.MaximumTransferSize = Integer.decode(mMaxTransferTF.getText()).intValue();
				int err;
				// send the command to the driver
				err= mainFrame.gUsbIo.setInterface(InterfaceSettings);
				if (err != 0) {
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("New Alternate Setting has been successfully set.\n");
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}
}