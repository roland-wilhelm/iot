package de.thesycon.usbiodemo.usbioapp;
import java.awt.GridBagConstraints;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JTextField;

import de.thesycon.usbio.structs.USBIO_PIPE_STATISTICS;

public class PipeStatisticsPanel extends PanelPage {

	public String getPageName() { return ""; };

	//protected PipeDialog mainFrame;
	protected JLabel MeanDataRateLabel;
	protected JLabel ReqSucceededLabel;
	protected JLabel TotalBytesTransferedLabel;
	protected JLabel ReqFailedLabel;

	protected JTextField MeanDataRateTF;
	protected JTextField ReqSucceededTF;
	protected JTextField TotalBytesTransferedTF;
	protected JTextField ReqFailedTF;

	public PipeStatisticsPanel() {
		//mainFrame = Frame;
	}

	public void initGUIelements() {
		this.setBorder(BorderFactory.createTitledBorder("Pipe Statistics"));
		MeanDataRateLabel = new JLabel("Mean data rate (bytes/s)");
		ReqSucceededLabel = new JLabel("Requests succeeded");
		TotalBytesTransferedLabel = new JLabel("Total number of bytes transferred");
		ReqFailedLabel = new JLabel("Requests failed");

		MeanDataRateTF = new JTextField("0",10);
		ReqSucceededTF = new JTextField("0",10);
		TotalBytesTransferedTF = new JTextField("0",10);
		ReqFailedTF = new JTextField("0",10);

		layout.setConstraints(MeanDataRateLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(MeanDataRateLabel);

		layout.setConstraints(ReqSucceededLabel, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(ReqSucceededLabel);

		layout.setConstraints(MeanDataRateTF, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(MeanDataRateTF);

		layout.setConstraints(ReqSucceededTF, makegbc(1, 1, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(ReqSucceededTF);

		layout.setConstraints(TotalBytesTransferedLabel, makegbc(0, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(TotalBytesTransferedLabel);

		layout.setConstraints(ReqFailedLabel, makegbc(1, 2, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(ReqFailedLabel);

		layout.setConstraints(TotalBytesTransferedTF, makegbc(0, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(TotalBytesTransferedTF);

		layout.setConstraints(ReqFailedTF, makegbc(1, 3, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		this.add(ReqFailedTF);

	}

	public void setStatistics(USBIO_PIPE_STATISTICS stat) {

		MeanDataRateTF.setText(String.valueOf(stat.AverageRate));
		ReqSucceededTF.setText(String.valueOf(stat.RequestsSucceeded));
		TotalBytesTransferedTF.setText(String.valueOf(stat.BytesTransferred_L));
		ReqFailedTF.setText(String.valueOf(stat.RequestsFailed));
	}
}