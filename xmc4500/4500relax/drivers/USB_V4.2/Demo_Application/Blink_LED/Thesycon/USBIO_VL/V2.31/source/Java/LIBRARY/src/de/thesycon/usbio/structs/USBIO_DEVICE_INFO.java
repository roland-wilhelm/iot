package de.thesycon.usbio.structs;

/**
 * The USBIO_DEVICE_INFO class contains information on the USB device.
 * This structure returns the results of the IOCTL_USBIO_GET_DEVICE_INFO operation.
 */
public class USBIO_DEVICE_INFO extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 16;

	/**
	 * This field contains zero or any combination (bit-wise or) of the following values.
	 * <ul>
	 * <li>USBIO_DEVICE_INFOFLAG_HIGH_SPEED - If this flag is set then the USB device operates in high speed mode.
     * The USB 2.0 device is connected to a hub port that is high speed capable.<br>
     * Note that this flag does not indicate whether a device is capable of high speed
     * operation, but rather whether it is in fact operating at high speed.
	 * </ul>
	 */
	public int    Flags;
	/** This member is reserved for future use.*/
	public int    reserved1;
	/** This member is reserved for future use.*/
	public int    reserved2;
	/** This member is reserved for future use.*/
	public int    reserved3;

	/**
	 * Standard constructor of the USBIO_DEVICE_INFO class.
	 */
	public USBIO_DEVICE_INFO() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.Flags = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.reserved1 = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.reserved2 = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.reserved3 = (int)((Bytes[15] & 0xFF) << 24 | (Bytes[14] & 0xFF) << 16 | (Bytes[13] & 0xFF) << 8 | (Bytes[12] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((Flags) & 0xFF);
		tempbuffer[1] = (byte) ((Flags >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((Flags >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((Flags >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((reserved1) & 0xFF);
		tempbuffer[5] = (byte) ((reserved1 >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((reserved1 >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((reserved1 >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((reserved2) & 0xFF);
		tempbuffer[9] = (byte) ((reserved2 >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((reserved2 >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((reserved2 >> 24) & 0xFF);
		tempbuffer[12] = (byte) ((reserved3) & 0xFF);
		tempbuffer[13] = (byte) ((reserved3 >> 8) & 0xFF);
		tempbuffer[14] = (byte) ((reserved3 >> 16) & 0xFF);
		tempbuffer[15] = (byte) ((reserved3 >> 24) & 0xFF);
		return tempbuffer;
	}
}