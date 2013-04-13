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

import de.thesycon.usbio.UsbIo;
import de.thesycon.usbio.structs.USBIO_DATA_BUFFER;
import de.thesycon.usbio.structs.USB_COMMON_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_CONFIGURATION_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_DEVICE_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_DEVICE_QUALIFIER_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_ENDPOINT_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_HID_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_INTERFACE_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_STRING_DESCRIPTOR;

public class DescriptorPage extends PanelPage {

	public String getPageName() { return "Descriptors"; };

	public static final int MAX_DESCRIPTOR_BUFFER_SIZE = 2047;

	protected UsbIoApp mainFrame;

	protected JPanel mDevDescPanel;
	protected JPanel mConfDescPanel;
	protected JPanel mStringDescPanel;
	protected JPanel mAnyDescPanel;

	protected JButton mGetDevDescButton;
	protected JButton mGetDevQuDescButton;

	protected JButton mGetConfDescButton;
	protected JButton mGetOtherSpeedConfDescButton;
	protected JLabel mConfDescIndexLabel;
	protected JTextField mConfDescIndexTF;

	protected JButton mGetStringDescButton;
	protected JLabel mStringDescIndexLabel;
	protected JTextField mStringDescIndexTF;
	protected JLabel mStringDescLanguageIDLabel;
	protected JTextField mStringDescLanguageIDTF;

	protected JButton mGetDescButton;
	protected JLabel mAnyDescTypeLabel;
	protected JTextField mAnyDescTypeTF;
	protected JLabel mAnyDescIndexLabel;
	protected JTextField mAnyDescIndexTF;
	protected JLabel mAnyDescLengthLabel;
	protected JTextField mAnyDescLengthTF;

	protected GridBagLayout mDevDescLayout;
	protected GridBagLayout mConfDescLayout;
	protected GridBagLayout mStringDescLayout;
	protected GridBagLayout mAnyDescLayout;

	public DescriptorPage(UsbIoApp Frame) {
		mainFrame = Frame;
	}

	public Vector getControlComponentsVector() {
		Vector ret = new Vector();
		ret.addElement(mGetDevDescButton);
		ret.addElement(mGetDevQuDescButton);
		ret.addElement(mGetConfDescButton);
		ret.addElement(mGetOtherSpeedConfDescButton);
		ret.addElement(mConfDescIndexTF);
		ret.addElement(mGetStringDescButton);
		ret.addElement(mStringDescIndexTF);
		ret.addElement(mStringDescLanguageIDTF);
		ret.addElement(mGetDescButton);
		ret.addElement(mAnyDescTypeTF);
		ret.addElement(mAnyDescIndexTF);
		ret.addElement(mAnyDescLengthTF);
		return ret;
	}

