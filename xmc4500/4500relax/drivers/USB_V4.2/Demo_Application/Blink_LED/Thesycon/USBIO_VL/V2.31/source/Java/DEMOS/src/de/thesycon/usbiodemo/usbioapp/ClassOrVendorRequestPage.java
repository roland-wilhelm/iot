package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JTextField;

import de.thesycon.usbio.UsbIo;
import de.thesycon.usbio.structs.USBIO_CLASS_OR_VENDOR_REQUEST;
import de.thesycon.usbio.structs.USBIO_DATA_BUFFER;

public class ClassOrVendorRequestPage extends PanelPage {

	public String getPageName() { return "Class or Vendor Requests"; };

	protected UsbIoApp mainFrame;


	protected JButton mSendRequest;

	protected JLabel mDirectionLabel;
	protected JLabel mTypeLabel;
	protected JLabel mRecipientLabel;
	protected JLabel mbRequestLabel;
	protected JLabel mwValueLabel;
	protected JLabel mwIndexLabel;
	protected JLabel mBytesToSendLabel;
	protected JLabel mMaxBytesToReLabel;

	protected JComboBox mDirectionCombo;
	protected JComboBox mTypeCombo;
	protected JComboBox mRecipientCombo;
	protected JTextField mbRequestTF;
	protected JTextField mwValueTF;
	protected JTextField mwIndexTF;
	protected JTextField mBytesToSendTF;
	protected JTextField mMaxBytesToReTF;

	protected JCheckBox mShortTransferOkCheck;

	public ClassOrVendorRequestPage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mSendRequest);
		ret.addElement(mDirectionCombo);
		ret.addElement(mTypeCombo);
		ret.addElement(mRecipientCombo);
		ret.addElement(mbRequestTF);
		ret.addElement(mwValueTF);
		ret.addElement(mwIndexTF);
		ret.addElement(mBytesToSendTF);
		ret.addElement(mMaxBytesToReTF);
		ret.addElement(mShortTransferOkCheck);
		return ret;
	}

	public void initGUIelements() {
		mSendRequest = new JButton("Send Request");
		mSendRequest.addActionListener(new OnSendRequestButton());

		mDirectionLabel = new JLabel("Direction:");
		mTypeLabel = new JLabel("Type:");
		mRecipientLabel = new JLabel("Recipient:");
		mbRequestLabel = new JLabel("bRequest:");
		mwValueLabel = new JLabel("wValue:");
		mwIndexLabel = new JLabel("wIndex:");
		mBytesToSendLabel = new JLabel("Bytes to send:");
		mMaxBytesToReLabel = new JLabel("May bytes to receive");

		mShortTransferOkCheck = new JCheckBox("Short Transfer OK",true);

		Object[] DirectionData = {"HostToDevice","DeviceToHost"};
		mDirectionCombo = new JComboBox(DirectionData);
		Object[] TypeData = {"Class","Vendor"};
		mTypeCombo = new JComboBox(TypeData);
		Object[] RecipientData = {"Device","Interface","Endpoint","Other"};
		mRecipientCombo = new JComboBox(RecipientData);
		mbRequestTF = new JTextField("0x00",5);
		mwValueTF = new JTextField("0x0000",5);
		mwIndexTF = new JTextField("0x0000",5);
		mBytesToSendTF = new JTextField("0x00 0x00 0x00 0x00",30);
		mMaxBytesToReTF = new JTextField("8",5);

		layout.setConstraints(mDirectionLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mDirectionLabel);

		layout.setConstraints(mDirectionCombo, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mDirectionCombo);

		layout.setConstraints(mbRequestLabel, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mbRequestLabel);

		layout.setConstraints(mbRequestTF, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mbRequestTF);

		layout.setConstraints(mSendRequest, makegbc(4, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mSendRequest);

		layout.setConstraints(mTypeLabel, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mTypeLabel);

		layout.setConstraints(mTypeCombo, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mTypeCombo);

		layout.setConstraints(mwValueLabel, makegbc(2, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mwValueLabel);

		layout.setConstraints(mwValueTF, makegbc(3, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mwValueTF);

		layout.setConstraints(mRecipientLabel, makegbc(0, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mRecipientLabel);

		layout.setConstraints(mRecipientCombo, makegbc(1, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mRecipientCombo);

		layout.setConstraints(mwIndexLabel, makegbc(2, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mwIndexLabel);

		layout.setConstraints(mwIndexTF, makegbc(3, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mwIndexTF);

		layout.setConstraints(mBytesToSendLabel, makegbc(0, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mBytesToSendLabel);

		layout.setConstraints(mBytesToSendTF, makegbc(1, 3, 4, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mBytesToSendTF);

		layout.setConstraints(mMaxBytesToReLabel, makegbc(0, 4, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mMaxBytesToReLabel);

		layout.setConstraints(mMaxBytesToReTF, makegbc(1, 4, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mMaxBytesToReTF);

		layout.setConstraints(mShortTransferOkCheck, makegbc(2, 4, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mShortTransferOkCheck);

	}

	public class OnSendRequestButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				USBIO_DATA_BUFFER BufDesc = null;
				int BufferLength = Integer.decode(mMaxBytesToReTF.getText()).intValue();
				USBIO_CLASS_OR_VENDOR_REQUEST Request = new USBIO_CLASS_OR_VENDOR_REQUEST();
				Request.Type = mTypeCombo.getSelectedIndex() + 1;
				Request.Recipient = mRecipientCombo.getSelectedIndex();
				Request.RequestTypeReservedBits = (byte)0;
				Request.Request = (byte)Integer.decode(mbRequestTF.getText()).intValue();
				Request.Value = (short)Integer.decode(mwValueTF.getText()).intValue();
				Request.Index = (short)Integer.decode(mwIndexTF.getText()).intValue();
				if (mShortTransferOkCheck.isSelected()) {Request.Flags |= UsbIo.USBIO_SHORT_TRANSFER_OK;}
				int err = 0;
				switch (mDirectionCombo.getSelectedIndex()) {
					case 0:
						// write
						Vector arg = new Vector();
						String str = mBytesToSendTF.getText();
						StringBuffer buf = new StringBuffer();
						for (int i = 0; i< str.length(); i++){
							char a = str.charAt(i);
							if (a == ' ') {
								arg.add(String.valueOf(Integer.decode(buf.toString()).intValue()));
								buf = new StringBuffer();
							} else {
								buf.append(a);
							}
						}
						BufDesc = new USBIO_DATA_BUFFER(arg.size());
						BufDesc.setNumberOfBytesToTransfer(arg.size());
						for (int j = 0;j < BufDesc.getBytesTransferred();j++) {
							BufDesc.Buffer()[j] = (byte)Integer.parseInt(arg.elementAt(j).toString());
						}
						err = mainFrame.gUsbIo.classOrVendorOutRequest(BufDesc, Request);
					break;
					case 1:
						// read
						BufDesc = new USBIO_DATA_BUFFER(BufferLength);
						BufDesc.setNumberOfBytesToTransfer(BufferLength);
						err = mainFrame.gUsbIo.classOrVendorInRequest(BufDesc, Request);
					break;
				}

				if (err != 0) {
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("Class or Vendor request was successful.\n");
					if (mDirectionCombo.getSelectedIndex() == 1) {
						for (int i = 0; i < BufDesc.getBytesTransferred();i++) {
							mainFrame.printOutput("0x" + UsbIoApp.byteToString(BufDesc.Buffer()[i]) + " ");
							if ((i % 8) == 7) {
								mainFrame.printOutput("\n");
							}
						}
					}
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}
}