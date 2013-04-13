package de.thesycon.usbiodemo.usbioapp;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;

import de.thesycon.usbio.PnPNotify;
import de.thesycon.usbio.PnPNotifyInterface;
import de.thesycon.usbio.UsbIo;
import de.thesycon.usbio.UsbIoErrorCodes;

public class UsbIoApp extends JFrame implements PnPNotifyInterface, UsbIoErrorCodes {

	static final String guid = "{325ddf96-938c-11d3-9e34-0080c82727f4}";
	static final int width = 680;
	static final int height = 380;
	static final int outputheight = 300;

	protected JTabbedPane TabControlMain;
	protected JPanel OutputWindowControl;
	protected JPanel OutputWindowButtonPanel;
	protected GridBagLayout OutputWindowControlLayout;
	protected GridBagLayout OutputWindowButtonPanelLayout;
	protected JButton ExitButton;
	protected JButton ClearButton;
	protected JButton ShowButton;
	protected JButton DockButton;

	protected DevicePage mDevicePage;
	protected DescriptorPage mDescriptorPage;
	protected InterfacePage mInterfacePage;
	protected FeaturePage mFeaturePage;
	protected OtherPage mOtherPage;
	protected ClassOrVendorRequestPage mClassOrVendorRequestPage;
	protected ConfigurationPage mConfigurationPage;
	protected PipesPage mPipesPage;

	public UsbIo gUsbIo;
	public PnPNotify gPnPNotify;
	public int gDevList;
	public int gDeviceNumber = -1;

	protected JFrame OutputWindow;
	protected JTextArea OutputWindowTA;

	public void onAdd() {
		printOutput("Device added\n");
	}

	public void onRemove() {
		printOutput("Device removed\n");
	}

	public void exit() {
		gUsbIo.close();
		UsbIo.destroyDeviceList(gDevList);
		gPnPNotify.disablePnPNotification(guid);
		dispose();
		System.exit(0);
	}

