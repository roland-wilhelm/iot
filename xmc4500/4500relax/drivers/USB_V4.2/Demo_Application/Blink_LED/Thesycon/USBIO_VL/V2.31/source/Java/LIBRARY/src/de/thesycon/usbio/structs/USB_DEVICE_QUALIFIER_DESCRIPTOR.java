package de.thesycon.usbio.structs;

/**
 * USB device qualifier descriptor class.
 */
public class USB_DEVICE_QUALIFIER_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int SIZE = 10;

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
	/** The number of possible configurations for the device.*/
	public int   bNumConfigurations;	// 8bit
	/**
	 * This member is reserved for future use.
	 * It has to be set to zero.
	 */
	public int   bReserved;				// 8bit

	/**
	 * Standard constructor of the USB_DEVICE_QUALIFIER_DESCRIPTOR class.
	 */
	public USB_DEVICE_QUALIFIER_DESCRIPTOR() {
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
			this.bNumConfigurations = Bytes[8];
			this.bReserved = Bytes[9];
		}
	}
}