package de.thesycon.usbio.structs;

/**
 * USB endpoint descriptor class.
 */
public class USB_ENDPOINT_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int SIZE = 7;

	/**
	 * Specifies the address of the endpoint on the USB device.
	 * <p>
	 * The endpoint address includes the direction flag at bit position 7 (MSB).
	 * <table>
	 * <tr><td>Bit 7 = 0:</td><td>OUT endpoint</td></tr>
	 * <tr><td>Bit 7 = 1:</td><td>IN endpoint</td></tr>
	 * </table>
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public int   bEndpointAddress;	// 8bit
	/** Specifies the endpoint type.*/
	public int   bmAttributes;		// 8bit
	/** Specifies the maximum packet size that can be sent from or to this endpoint.*/
	public int   wMaxPacketSize;	// 16bit
	/** Polling interval, in frames, for interrupt endpoints.*/
	public int   bInterval;			// 8bit

	/**
	 * Standard constructor of the USB_ENDPOINT_DESCRIPTOR class.
	 */
	public USB_ENDPOINT_DESCRIPTOR() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.bLength = Bytes[0];
			this.bDescriptorType = Bytes[1];
			this.bEndpointAddress = Bytes[2];
			this.bmAttributes = Bytes[3];
			this.wMaxPacketSize = (short)((Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.bInterval = Bytes[6];
		}
	}
}