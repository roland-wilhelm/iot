package de.thesycon.usbio.structs;

/**
 * The USBIO_ISO_TRANSFER data structure provides information about an
 * isochronous data transfer buffer.
 */
public class USBIO_ISO_TRANSFER extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 16;

	/**
	 * Specifies the number of packets to be sent to or to be received from the device.
	 * Each packet corresponds to a USB frame or a microframe respectively.
	 * The maximum number of packets allowed in a read or write operation is limited by the registry
	 * parameter MaxIsoPackets.
	 */
	public int    NumberOfPackets;
	/**
	 * This field contains zero or any combination (bit-wise or) of the following values.
	 * <ul>
	 * <li> USBIO_SHORT_TRANSFER_OK -
	 * If this flag is set then the USBIO driver does not return an error if a data
	 * packet received from the device is shorter than the maximum packet size
	 * of the endpoint.
	 * If this flag is not set then a short packet causes an error condition.
	 * <li> USBIO_START_TRANSFER_ASAP -
	 * If this flag is set then the transfer will be started as soon as possible
	 * and the StartFrame parameter is ignored.
	 * This flag has to be used if a continuous data stream shall be sent to the isochronous
	 * endpoint of the USB device.
	 * </ul>
	 */
	public int    Flags;
	/**
	 * Specifies the frame number or microframe number respectively at which the transfer is to be started.
	 * The value has to be within a system-defined range relative to the current frame.
	 * Normally, this range is set to 1024 frames.
	 * <br>
	 * If USBIO_START_TRANSFER_ASAP is not specified in Flags then
	 * StartFrame has to be initialized by the caller.
	 * The caller has to specify the frame number at which the first packet of the
	 * data transfer is to be transmitted.
	 * An error occurs if the frame number is not in the valid range, relative to
	 * the current frame number.
	 * <br>
	 * If USBIO_START_TRANSFER_ASAP is specified in Flags
	 * then the StartFrame value specified by the user will be ignored.
	 * After the transfer has been started and the write request has been completed
	 * the StartFrame field contains the frame number assigned to the first
	 * packet of the transfer.
	 */
	public int    StartFrame;
	/**
	 * After the isochronous read or write request has been completed by the USBIO driver
	 * this member contains the total number of errors occurred during the data transfer.
	 * In other words, ErrorCount specifies the number of frames that caused
	 * an error.
	 * This field can be used by an application to check if an isochronous read or write request
	 * has been completed successfully.
	 */
	public int    ErrorCount;

	/**
	 * Standard constructor of the USBIO_ISO_TRANSFER class.
	 */
	public USBIO_ISO_TRANSFER() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.NumberOfPackets = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.Flags = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.StartFrame = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.ErrorCount = (int)((Bytes[15] & 0xFF) << 24 | (Bytes[14] & 0xFF) << 16 | (Bytes[13] & 0xFF) << 8 | (Bytes[12] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((NumberOfPackets) & 0xFF);
		tempbuffer[1] = (byte) ((NumberOfPackets >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((NumberOfPackets >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((NumberOfPackets >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((Flags) & 0xFF);
		tempbuffer[5] = (byte) ((Flags >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((Flags >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((Flags >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((StartFrame) & 0xFF);
		tempbuffer[9] = (byte) ((StartFrame >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((StartFrame >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((StartFrame >> 24) & 0xFF);
		tempbuffer[12] = (byte) ((ErrorCount) & 0xFF);
		tempbuffer[13] = (byte) ((ErrorCount >> 8) & 0xFF);
		tempbuffer[14] = (byte) ((ErrorCount >> 16) & 0xFF);
		tempbuffer[15] = (byte) ((ErrorCount >> 24) & 0xFF);
		return tempbuffer;
	}
}