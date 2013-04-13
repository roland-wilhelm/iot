package de.thesycon.usbio.structs;

/**
 * The USBIO_PIPE_CONTROL_TRANSFER class provides information used to
 * generate a specific control request.
 * The values defined by this structure are used to generate an eight byte
 * SETUP packet for a control endpoint.
 * However, it is not possible to generate a control transfer for the
 * default endpoint zero.
 * <p>
 * This structure provides the input parameters for the IOCTL_USBIO_PIPE_CONTROL_TRANSFER_IN
 * and the IOCTL_USBIO_PIPE_CONTROL_TRANSFER_OUT operation.
 */
public class USBIO_PIPE_CONTROL_TRANSFER extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 12;

	/**
	 * This field contains zero or the following value.
	 * <ul>
	 * <li> USBIO_SHORT_TRANSFER_OK -
	 * If this flag is set then the USBIO driver does not return an error if a data
	 * packet received from the device is shorter than the maximum packet size
	 * of the endpoint.
	 * If this flag is not set then a short packet causes an error condition.
	 * </ul>
	 */
	public int    Flags;
	/**
	 * Specifies the SETUP packet to be issued to the device.
	 * The format of the eight byte SETUP packet is defined by the
	 * Universal Serial Bus Specification 1.1, Chapter 9.
	 */
	public byte[] SetupPacket = new byte[8];

	/**
	 * Standard constructor of the USBIO_PIPE_CONTROL_TRANSFER class.
	 */
	public USBIO_PIPE_CONTROL_TRANSFER() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.Flags = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.SetupPacket[0] = Bytes[4];
			this.SetupPacket[1] = Bytes[5];
			this.SetupPacket[2] = Bytes[6];
			this.SetupPacket[3] = Bytes[7];
			this.SetupPacket[4] = Bytes[8];
			this.SetupPacket[5] = Bytes[9];
			this.SetupPacket[6] = Bytes[10];
			this.SetupPacket[7] = Bytes[11];
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((Flags) & 0xFF);
		tempbuffer[1] = (byte) ((Flags >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((Flags >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((Flags >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((SetupPacket[0]) & 0xFF);
		tempbuffer[5] = (byte) ((SetupPacket[1]) & 0xFF);
		tempbuffer[6] = (byte) ((SetupPacket[2]) & 0xFF);
		tempbuffer[7] = (byte) ((SetupPacket[3]) & 0xFF);
		tempbuffer[8] = (byte) ((SetupPacket[4]) & 0xFF);
		tempbuffer[9] = (byte) ((SetupPacket[5]) & 0xFF);
		tempbuffer[10] = (byte) ((SetupPacket[6]) & 0xFF);
		tempbuffer[11] = (byte) ((SetupPacket[7]) & 0xFF);
		return tempbuffer;
	}
}