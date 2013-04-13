package de.thesycon.usbio.structs;

/**
 * USB configuration descriptor class.
 */
public class USB_CONFIGURATION_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int SIZE = 9;

	/**
	 * Specifies the length, in bytes, of all data for the configuration.
	 * The length includes all endpoint, class, interface or vendor specific
	 * decriptors returned with the configuration descriptor.
	 */
	public int   wTotalLength;				// 16bit
	/**
	 * Total number of interfaces supported by this configuration.
	 */
	public int   bNumInterfaces;			// 8bit
	/**
	 * Index that identifies this USB configuration.
	 * 0 is unconfigured, 1 default configuration.
	 */
	public int   bConfigurationValue;		// 8bit
	/**
	 * Optional device defined index of the string descriptor for the configuration.
	 */
	public int   iConfiguration;			// 8bit
	/**
	 * Attributes of the configuration.
	 */
	public int   bmAttributes;				// 8bit
	/**
	 * Specifies the power requirements of the device.
	 */
	public int   MaxPower;					// 8bit

	/**
	 * Standard constructor of the USB_CONFIGURATION_DESCRIPTOR class.
	 */
	public USB_CONFIGURATION_DESCRIPTOR() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.bLength = Bytes[0];
			this.bDescriptorType = Bytes[1];
			this.wTotalLength = (short)((Bytes[3] & 0xFF) << 8 | (Bytes[2] & 0xFF));
			this.bNumInterfaces = Bytes[4];
			this.bConfigurationValue = Bytes[5];
			this.iConfiguration = Bytes[6];
			this.bmAttributes = Bytes[7];
			this.MaxPower = Bytes[8];
		}
	}
}