package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class ReadFromFilePage extends PanelPage {

	public String getPageName() { return "Write from File to Pipe"; };

	protected PipeDlgFromFile mainFrame;


	public JButton mStartButton;
	protected JButton mStopButton;

	public JTextField mDestFileTF;
	protected JButton mBrowseButton;

	protected JPanel mBrowsePanel;
	protected GridBagLayout mBrowsePanelLayout;


	public ReadFromFilePage(PipeDlgFromFile Frame) {
		mainFrame = Frame;
	}

	public void initGUIelements() {
		mStartButton = new JButton("Start Writing");
		mStartButton.addActionListener(new OnStartButton());
		mStopButton = new JButton("Stop Writing");
		mStopButton.addActionListener(new OnStopButton());

		mDestFileTF = new JTextField("",20);
		mBrowseButton = new JButton("Browse");
		mBrowseButton.addActionListener(new OnBrowseButton());


		mBrowsePanelLayout = new GridBagLayout();

		mBrowsePanel = new JPanel(mBrowsePanelLayout, true);
		mBrowsePanel.setBorder(BorderFactory.createTitledBorder("Source File"));

		mBrowsePanelLayout.setConstraints(mDestFileTF, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mBrowsePanel.add(mDestFileTF);

		mBrowsePanelLayout.setConstraints(mBrowseButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mBrowsePanel.add(mBrowseButton);

		layout.setConstraints(mStartButton, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mStartButton);

		layout.setConstraints(mStopButton, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mStopButton);

		layout.setConstraints(mBrowsePanel, makegbc(0, 0, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mBrowsePanel);
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

	public class OnBrowseButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			JFileChooser chooser = new JFileChooser();
			int returnVal = chooser.showOpenDialog(mainFrame);
			if(returnVal == JFileChooser.APPROVE_OPTION) {
			   mDestFileTF.setText(chooser.getSelectedFile().getPath());
			}
		}
	}
}