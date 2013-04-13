package de.thesycon.usbio.structs;

/**
 * USB HID descriptor class.
 */
public class USB_HID_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int SIZE = 9;

	/** HID class*/
	public int  bcdHID;				// 16bit
	/** Country code*/
	public int  bCountryCode;		// 8bit
	/** Number of class descriptors.*/
	public int  bNumDescriptors;	// 8bit
	/** Type of the decriptor*/
	public int  bDescriptorType1;	// 8bit
	/** Length of the descriptor*/
	public int  wDescriptorLength1;	// 16bit

	/**
	 * Standard constructor of the USB_HID_DESCRIPTOR class.
	 */
	public USB_HID_DESCRIPTOR() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.bLength = Bytes[0];
			this.bDescriptorType = Bytes[1];
			this.bcdHID = (short)((Bytes[3] & 0xFF) << 8 | (Bytes[2] & 0xFF));
			this.bCountryCode = Bytes[4];
			this.bNumDescriptors = Bytes[5];
			this.bDescriptorType1 = Bytes[6];
			this.wDescriptorLength1 = (short)((Bytes[8] & 0xFF) << 8 | (Bytes[7] & 0xFF));
		}
	}
}