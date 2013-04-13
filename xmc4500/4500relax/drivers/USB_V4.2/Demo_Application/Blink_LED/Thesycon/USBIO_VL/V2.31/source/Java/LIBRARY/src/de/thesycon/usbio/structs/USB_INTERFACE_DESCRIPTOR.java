package de.thesycon.usbio.structs;

/**
 * USB interface descriptor class.
 */
public class USB_INTERFACE_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int SIZE = 9;

	/** Specifies the index number of this interface.*/
	public int   bInterfaceNumber;		// 8bit
	/** Specifies the alternate setting of this interface.*/
	public int   bAlternateSetting;		// 8bit
	/** Specifies the number of endpoints of this interface.*/
	public int   bNumEndpoints;			// 8bit
	/** Specifies the class code of the device.*/
	public int   bInterfaceClass;		// 8bit
	/** Specifies the subclass code of the device.*/
	public int   bInterfaceSubClass;	// 8bit
	/** Specifies the protocol code of the device.*/
	public int   bInterfaceProtocol;	// 8bit
	/** Specifies the index of a string descriptor that describes the interface.*/
	public int   iInterface;			// 8bit

	/**
	 * Standard constructor of the USB_INTERFACE_DESCRIPTOR class.
	 */
	public USB_INTERFACE_DESCRIPTOR() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.bLength = Bytes[0];
			this.bDescriptorType = Bytes[1];
			this.bInterfaceNumber = Bytes[2];
			this.bAlternateSetting = Bytes[3];
			this.bNumEndpoints = Bytes[4];
			this.bInterfaceClass = Bytes[5];
			this.bInterfaceSubClass = Bytes[6];
			this.bInterfaceProtocol = Bytes[7];
			this.iInterface = Bytes[8];
		}
	}
}