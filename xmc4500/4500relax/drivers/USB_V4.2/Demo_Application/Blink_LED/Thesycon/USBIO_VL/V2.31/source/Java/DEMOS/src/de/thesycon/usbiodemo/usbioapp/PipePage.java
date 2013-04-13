package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JPanel;

import de.thesycon.usbio.UsbIo;
import de.thesycon.usbio.structs.USBIO_PIPE_PARAMETERS;

public class PipePage extends PanelPage {

	public String getPageName() { return "Pipe"; };

	protected PipeDialog mainFrame;


	protected JButton mAbortPipeButton;
	protected JButton mResetPipeButton;
	protected JButton mGetPipeParamButton;
	protected JButton mSetPipeParamButton;

	protected JCheckBox mAllowShortTransfer;
	protected JPanel mPipeParamPanel;

	protected GridBagLayout mPipeParamPanelLayout;


	public PipePage(PipeDialog Frame) {
		mainFrame = Frame;
	}

	public void initGUIelements() {
		mAbortPipeButton = new JButton("Abort Pipe");
		mAbortPipeButton.addActionListener(new OnAbortPipeButton());
		mResetPipeButton = new JButton("Reset Pipe");
		mResetPipeButton.addActionListener(new OnResetPipeButton());
		mGetPipeParamButton = new JButton("Get Pipe Parameters");
		mGetPipeParamButton.addActionListener(new OnGetPipeParams());
		mSetPipeParamButton = new JButton("Set Pipe Parameters");
		mSetPipeParamButton.addActionListener(new OnSetPipeParams());

		mAllowShortTransfer = new JCheckBox("Allow Short Transfer");

		mPipeParamPanelLayout = new GridBagLayout();

		mPipeParamPanel = new JPanel(mPipeParamPanelLayout, true);
		mPipeParamPanel.setBorder(BorderFactory.createTitledBorder("Pipe Parameters"));

		mPipeParamPanelLayout.setConstraints(mAllowShortTransfer, makegbc(0, 0, 2, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipeParamPanel.add(mAllowShortTransfer);

		mPipeParamPanelLayout.setConstraints(mGetPipeParamButton, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipeParamPanel.add(mGetPipeParamButton);

		mPipeParamPanelLayout.setConstraints(mSetPipeParamButton, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mPipeParamPanel.add(mSetPipeParamButton);

		layout.setConstraints(mAbortPipeButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mAbortPipeButton);

		layout.setConstraints(mResetPipeButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(mResetPipeButton);

		layout.setConstraints(mPipeParamPanel, makegbc(0, 1, 2, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.CENTER));
		this.add(mPipeParamPanel);

	}

	public int GetPipeParams() {
		USBIO_PIPE_PARAMETERS PipeParameters = new USBIO_PIPE_PARAMETERS();
		int err = mainFrame.mPipe.getPipeParameters(PipeParameters);
		if ( err != 0 ) {
		} else {
			if ((PipeParameters.Flags & UsbIo.USBIO_SHORT_TRANSFER_OK) != 0) {
				mAllowShortTransfer.setSelected(true);
			} else {
				mAllowShortTransfer.setSelected(false);
			}
		}
		return err;
	}

	public class OnGetPipeParams implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err = GetPipeParams();
			if (err != 0 ) {
				mainFrame.mainFrame.printError("",err);
			} else {
				mainFrame.mainFrame.printOutput("Get Pipe Parameters was successful.\n");
			}
		}
	}

	public class OnSetPipeParams implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			USBIO_PIPE_PARAMETERS PipeParameters = new USBIO_PIPE_PARAMETERS();
			PipeParameters.Flags = UsbIo.USBIO_SHORT_TRANSFER_OK;
			int err = mainFrame.mPipe.setPipeParameters(PipeParameters);
			if (err != 0 ) {
				mainFrame.mainFrame.printError("",err);
			} else {
				mainFrame.mainFrame.printOutput("Set Pipe Parameters was successful.\n");
			}
		}
	}

	public class OnAbortPipeButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err = mainFrame.mPipe.abortPipe();
			if (err != 0 ) {
				mainFrame.mainFrame.printError("",err);
			} else {
				mainFrame.mainFrame.printOutput("Abort Pipe was successful.\n");
			}
		}
	}

	public class OnResetPipeButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			int err = mainFrame.mPipe.resetPipe();
			if (err != 0 ) {
				mainFrame.mainFrame.printError("",err);
			} else {
				mainFrame.mainFrame.printOutput("Reset Pipe was successful.\n");
			}
		}
	}
}