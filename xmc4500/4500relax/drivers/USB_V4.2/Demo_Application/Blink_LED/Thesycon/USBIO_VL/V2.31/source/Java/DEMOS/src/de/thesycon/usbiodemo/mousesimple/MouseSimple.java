package de.thesycon.usbiodemo.mousesimple;
import de.thesycon.usbio.UsbIo;
import de.thesycon.usbio.UsbIoErrorCodes;
import de.thesycon.usbio.UsbIoInterface;
import de.thesycon.usbio.UsbIoPipe;
import de.thesycon.usbio.structs.USBIO_CONFIGURATION_INFO;
import de.thesycon.usbio.structs.USBIO_DATA_BUFFER;
import de.thesycon.usbio.structs.USBIO_SET_CONFIGURATION;
import de.thesycon.usbio.structs.USB_DEVICE_DESCRIPTOR;
import de.thesycon.usbio.structs.USB_STRING_DESCRIPTOR;

public class MouseSimple implements UsbIoErrorCodes {

	// consts
	public final static short CONFIG_INDEX                       = 0;
	public final static short CONFIG_NB_OF_INTERFACES            = 1;
	public final static short CONFIG_INTERFACE                   = 0;
	public final static short CONFIG_ALT_SETTING                 = 0;
	public final static int CONFIG_TRAN_SIZE                     = 4096;

	// default driver guid
	String guid = "{325ddf96-938c-11d3-9e34-0080c82727f4}";

	int Status;
	UsbIo gUsbIo;
	UsbIoPipe gUsbIoPipe;
	int gDevList;

	public static void main(String args[])
	{
		MouseSimple test = new MouseSimple();
		test.start();
	}

	public void start()
	{
		// create a instance of UsbIo object
		gUsbIo = new UsbIo();

		gDevList = UsbIo.createDeviceList(guid);

		// open device
		Status = gUsbIo.open(0,gDevList,guid);
		if (Status != USBIO_ERR_SUCCESS) {
			System.out.println("Open: "+UsbIo.errorText(Status));
			UsbIo.destroyDeviceList(gDevList);
			return;
		} else {
			System.out.println("OPEN Device ok");
		}

		// get device descriptor
		USB_DEVICE_DESCRIPTOR desc = new USB_DEVICE_DESCRIPTOR();
		Status = gUsbIo.getDeviceDescriptor(desc);
		if (Status != USBIO_ERR_SUCCESS) {
			System.out.println("GetDeviceDescriptor: "+UsbIo.errorText(Status));
			UsbIo.destroyDeviceList(gDevList);
			return;
		} else {
			System.out.println("GetDeviceDescriptor: 0x" + intToString(desc.idVendor) + " 0x" + intToString(desc.idProduct));
		}

		// get string descriptor
		USB_STRING_DESCRIPTOR StrDesc = new USB_STRING_DESCRIPTOR();
		Status = gUsbIo.getStringDescriptor(StrDesc,(byte)1,0);
		if (Status != USBIO_ERR_SUCCESS) {
			System.out.println("GetStringDescriptor: "+UsbIo.errorText(Status));
			UsbIo.destroyDeviceList(gDevList);
			return;
		} else {
			System.out.println("GetStringDescriptor: " + StrDesc.Str);
		}

		// set configuration
		USBIO_SET_CONFIGURATION Conf = new USBIO_SET_CONFIGURATION();
		Conf.ConfigurationIndex = CONFIG_INDEX;
		Conf.NbOfInterfaces = CONFIG_NB_OF_INTERFACES;
		Conf.InterfaceList[0].InterfaceIndex = CONFIG_INTERFACE;
		Conf.InterfaceList[0].AlternateSettingIndex = CONFIG_ALT_SETTING;
		Conf.InterfaceList[0].MaximumTransferSize = CONFIG_TRAN_SIZE;
		Status = gUsbIo.setConfiguration(Conf);
		if (Status != USBIO_ERR_SUCCESS) {
			System.out.println("SetConfiguration: "+UsbIo.errorText(Status));
			UsbIo.destroyDeviceList(gDevList);
			return;
		} else {
			System.out.println("SetConfiguration ok");
		}

		// get pipe information and extract the FIFO size
		USBIO_CONFIGURATION_INFO ConfigurationInfo = new USBIO_CONFIGURATION_INFO();
		Status = gUsbIo.getConfigurationInfo(ConfigurationInfo);
		if (Status != USBIO_ERR_SUCCESS) {
			System.out.println("GetConfigurationInfo: "+UsbIo.errorText(Status));
			UsbIo.destroyDeviceList(gDevList);
			return;
		} else {
			System.out.println("GetConfigurationInfo ok");
		}
		if (ConfigurationInfo.NbOfPipes != 1) {
			System.out.println("Device has more than one endpoint, it is not a mouse");
			UsbIo.destroyDeviceList(gDevList);
			return;
		}

		int FifoSize = ConfigurationInfo.PipeInfo[0].MaximumPacketSize;
		byte EndpointAddress = ConfigurationInfo.PipeInfo[0].EndpointAddress;

		
		// bind pipe
		gUsbIoPipe = new UsbIoPipe();
		Status = gUsbIoPipe.bind(0,EndpointAddress,gDevList,guid);
		if (Status != USBIO_ERR_SUCCESS) {
			System.out.println("Bind: "+UsbIo.errorText(Status));
			UsbIo.destroyDeviceList(gDevList);
			return;
		} else {
			System.out.println("Bind ok");
		}

		// test readSYNC ....
		boolean BothMouseButtonsPressed = false;
		USBIO_DATA_BUFFER BufDesc = new USBIO_DATA_BUFFER(FifoSize);
		BufDesc.setNumberOfBytesToTransfer(FifoSize);
		System.out.println("Move mouse! Press both mouse buttons to stop");
		while (!BothMouseButtonsPressed) {
			Status = gUsbIoPipe.readSync(BufDesc,UsbIoInterface.INFINITE);
			if (Status != USBIO_ERR_SUCCESS) {
				System.out.println("Status: "+UsbIo.errorText(Status));
				BothMouseButtonsPressed = true;
			} else {
				if (BufDesc.getBytesTransferred() > 0) {
					for (int i = 0;i<BufDesc.getBytesTransferred();i++) {
						System.out.print(byteToString(BufDesc.Buffer()[i]) + "  ");
						if (i%16 == 15) {
							System.out.println();
						}
					}
					System.out.println();
				}
				BothMouseButtonsPressed = (BufDesc.Buffer()[0] == 3);
			}
		}

		// unbind pipe
		gUsbIoPipe.unbind();

		// close device
		gUsbIoPipe.close();
		gUsbIo.close();
	}

	// helper functions

    private static final char[] HEX_DIGITS = {
		'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
    };

    public static String byteToString (byte n) {
		char[] buf = new char[2];
		for(int i = 1; i >= 0; i--) {
			buf[i] = HEX_DIGITS[n & 0x0F];
			n >>>= 4;
		}
		return new String(buf);
    }

	public static String intToString (int n) {
		char[] buf = new char[8];
		for(int i = 7; i >= 0; i--) {
			buf[i] = HEX_DIGITS[n & 0x0F];
			n >>>= 4;
		}
		return new String(buf);
	}
}
