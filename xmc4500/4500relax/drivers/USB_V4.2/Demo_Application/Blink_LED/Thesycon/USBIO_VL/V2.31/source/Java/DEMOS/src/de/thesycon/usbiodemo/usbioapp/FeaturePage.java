package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class FeaturePage extends PanelPage {

	public String getPageName() { return "Feature"; };

	protected UsbIoApp mainFrame;


	protected JButton mSetFeatureButton;
	protected JButton mClearFeatureButton;

	protected JLabel mRecipientLabel;
	protected JComboBox mRecipientCombo;
	protected JLabel mFeatureLabel;
	protected JTextField mFeatureTF;
	protected JLabel mIndexLabel;
	protected JTextField mIndexTF;


	public FeaturePage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mSetFeatureButton);
		ret.addElement(mClearFeatureButton);
		ret.addElement(mRecipientCombo);
		ret.addElement(mFeatureTF);
		ret.addElement(mIndexTF);
		return ret;
	}

	public void initGUIelements() {

		mClearFeatureButton = new JButton("Clear Feature");
		mClearFeatureButton.addActionListener(new OnClearFeatureButton());
		mSetFeatureButton = new JButton("Set Feature");
		mSetFeatureButton.addActionListener(new OnSetFeatureButton());

		mRecipientLabel = new JLabel("Recipient:");
		mFeatureLabel = new JLabel("Feature:");
		mIndexLabel = new JLabel("Index:");

		Object[] data = {"Device","Interface","Endpoint","Other"};
		mRecipientCombo = new JComboBox(data);
		mFeatureTF = new JTextField("0x0000",5);
		mIndexTF = new JTextField("0x0000",5);

		layout.setConstraints(mRecipientLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mRecipientLabel);

		layout.setConstraints(mRecipientCombo, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mRecipientCombo);

		layout.setConstraints(mFeatureLabel, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mFeatureLabel);

		layout.setConstraints(mFeatureTF, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mFeatureTF);

		layout.setConstraints(mIndexLabel, makegbc(0, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mIndexLabel);

		layout.setConstraints(mIndexTF, makegbc(1, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mIndexTF);

		layout.setConstraints(mSetFeatureButton, makegbc(0, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mSetFeatureButton);

		layout.setConstraints(mClearFeatureButton, makegbc(1, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mClearFeatureButton);

	}

	public class OnClearFeatureButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int Index = Integer.decode(mIndexTF.getText()).intValue();
				int Feature = Integer.decode(mFeatureTF.getText()).intValue();
				int Recipient = mRecipientCombo.getSelectedIndex();
				int err;
				// send the command to the driver
				err= mainFrame.gUsbIo.clearFeature(Recipient, (short)Feature, (short)Index );
				if (err != 0) {
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("Clear Feature was successful.\n");
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}

	public class OnSetFeatureButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int Index = Integer.decode(mIndexTF.getText()).intValue();
				int Feature = Integer.decode(mFeatureTF.getText()).intValue();
				int Recipient = mRecipientCombo.getSelectedIndex();
				int err;
				// send the command to the driver
				err= mainFrame.gUsbIo.setFeature(Recipient, (short)Feature, (short)Index );
				if (err != 0) {
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("Set Feature was successful.\n");
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}
}