	public void initGUIelements() {

		mDevDescLayout = new GridBagLayout();
		mConfDescLayout = new GridBagLayout();
		mStringDescLayout = new GridBagLayout();
		mAnyDescLayout = new GridBagLayout();

		mDevDescPanel = new JPanel(mDevDescLayout,true);
		mDevDescPanel.setBorder(BorderFactory.createTitledBorder("Device Descriptor"));
		mConfDescPanel = new JPanel(mConfDescLayout,true);
		mConfDescPanel.setBorder(BorderFactory.createTitledBorder("Configuration Descriptor"));
		mStringDescPanel = new JPanel(mStringDescLayout,true);
		mStringDescPanel.setBorder(BorderFactory.createTitledBorder("String Descriptor"));
		mAnyDescPanel = new JPanel(mAnyDescLayout,true);
		mAnyDescPanel.setBorder(BorderFactory.createTitledBorder("Any Descriptor"));

		mGetDevDescButton = new JButton("Get Device Descriptor");
		mGetDevDescButton.addActionListener(new OnGetDevDescButton());
		mGetDevQuDescButton = new JButton("Get Device Qualifier Descriptor");
		mGetDevQuDescButton.addActionListener(new OnGetDevQuDescButton());

		mGetConfDescButton = new JButton("Get Config Descriptor");
		mGetConfDescButton.addActionListener(new OnGetConfDescButton());
		mGetOtherSpeedConfDescButton = new JButton("Get Other Speed Config Descriptor");
		mGetOtherSpeedConfDescButton.addActionListener(new OnGetOtherSpeedConfDescButton());
		mConfDescIndexLabel = new JLabel("Index:");
		mConfDescIndexTF = new JTextField("0",5);

		mGetStringDescButton = new JButton("Get String Descriptor");
		mGetStringDescButton.addActionListener(new OnGetStringDescButton());
		mStringDescIndexLabel = new JLabel("Index:");
		mStringDescIndexTF = new JTextField("1",5);
		mStringDescLanguageIDLabel = new JLabel("Language ID:");
		mStringDescLanguageIDTF = new JTextField("0x0000",5);

		mGetDescButton = new JButton("Get Descriptor");
		mGetDescButton.addActionListener(new OnGetAnyDescButton());
		mAnyDescTypeLabel = new JLabel("Type:");
		mAnyDescTypeTF = new JTextField("0x21",5);
		mAnyDescIndexLabel = new JLabel("Index:");
		mAnyDescIndexTF = new JTextField("0",5);
		mAnyDescLengthLabel = new JLabel("Length:");
		mAnyDescLengthTF = new JTextField("256",5);

		mDevDescLayout.setConstraints(mGetDevDescButton, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mDevDescPanel.add(mGetDevDescButton);

		mDevDescLayout.setConstraints(mGetDevQuDescButton, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mDevDescPanel.add(mGetDevQuDescButton);

		mConfDescLayout.setConstraints(mConfDescIndexLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mConfDescPanel.add(mConfDescIndexLabel);

		mConfDescLayout.setConstraints(mConfDescIndexTF, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mConfDescPanel.add(mConfDescIndexTF);

		mConfDescLayout.setConstraints(mGetConfDescButton, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mConfDescPanel.add(mGetConfDescButton);

		mConfDescLayout.setConstraints(mGetOtherSpeedConfDescButton, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mConfDescPanel.add(mGetOtherSpeedConfDescButton);

		mStringDescLayout.setConstraints(mStringDescIndexLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mStringDescPanel.add(mStringDescIndexLabel);

		mStringDescLayout.setConstraints(mStringDescIndexTF, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mStringDescPanel.add(mStringDescIndexTF);

		mStringDescLayout.setConstraints(mStringDescLanguageIDLabel, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mStringDescPanel.add(mStringDescLanguageIDLabel);

		mStringDescLayout.setConstraints(mStringDescLanguageIDTF, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mStringDescPanel.add(mStringDescLanguageIDTF);

		mStringDescLayout.setConstraints(mGetStringDescButton, makegbc(4, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mStringDescPanel.add(mGetStringDescButton);

		mAnyDescLayout.setConstraints(mAnyDescTypeLabel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mAnyDescPanel.add(mAnyDescTypeLabel);

		mAnyDescLayout.setConstraints(mAnyDescTypeTF, makegbc(1, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mAnyDescPanel.add(mAnyDescTypeTF);

		mAnyDescLayout.setConstraints(mAnyDescIndexLabel, makegbc(2, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mAnyDescPanel.add(mAnyDescIndexLabel);

		mAnyDescLayout.setConstraints(mAnyDescIndexTF, makegbc(3, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mAnyDescPanel.add(mAnyDescIndexTF);

		mAnyDescLayout.setConstraints(mAnyDescLengthLabel, makegbc(4, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.EAST));
		mAnyDescPanel.add(mAnyDescLengthLabel);

		mAnyDescLayout.setConstraints(mAnyDescLengthTF, makegbc(5, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.WEST));
		mAnyDescPanel.add(mAnyDescLengthTF);

		mAnyDescLayout.setConstraints(mGetDescButton, makegbc(6, 0, 1, 1,100,100,GridBagConstraints.NONE,GridBagConstraints.CENTER));
		mAnyDescPanel.add(mGetDescButton);

		layout.setConstraints(mDevDescPanel, makegbc(0, 0, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		this.add(mDevDescPanel);
		layout.setConstraints(mConfDescPanel, makegbc(0, 1, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		this.add(mConfDescPanel);
		layout.setConstraints(mStringDescPanel, makegbc(0, 2, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		this.add(mStringDescPanel);
		layout.setConstraints(mAnyDescPanel, makegbc(0, 3, 1, 1,100,100,GridBagConstraints.BOTH,GridBagConstraints.WEST));
		this.add(mAnyDescPanel);
	}


	public class OnGetDevDescButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			USB_DEVICE_DESCRIPTOR Desc = new USB_DEVICE_DESCRIPTOR();
			int err;

			// send command to driver
			err = mainFrame.gUsbIo.getDeviceDescriptor(Desc);
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				dumpDescriptor((USB_COMMON_DESCRIPTOR)Desc);
			}
		}
	}

	public class OnGetDevQuDescButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			USB_DEVICE_QUALIFIER_DESCRIPTOR Desc = new USB_DEVICE_QUALIFIER_DESCRIPTOR();
			USBIO_DATA_BUFFER BufDesc = new USBIO_DATA_BUFFER(Desc.getSize());
			BufDesc.setNumberOfBytesToTransfer(Desc.getSize());
			int err;

			// send command to driver
			err = mainFrame.gUsbIo.getDescriptor(BufDesc,0,(byte)(UsbIo.USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE),(byte)0);
			if (err != 0) {
				// print error message
				mainFrame.printError("",err);
			} else {
				Desc.parseByteArray(BufDesc.Buffer());
				dumpDescriptor((USB_COMMON_DESCRIPTOR)Desc);
			}
		}
	}

	public class OnGetStringDescButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			USB_STRING_DESCRIPTOR Desc = new USB_STRING_DESCRIPTOR();
			try {
				int index = Integer.decode(mStringDescIndexTF.getText()).intValue();
				int lang = Integer.decode(mStringDescLanguageIDTF.getText()).intValue();
				int err;

				// send command to driver
				err = mainFrame.gUsbIo.getStringDescriptor(Desc,(byte)index,lang);
				if (err != 0) {
					// print error message
					mainFrame.printError("",err);
				} else {
					if (index == 0) {
						mainFrame.printOutput("\n");
						mainFrame.printOutput("String Descriptor Language ID's\n");
						mainFrame.printOutput("0x" + UsbIoApp.byteToString(Desc.ByteArray[0]) + " " + "0x" + UsbIoApp.byteToString(Desc.ByteArray[1]) + " " + "0x" + UsbIoApp.byteToString(Desc.ByteArray[2]) + " " + "0x" + UsbIoApp.byteToString(Desc.ByteArray[3]) + " " + "\n");
						mStringDescLanguageIDTF.setText("0x"+UsbIoApp.byteToString(Desc.ByteArray[3])+UsbIoApp.byteToString(Desc.ByteArray[2]));
					} else {
						dumpDescriptor((USB_COMMON_DESCRIPTOR)Desc);
					}
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}

	public class OnGetAnyDescButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int type = Integer.decode(mAnyDescTypeTF.getText()).intValue();
				int index = Integer.decode(mAnyDescIndexTF.getText()).intValue();
				int length = Integer.decode(mAnyDescLengthTF.getText()).intValue();
				int err;

				USBIO_DATA_BUFFER BufDesc = new USBIO_DATA_BUFFER(length);
				BufDesc.setNumberOfBytesToTransfer(length);

				// send command to driver
				err = mainFrame.gUsbIo.getDescriptor(BufDesc, 0,(byte)type,(byte)index);
				if (err != 0) {
					// print error message
					mainFrame.printError("",err);
				} else {
					mainFrame.printOutput("\n");
					for (int i = 0; i < BufDesc.getBytesTransferred();i++) {
						mainFrame.printOutput("0x" + UsbIoApp.byteToString(BufDesc.Buffer()[i]) + " ");
						if ((i % 8) == 7) {
							mainFrame.printOutput("\n");
						}
					}
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}

	public class OnGetConfDescButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int index = Integer.decode(mConfDescIndexTF.getText()).intValue();
				int err;

				USBIO_DATA_BUFFER BufDesc = new USBIO_DATA_BUFFER(MAX_DESCRIPTOR_BUFFER_SIZE);
				BufDesc.setNumberOfBytesToTransfer(MAX_DESCRIPTOR_BUFFER_SIZE);

				// send command to driver
				err = mainFrame.gUsbIo.getConfigurationDescriptor(BufDesc,(byte)index);
				if (err != 0) {
					// print error message
					mainFrame.printError("",err);
				} else {
					int size = BufDesc.getBytesTransferred();
					int pos = 0;
					byte[] data;
					while (pos < size) {
						data = new byte[BufDesc.Buffer()[pos]];
						System.arraycopy(BufDesc.Buffer(),pos,data,0,BufDesc.Buffer()[pos]);
						switch(BufDesc.Buffer()[pos+1]) {
							case UsbIo.USB_DEVICE_DESCRIPTOR_TYPE:
								USB_DEVICE_DESCRIPTOR desc1 = new USB_DEVICE_DESCRIPTOR();
								desc1.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc1);
								break;
							case UsbIo.USB_CONFIGURATION_DESCRIPTOR_TYPE:
								USB_CONFIGURATION_DESCRIPTOR desc2 = new USB_CONFIGURATION_DESCRIPTOR();
								desc2.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc2);
								break;
							case UsbIo.USB_STRING_DESCRIPTOR_TYPE:
								USB_STRING_DESCRIPTOR desc3 = new USB_STRING_DESCRIPTOR();
								desc3.parseByteArray(data,BufDesc.Buffer()[pos]);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc3);
								break;
							case UsbIo.USB_INTERFACE_DESCRIPTOR_TYPE:
								USB_INTERFACE_DESCRIPTOR desc4 = new USB_INTERFACE_DESCRIPTOR();
								desc4.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc4);
								break;
							case UsbIo.USB_ENDPOINT_DESCRIPTOR_TYPE:
								USB_ENDPOINT_DESCRIPTOR desc5 = new USB_ENDPOINT_DESCRIPTOR();
								desc5.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc5);
								break;
							case UsbIo.USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:
								USB_DEVICE_QUALIFIER_DESCRIPTOR desc6 = new USB_DEVICE_QUALIFIER_DESCRIPTOR();
								desc6.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc6);
								break;
							case UsbIo.USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE:
								USB_CONFIGURATION_DESCRIPTOR desc7 = new USB_CONFIGURATION_DESCRIPTOR();
								desc7.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc7);
								break;
							case UsbIo.USB_HID_DESCRIPTOR_TYPE:
								USB_HID_DESCRIPTOR desc8 = new USB_HID_DESCRIPTOR();
								desc8.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc8);
								break;

							default:
								mainFrame.printOutput("\n");
								mainFrame.printOutput("Unknown Descriptor:\n");
						}
						pos = pos + BufDesc.Buffer()[pos];
					}
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}

	public class OnGetOtherSpeedConfDescButton implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int index = Integer.decode(mConfDescIndexTF.getText()).intValue();
				int err;

				USBIO_DATA_BUFFER BufDesc = new USBIO_DATA_BUFFER(MAX_DESCRIPTOR_BUFFER_SIZE);
				BufDesc.setNumberOfBytesToTransfer(MAX_DESCRIPTOR_BUFFER_SIZE);

				// send command to driver
				err = mainFrame.gUsbIo.getDescriptor(BufDesc,0,(byte)UsbIo.USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE,(byte)index);
				if (err != 0) {
					// print error message
					mainFrame.printError("",err);
				} else {
					int size = BufDesc.getBytesTransferred();
					int pos = 0;
					byte[] data;
					while (pos < size) {
						data = new byte[BufDesc.Buffer()[pos]];
						System.arraycopy(BufDesc.Buffer(),pos,data,0,BufDesc.Buffer()[pos]);
						switch(BufDesc.Buffer()[pos+1]) {
							case UsbIo.USB_DEVICE_DESCRIPTOR_TYPE:
								USB_DEVICE_DESCRIPTOR desc1 = new USB_DEVICE_DESCRIPTOR();
								desc1.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc1);
								break;
							case UsbIo.USB_CONFIGURATION_DESCRIPTOR_TYPE:
								USB_CONFIGURATION_DESCRIPTOR desc2 = new USB_CONFIGURATION_DESCRIPTOR();
								desc2.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc2);
								break;
							case UsbIo.USB_STRING_DESCRIPTOR_TYPE:
								USB_STRING_DESCRIPTOR desc3 = new USB_STRING_DESCRIPTOR();
								desc3.parseByteArray(data,BufDesc.Buffer()[pos]);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc3);
								break;
							case UsbIo.USB_INTERFACE_DESCRIPTOR_TYPE:
								USB_INTERFACE_DESCRIPTOR desc4 = new USB_INTERFACE_DESCRIPTOR();
								desc4.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc4);
								break;
							case UsbIo.USB_ENDPOINT_DESCRIPTOR_TYPE:
								USB_ENDPOINT_DESCRIPTOR desc5 = new USB_ENDPOINT_DESCRIPTOR();
								desc5.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc5);
								break;
							case UsbIo.USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:
								USB_DEVICE_QUALIFIER_DESCRIPTOR desc6 = new USB_DEVICE_QUALIFIER_DESCRIPTOR();
								desc6.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc6);
								break;
							case UsbIo.USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE:
								USB_CONFIGURATION_DESCRIPTOR desc7 = new USB_CONFIGURATION_DESCRIPTOR();
								desc7.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc7);
								break;
							case UsbIo.USB_HID_DESCRIPTOR_TYPE:
								USB_HID_DESCRIPTOR desc8 = new USB_HID_DESCRIPTOR();
								desc8.parseByteArray(data);
								dumpDescriptor((USB_COMMON_DESCRIPTOR)desc8);
								break;

							default:
								mainFrame.printOutput("\n");
								mainFrame.printOutput("Unknown Descriptor:\n");
						}
						pos = pos + BufDesc.Buffer()[pos];
					}
				}
			}
			catch (NumberFormatException ex) {
				mainFrame.printOutput("Wrong input format.\n");
			}
		}
	}

	void
	dumpDeviceDescriptor(
	USB_DEVICE_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("Device Descriptor:\n");
		mainFrame.printOutput("bLength            :   " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("bcdUSB             : 0x" + UsbIoApp.shortToString((short)Desc.bcdUSB) + "\n");
		mainFrame.printOutput("bDeviceClass       : 0x" + UsbIoApp.byteToString((byte)Desc.bDeviceClass) + "\n");
		mainFrame.printOutput("bDeviceSubClass    : 0x" + UsbIoApp.byteToString((byte)Desc.bDeviceSubClass) + "\n");
		mainFrame.printOutput("bDeviceProtocol    : 0x" + UsbIoApp.byteToString((byte)Desc.bDeviceProtocol) + "\n");
		mainFrame.printOutput("bMaxPacketSize0    :   " + Desc.bMaxPacketSize0 + "\n");
		mainFrame.printOutput("idVendor           : 0x" + UsbIoApp.shortToString((short)Desc.idVendor) + "\n");
		mainFrame.printOutput("idProduct          : 0x" + UsbIoApp.shortToString((short)Desc.idProduct) + "\n");
		mainFrame.printOutput("bcdDevice          : 0x" + UsbIoApp.shortToString((short)Desc.bcdDevice) + "\n");
		mainFrame.printOutput("iManufacturer      :   " + Desc.iManufacturer + "\n");
		mainFrame.printOutput("iProduct           :   " + Desc.iProduct + "\n");
		mainFrame.printOutput("iSerialNumber      :   " + Desc.iSerialNumber + "\n");
		mainFrame.printOutput("bNumConfigurations :   " + Desc.bNumConfigurations + "\n");

	}

	void
	dumpConfigurationDescriptor(
	USB_CONFIGURATION_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("Configuration Descriptor:\n");
		mainFrame.printOutput("bLength            :   " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("wTotalLength       :   " + Desc.wTotalLength + "\n");
		mainFrame.printOutput("bNumInterfaces     :   " + Desc.bNumInterfaces + "\n");
		mainFrame.printOutput("bConfigurationValue:   " + Desc.bConfigurationValue + "\n");
		mainFrame.printOutput("iConfiguration     :   " + Desc.iConfiguration + "\n");
		mainFrame.printOutput("bmAttributes       : 0x" + UsbIoApp.byteToString((byte)Desc.bmAttributes) + "\n");
		mainFrame.printOutput("MaxPower           :   " + UsbIoApp.byteToString((byte)Desc.MaxPower) + "\n");
	}

	void
	dumpStringDescriptor(
	USB_STRING_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("String Descriptor:\n");
		mainFrame.printOutput("bLength            :   " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("DescriptorContents :   " + Desc.Str + "\n");
	}

	void
	dumpInterfaceDescriptor(
	USB_INTERFACE_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("Interface Descriptor:\n");
		mainFrame.printOutput("bLength            :   " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("bInterfaceNumber   :   " + Desc.bInterfaceNumber + "\n");
		mainFrame.printOutput("bAlternateSetting  :   " + Desc.bAlternateSetting + "\n");
		mainFrame.printOutput("bNumEndpoints      :   " + Desc.bNumEndpoints + "\n");
		mainFrame.printOutput("bInterfaceClass    : 0x" + UsbIoApp.byteToString((byte)Desc.bInterfaceClass) + "\n");
		mainFrame.printOutput("bInterfaceSubClass : 0x" + UsbIoApp.byteToString((byte)Desc.bInterfaceSubClass) + "\n");
		mainFrame.printOutput("bInterfaceProtocol : 0x" + UsbIoApp.byteToString((byte)Desc.bInterfaceProtocol) + "\n");
		mainFrame.printOutput("iInterface         :   " + Desc.iInterface + "\n");
	}

	void
	dumpHIDDescriptor(
	USB_HID_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("HID Descriptor:\n");
		mainFrame.printOutput("bLength            : " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("bcdHID             : 0x" + UsbIoApp.shortToString((short)Desc.bcdHID) + "\n");
		mainFrame.printOutput("bCountryCode       : 0x" + UsbIoApp.byteToString((byte)Desc.bCountryCode) + "\n");
		mainFrame.printOutput("bNumDescriptors    : 0x" + UsbIoApp.byteToString((byte)Desc.bNumDescriptors) + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType1) + "\n");
		mainFrame.printOutput("wDescriptorLength  : 0x" + UsbIoApp.shortToString((short)Desc.wDescriptorLength1) + "\n");
	}

	void
	dumpEndpointDescriptor(
	USB_ENDPOINT_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("Endpoint Descriptor:\n");
		mainFrame.printOutput("bLength            :   " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("bEndpointAddress   : 0x" + UsbIoApp.byteToString((byte)Desc.bEndpointAddress) + "\n");
		mainFrame.printOutput("bmAttributes       : 0x" + UsbIoApp.byteToString((byte)Desc.bmAttributes) + "\n");
		mainFrame.printOutput("wMaxPacketSize     :   " + Desc.wMaxPacketSize + "\n");
		mainFrame.printOutput("bInterval          :   " + Desc.bInterval + "\n");
	}

	void
	dumpDeviceQualifierDescriptor(
	USB_DEVICE_QUALIFIER_DESCRIPTOR Desc
	)
	{
		mainFrame.printOutput("\n");
		mainFrame.printOutput("Device Qualifier Descriptor:\n");
		mainFrame.printOutput("bLength            :   " + Desc.bLength + "\n");
		mainFrame.printOutput("bDescriptorType    : 0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
		mainFrame.printOutput("bcdUSB             : 0x" + UsbIoApp.shortToString((short)Desc.bcdUSB) + "\n");
		mainFrame.printOutput("bDeviceClass       : 0x" + UsbIoApp.byteToString((byte)Desc.bDeviceClass) + "\n");
		mainFrame.printOutput("bDeviceSubClass    : 0x" + UsbIoApp.byteToString((byte)Desc.bDeviceSubClass) + "\n");
		mainFrame.printOutput("bDeviceProtocol    : 0x" + UsbIoApp.byteToString((byte)Desc.bDeviceProtocol) + "\n");
		mainFrame.printOutput("bMaxPacketSize0    :   " + Desc.bMaxPacketSize0 + "\n");
		mainFrame.printOutput("bNumConfigurations :   " + Desc.bNumConfigurations + "\n");
		mainFrame.printOutput("bReserved          :   " + Desc.bReserved + "\n");
	}


	public void dumpDescriptor(USB_COMMON_DESCRIPTOR Desc) {
		int DescLength = Desc.bLength;
		if (DescLength == 0) {
			mainFrame.printOutput("Device returned a Zero packet (length=0) to the request.\n");
		} else {
			switch(Desc.bDescriptorType) {
				case UsbIo.USB_DEVICE_DESCRIPTOR_TYPE:
					dumpDeviceDescriptor((USB_DEVICE_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_CONFIGURATION_DESCRIPTOR_TYPE:
					dumpConfigurationDescriptor((USB_CONFIGURATION_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_STRING_DESCRIPTOR_TYPE:
					dumpStringDescriptor((USB_STRING_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_INTERFACE_DESCRIPTOR_TYPE:
					dumpInterfaceDescriptor((USB_INTERFACE_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_ENDPOINT_DESCRIPTOR_TYPE:
					dumpEndpointDescriptor((USB_ENDPOINT_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:
					dumpDeviceQualifierDescriptor((USB_DEVICE_QUALIFIER_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE:
					dumpConfigurationDescriptor((USB_CONFIGURATION_DESCRIPTOR)Desc);
					break;
				case UsbIo.USB_HID_DESCRIPTOR_TYPE:
					dumpHIDDescriptor((USB_HID_DESCRIPTOR)Desc);
					break;

				default:
					mainFrame.printOutput("\n");
					mainFrame.printOutput("Unknown Descriptor:\n");
					mainFrame.printOutput("Descriptor length:   " + DescLength + "\n");
					mainFrame.printOutput("Descriptor Type:   0x" + UsbIoApp.byteToString((byte)Desc.bDescriptorType) + "\n");
			}
		}
	}

}