package de.thesycon.usbio.structs;

/**
 * The USBIO_BANDWIDTH_INFO class contains information on the USB bandwidth consumption.
 * This structure returns the results of the IOCTL_USBIO_GET_BANDWIDTH_INFO operation.
 */
public class USBIO_BANDWIDTH_INFO extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 16;

	/** This field contains the total bandwidth, in kilobits per second, available on the bus.
	 * This bandwidth is provided by the USB host controller the device is connected to.
	 */
	public int    TotalBandwidth;
	/** This field contains the mean bandwidth that is already in use, in kilobits per second.*/
	public int    ConsumedBandwidth;
	/** This member is reserved for future use.*/
	public int    reserved1;
	/** This member is reserved for future use.*/
	public int    reserved2;

	/**
	 * Standard constructor of the USBIO_BANDWIDTH_INFO class.
	 */
	public USBIO_BANDWIDTH_INFO() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.TotalBandwidth = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.ConsumedBandwidth = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.reserved1 = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.reserved2 = (int)((Bytes[15] & 0xFF) << 24 | (Bytes[14] & 0xFF) << 16 | (Bytes[13] & 0xFF) << 8 | (Bytes[12] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((TotalBandwidth) & 0xFF);
		tempbuffer[1] = (byte) ((TotalBandwidth >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((TotalBandwidth >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((TotalBandwidth >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((ConsumedBandwidth) & 0xFF);
		tempbuffer[5] = (byte) ((ConsumedBandwidth >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((ConsumedBandwidth >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((ConsumedBandwidth >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((reserved1) & 0xFF);
		tempbuffer[9] = (byte) ((reserved1 >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((reserved1 >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((reserved1 >> 24) & 0xFF);
		tempbuffer[12] = (byte) ((reserved2) & 0xFF);
		tempbuffer[13] = (byte) ((reserved2 >> 8) & 0xFF);
		tempbuffer[14] = (byte) ((reserved2 >> 16) & 0xFF);
		tempbuffer[15] = (byte) ((reserved2 >> 24) & 0xFF);
		return tempbuffer;
	}
}