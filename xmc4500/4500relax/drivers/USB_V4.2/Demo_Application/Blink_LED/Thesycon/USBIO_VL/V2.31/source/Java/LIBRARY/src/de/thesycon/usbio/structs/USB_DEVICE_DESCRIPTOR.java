package de.thesycon.usbio.structs;

/**
 * USB device descriptor class.
 */
public class USB_DEVICE_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int SIZE = 18;

	/** Identifies the version of the USB spec. The value is in BCD code.*/
	public int   bcdUSB;				// 16bit
	/** Specifies the class code of the device.*/
	public int   bDeviceClass;			// 8bit
	/** Specifies the subclass code of the device.*/
	public int   bDeviceSubClass;		// 8bit
	/** Specifies the protocol code of the device.*/
	public int   bDeviceProtocol;		// 8bit
	/** Specifies the maximum packet size for endpoint 0x00.*/
	public int   bMaxPacketSize0;		// 8bit
	/** Specifies the vendor ID of the device.*/
	public int   idVendor;				// 16bit
	/** Specifies the product ID.*/
	public int   idProduct;				// 16bit
	/** Identifies the version of the device. The value is in BCD code.*/
	public int   bcdDevice;				// 16bit
	/** Specifies a device-defined index of the string descriptor that provides a string containing the name of the manufacturer of this device.*/
	public int   iManufacturer;			// 8bit
	/** Specifies a device-defined index of the string descriptor that provides a string that contains a description of the device.*/
	public int   iProduct;				// 8bit
	/** Specifies a device-defined index of the string descriptor that provides a string that contains a manufacturer-determined serial number for the device.*/
	public int   iSerialNumber;			// 8bit
	/** The number of possible configurations for the device.*/
	public int   bNumConfigurations;	// 8bit

	/**
	 * Standard constructor of the USB_DEVICE_DESCRIPTOR class.
	 */
	public USB_DEVICE_DESCRIPTOR() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.bLength = Bytes[0];
			this.bDescriptorType = Bytes[1];
			this.bcdUSB = (short)((Bytes[3] & 0xFF) << 8 | (Bytes[2] & 0xFF));
			this.bDeviceClass = Bytes[4];
			this.bDeviceSubClass = Bytes[5];
			this.bDeviceProtocol = Bytes[6];
			this.bMaxPacketSize0 = Bytes[7];
			this.idVendor = (short)((Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.idProduct = (short)((Bytes[11] & 0xFF) << 8 | (Bytes[10] & 0xFF));
			this.bcdDevice = (short)((Bytes[13] & 0xFF) << 8 | (Bytes[12] & 0xFF));
			this.iManufacturer = Bytes[14];
			this.iProduct = Bytes[15];
			this.iSerialNumber = Bytes[16];
			this.bNumConfigurations = Bytes[17];
		}
	}
}