	public UsbIoApp () {
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				exit();
			}
		});

		gUsbIo = new UsbIo();

		gPnPNotify = new PnPNotify(this);

		OutputWindowControlLayout = new GridBagLayout();
		OutputWindowButtonPanelLayout = new GridBagLayout();

		ExitButton = new JButton("Exit");
		ExitButton.addActionListener(new OnExitButton());
		ClearButton = new JButton("Clear");
		ClearButton.addActionListener(new OnClearButton());
		ShowButton = new JButton("Show");
		ShowButton.addActionListener(new OnShowButton());
		DockButton = new JButton("Dock");
		DockButton.addActionListener(new OnDockButton());

		OutputWindowControl = new JPanel(OutputWindowControlLayout,true);
		OutputWindowButtonPanel = new JPanel(OutputWindowButtonPanelLayout,true);
		OutputWindowButtonPanel.setBorder(BorderFactory.createTitledBorder("Output Window"));

		OutputWindowButtonPanelLayout.setConstraints(ShowButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		OutputWindowButtonPanel.add(ShowButton);

		OutputWindowButtonPanelLayout.setConstraints(DockButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		OutputWindowButtonPanel.add(DockButton);

		OutputWindowButtonPanelLayout.setConstraints(ClearButton, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		OutputWindowButtonPanel.add(ClearButton);

		OutputWindowControlLayout.setConstraints(OutputWindowButtonPanel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		OutputWindowControl.add(OutputWindowButtonPanel);

		OutputWindowControlLayout.setConstraints(ExitButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		OutputWindowControl.add(ExitButton);

		mDevicePage = new DevicePage(this);
		mDescriptorPage = new DescriptorPage(this);
		mInterfacePage = new InterfacePage(this);
		mFeaturePage = new FeaturePage(this);
		mOtherPage = new OtherPage(this);
		mClassOrVendorRequestPage = new ClassOrVendorRequestPage(this);
		mConfigurationPage = new ConfigurationPage(this);
		mPipesPage = new PipesPage(this);

		OutputWindow = new JFrame("USBIO Output Window");
		OutputWindowTA = new JTextArea();
		OutputWindowTA.setFont(new Font("Courier", Font.PLAIN, 12));
		OutputWindow.getContentPane().add(new JScrollPane(OutputWindowTA));
		OutputWindow.setSize(width,outputheight);

		TabControlMain = new JTabbedPane();
		TabControlMain.addTab(mDevicePage.getPageName(),null,mDevicePage,mDevicePage.getPageName());
		TabControlMain.addTab(mDescriptorPage.getPageName(),null,mDescriptorPage,mDescriptorPage.getPageName());
		TabControlMain.addTab(mConfigurationPage.getPageName(),null,mConfigurationPage,mConfigurationPage.getPageName());
		TabControlMain.addTab(mInterfacePage.getPageName(),null,mInterfacePage,mInterfacePage.getPageName());
		TabControlMain.addTab(mPipesPage.getPageName(),null,mPipesPage,mPipesPage.getPageName());
		TabControlMain.addTab(mClassOrVendorRequestPage.getPageName(),null,mClassOrVendorRequestPage,mClassOrVendorRequestPage.getPageName());
		TabControlMain.addTab(mFeaturePage.getPageName(),null,mFeaturePage,mFeaturePage.getPageName());
		TabControlMain.addTab(mOtherPage.getPageName(),null,mOtherPage,mOtherPage.getPageName());
		TabControlMain.setTabPlacement(JTabbedPane.TOP);
		getContentPane().setLayout(new BorderLayout(2,1));
		getContentPane().add(TabControlMain,BorderLayout.CENTER);
		getContentPane().add(OutputWindowControl,BorderLayout.SOUTH);

		if (gPnPNotify.enablePnPNotification(guid) != USBIO_ERR_SUCCESS) {
			printOutput("Error EnablePnPNotificytion.");
		}

		updateStateOfControls();
	}

	// update enable/disable state of controls
	public void updateStateOfControls()
	{
		boolean isOpen = gUsbIo.isOpen();
		mDevicePage.updateStateOfControls(isOpen);
		mDescriptorPage.updateStateOfControls(isOpen);
		mConfigurationPage.updateStateOfControls(isOpen);
		mInterfacePage.updateStateOfControls(isOpen);
		mPipesPage.updateStateOfControls(isOpen);
		mClassOrVendorRequestPage.updateStateOfControls(isOpen);
		mFeaturePage.updateStateOfControls(isOpen);
		mOtherPage.updateStateOfControls(isOpen);
	}

	public class OnExitButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			exit();
		}
	}

	public class OnShowButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			OutputWindow.setVisible(true);
		}
	}

	public class OnClearButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			OutputWindowTA.setText("");
		}
	}

	public void dock() {

		Dimension scr = this.getSize();
		Point p = this.getLocation();
		OutputWindow.setLocation(p.x,p.y+scr.height);
	}

	public class OnDockButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			dock();
		}
	}

	public void printOutput(String str) {
		OutputWindowTA.append(str);
	}

	public void printError(String str,int ErrorCode) {
		OutputWindowTA.append(str + UsbIo.errorText(ErrorCode) + "\n");
	}

    private static final char[] HEX_DIGITS = {
	'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
    };

    public static String intToString (int n) {
		char[] buf = new char[8];
		for(int i = 7; i >= 0; i--) {
			buf[i] = HEX_DIGITS[n & 0x0F];
			n >>>= 4;
		}
		return new String(buf);
    }

    public static String shortToString (short n) {
		char[] buf = new char[4];
		for(int i = 3; i >= 0; i--) {
			buf[i] = HEX_DIGITS[n & 0x0F];
			n >>>= 4;
		}
		return new String(buf);
    }

    public static String byteToString (byte n) {
		char[] buf = new char[2];
		for(int i = 1; i >= 0; i--) {
			buf[i] = HEX_DIGITS[n & 0x0F];
			n >>>= 4;
		}
		return new String(buf);
    }

	public static GridBagConstraints makegbc (int x, int y, int width, int height) {
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = x;
		gbc.gridy = y;
		gbc.gridwidth = width;
		gbc.gridheight = height;
		gbc.insets = new Insets(1, 1, 1, 1);
		return gbc;
	}

	public static GridBagConstraints makegbc (int x, int y, int width, int height,int weightx,int weighty,int fill,int anchor) {
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = x;
		gbc.gridy = y;
		gbc.gridwidth = width;
		gbc.gridheight = height;
		gbc.insets = new Insets(1, 1, 1, 1);
		gbc.weightx = weightx;
		gbc.weighty = weighty;
		gbc.fill = fill;
		gbc.anchor = anchor;
		return gbc;
	}

	public static void main(String args[]) {
		Dimension scr= Toolkit.getDefaultToolkit().getScreenSize();
		UsbIoApp MainFrame = new UsbIoApp();
		MainFrame.setSize(width,height);
		MainFrame.setBounds((scr.width-width)/2,(scr.height-(height+outputheight))/2,
                 width,height);
		MainFrame.setTitle("USBIO Demo Application");
		MainFrame.dock();
		MainFrame.OutputWindow.setVisible(true);
		MainFrame.setVisible(true);
	}

	// return string for pipe type
	public String pipeTypeStr(int PipeType)
	{
		if (PipeType == 0) {
			return "Control";
		}
		if (PipeType == 1) {
			return "Isochronous";
		}
		if (PipeType == 2) {
			return "Bulk";
		}
		if (PipeType == 3) {
			return "Interrupt";
		}
		return "unknown";
	}


	// return string for endpoint direction
	public String endpointDirectionStr(byte EndpointAddress)
	{
		if ((EndpointAddress &0x80) != 0) {
			return "IN";
		} else {
			return "OUT";
		}
	}
}