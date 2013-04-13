package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class BufferPage extends PanelPage {

	public String getPageName() { return "Buffers"; };

	protected PipeDialog mainFrame;


	protected JButton mSetDefaultsButton;

	protected JLabel mSizeOfBufferLabel;
	protected JLabel mNumberOfBuffersLabel;
	protected JLabel mMaxErrorCountLabel;
	protected JLabel mNumberOfIsoPacketsPerBufferLabel;
	protected JTextField mSizeOfBufferTF;
	protected JTextField mNumberOfBuffersTF;
	protected JTextField mMaxErrorCountTF;
	protected JTextField mNumberOfIsoPacketsPerBufferTF;


	public BufferPage(PipeDialog Frame) {
		mainFrame = Frame;
	}

	public void initGUIelements() {
		mSetDefaultsButton = new JButton("Set Defaults");

		mSizeOfBufferLabel = new JLabel("Size of Buffer:");
		mNumberOfBuffersLabel = new JLabel("Number of Buffers:");
		mMaxErrorCountLabel = new JLabel("Max Error Count:");
		mNumberOfIsoPacketsPerBufferLabel = new JLabel("Number of Iso Packets per Buffer:");

		mSizeOfBufferTF = new JTextField("65536",5);
		mNumberOfBuffersTF = new JTextField("5",5);
		mMaxErrorCountTF = new JTextField("5",5);
		mNumberOfIsoPacketsPerBufferTF = new JTextField("32",5);
		mNumberOfIsoPacketsPerBufferTF.setEnabled(false);

		layout.setConstraints(mSetDefaultsButton, makegbc(0, 0, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mSetDefaultsButton);

		layout.setConstraints(mSizeOfBufferLabel, makegbc(0, 1, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mSizeOfBufferLabel);

		layout.setConstraints(mSizeOfBufferTF, makegbc(1, 1, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mSizeOfBufferTF);

		layout.setConstraints(mNumberOfBuffersLabel, makegbc(0, 2, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mNumberOfBuffersLabel);

		layout.setConstraints(mNumberOfBuffersTF, makegbc(1, 2, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mNumberOfBuffersTF);

		layout.setConstraints(mMaxErrorCountLabel, makegbc(0, 3, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mMaxErrorCountLabel);

		layout.setConstraints(mMaxErrorCountTF, makegbc(1, 3, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mMaxErrorCountTF);

		layout.setConstraints(mNumberOfIsoPacketsPerBufferLabel, makegbc(0, 4, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		this.add(mNumberOfIsoPacketsPerBufferLabel);

		layout.setConstraints(mNumberOfIsoPacketsPerBufferTF, makegbc(1, 4, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		this.add(mNumberOfIsoPacketsPerBufferTF);

	}

	public void setDefaults() {
	  // defaults:
		if ( 	mainFrame.mainFrame.gUsbIo.isOperatingAtHighSpeed() ) {
			// high speed
		  	mSizeOfBufferTF.setText("512");
			mNumberOfIsoPacketsPerBufferTF.setText("256");
		} else {
			// full speed or low speed
		  	mSizeOfBufferTF.setText("64");
			mNumberOfIsoPacketsPerBufferTF.setText("32");
		}
		mNumberOfBuffersTF.setText("5");
		mMaxErrorCountTF.setText("5");


	  // pipe type
	  switch ( mainFrame.mPipeInfo.PipeType ) {
	  case 0:
		break;
	  case 1:
			mSizeOfBufferTF.setText(String.valueOf(16 + Integer.parseInt(mNumberOfIsoPacketsPerBufferTF.getText()) * (mainFrame.mPipeInfo.MaximumPacketSize + 12)));
		break;
	  case 2:
			mSizeOfBufferTF.setText(String.valueOf(mainFrame.mPipeInfo.MaximumTransferSize));
		break;
	  case 3:
			mSizeOfBufferTF.setText(String.valueOf(mainFrame.mPipeInfo.MaximumPacketSize));
		break;
	  default:
			break;
		}
	}

	public class OnSetDefaults implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			setDefaults();
		}
	}
}