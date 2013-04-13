package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;

public class ReadToWinPage extends PanelPage {

	public String getPageName() { return "Read from Pipe to Output Window"; };

	protected PipeDlgToWin mainFrame;


	public JButton mStartButton;
	protected JButton mStopButton;

	protected JCheckBox mPrintToWindowCheck;



	public ReadToWinPage(PipeDlgToWin Frame) {
		mainFrame = Frame;
	}

	public void initGUIelements() {
		mStartButton = new JButton("Start Reading");
		mStartButton.addActionListener(new OnStartButton());
		mStopButton = new JButton("Stop Reading");
		mStopButton.addActionListener(new OnStopButton());

		mPrintToWindowCheck = new JCheckBox("Print to OutputWindow",true);

		layout.setConstraints(mStartButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mStartButton);

		layout.setConstraints(mStopButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mStopButton);

		layout.setConstraints(mPrintToWindowCheck, makegbc(0, 1, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mPrintToWindowCheck);
	}

	public class OnStartButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			mainFrame.start();
		}
	}

	public class OnStopButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			mainFrame.stop();
		}
	}
}