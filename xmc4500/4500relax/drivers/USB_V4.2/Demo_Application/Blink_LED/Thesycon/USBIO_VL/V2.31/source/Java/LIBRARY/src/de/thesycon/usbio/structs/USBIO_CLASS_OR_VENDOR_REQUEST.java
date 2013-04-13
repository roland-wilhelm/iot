package de.thesycon.usbio.structs;

/**
 * The USBIO_CLASS_OR_VENDOR_REQUEST class provides information used to
 * generate a class or vendor specific device request.
 * The values defined by this structure are used to generate an eight byte
 * SETUP packet for the default control endpoint (endpoint zero) of the device.
 * The format of the SETUP packet is defined by the Universal Serial Bus Specification 1.1,
 * Chapter 9.
 * The meaning of the values is defined by the device.
 * <p>
 * This structure provides the input parameters for the IOCTL_USBIO_CLASS_OR_VENDOR_IN_REQUEST
 * and the IOCTL_USBIO_CLASS_OR_VENDOR_OUT_REQUEST operation.
 */
public class USBIO_CLASS_OR_VENDOR_REQUEST extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 18;

	/**
	 * This field contains zero or the following value.
	 * <ul>
	 * <li>USBIO_SHORT_TRANSFER_OK -
	 * If this flag is set then the USBIO driver does not return an error if a data
	 * packet received from the device is shorter than the maximum packet size
	 * of the endpoint.
	 * If this flag is not set then a short packet causes an error condition.
	 * </ul>
     */
	public int    Flags;
	/** Specifies the type of the device request.*/
	public int    Type;
	/** Specifies the recipient of the device request.*/
	public int    Recipient;
	/** Specifies the reserved bits of the bmRequestType field of the SETUP packet.*/
	public byte   RequestTypeReservedBits;
	/** Specifies the value of the bRequest field of the SETUP packet.*/
	public byte   Request;
	/** Specifies the value of the wValue field of the SETUP packet.*/
	public short  Value;
	/** Specifies the value of the wIndex field of the SETUP packet.*/
	public short  Index;

	/**
	 * Standard constructor of the USBIO_CLASS_OR_VENDOR_REQUEST class.
	 */
	public USBIO_CLASS_OR_VENDOR_REQUEST() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.Flags = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.Type = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.Recipient = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.RequestTypeReservedBits = Bytes[12];
			this.Request = Bytes[13];
			this.Value = (short)((Bytes[15] & 0xFF) << 8 | (Bytes[14] & 0xFF));
			this.Index = (short)((Bytes[17] & 0xFF) << 8 | (Bytes[16] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((Flags) & 0xFF);
		tempbuffer[1] = (byte) ((Flags >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((Flags >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((Flags >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((Type) & 0xFF);
		tempbuffer[5] = (byte) ((Type >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((Type >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((Type >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((Recipient) & 0xFF);
		tempbuffer[9] = (byte) ((Recipient >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((Recipient >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((Recipient >> 24) & 0xFF);
		tempbuffer[12] = (byte) ((RequestTypeReservedBits) & 0xFF);
		tempbuffer[13] = (byte) ((Request) & 0xFF);
		tempbuffer[14] = (byte) ((Value) & 0xFF);
		tempbuffer[15] = (byte) ((Value >> 8) & 0xFF);
		tempbuffer[16] = (byte) ((Index) & 0xFF);
		tempbuffer[17] = (byte) ((Index >> 8) & 0xFF);
		return tempbuffer;
	}
}