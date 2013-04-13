package de.thesycon.usbio.structs;

/**
 * The USBIO_PIPE_PARAMETERS class contains USBIO driver settings related to a pipe.
 * This structure is intended to be used with the
 * IOCTL_USBIO_GET_PIPE_PARAMETERS and the IOCTL_USBIO_SET_PIPE_PARAMETERS operations.
 */
public class USBIO_PIPE_PARAMETERS extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 4;

	/**
	 * This field contains zero or the following value.
	 * <ul>
	 * <li> USBIO_SHORT_TRANSFER_OK -
	 * If this flag is set then the USBIO driver does not return an error during
	 * read operations from a Bulk or Interrupt pipe if a packet received from
	 * the device is shorter than the maximum packet size of the endpoint.
	 * If this flag is not set then a short packet causes an error condition.
	 * <br>
	 * Note that this option is meaningful for Bulk or Interrupt IN pipes only.
	 * It has an effect only for read operations from Bulk or Interrupt pipes.
	 * For Isochronous pipes the flags in the appropriate ISO data structures are used
	 * (see USBIO_ISO_TRANSFER).
	 * <br>
	 * The default state of the USBIO_SHORT_TRANSFER_OK flag is defined by the
	 * registry parameter ShortTransferOk.
	 * </ul>
	 */
	public int    Flags;

	/**
	 * Standard constructor of the USBIO_PIPE_PARAMETERS class.
	 */
	public USBIO_PIPE_PARAMETERS() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.Flags = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((Flags) & 0xFF);
		tempbuffer[1] = (byte) ((Flags >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((Flags >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((Flags >> 24) & 0xFF);
		return tempbuffer;
	}
}