package de.thesycon.usbio.structs;

/**
 * The USBIO_PIPE_CONFIGURATION_INFO class provides information about a pipe.
 * This structure returns results of the IOCTL_USBIO_GET_CONFIGURATION_INFO operation.
 * It is a substructure within the USBIO_CONFIGURATION_INFO structure.
 */
public class USBIO_PIPE_CONFIGURATION_INFO extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 16;

	/**
	 * Specifies the type of the pipe.
	 */
	public int    PipeType;  // type
	/**
	 * Specifies the maximum size, in bytes, of data transfers the
	 * USB bus driver USBD supports on this pipe.
	 * This is the maximum size of buffers that can be used with read or write
	 * operations on this pipe.
	 */
	public int    MaximumTransferSize;// maximum Read/Write buffer size
	/**
	 * Specifies the maximum packet size of USB data transfers the endpoint is
	 * capable of sending or receiving.
	 * This is also referred to as FIFO size.
	 * The MaximumPacketSize value is reported by the device in the
	 * corresponding endpoint descriptor.
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public short  MaximumPacketSize;  // FIFO size of the endpoint
	/**
	 * Specifies the address of the endpoint on the USB device as reported in
	 * the corresponding endpoint descriptor.
	 * <p>
	 * The endpoint address includes the direction flag at bit position 7 (MSB).
	 * <table>
	 * <tr><td>Bit 7 = 0:</td><td>OUT endpoint</td></tr>
	 * <tr><td>Bit 7 = 1:</td><td>IN endpoint</td></tr>
	 * </table>
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public byte   EndpointAddress;    // including direction bit (bit 7)
	/**
	 * Specifies the interval, in milliseconds, for polling the endpoint for
	 * data as reported in the corresponding endpoint descriptor.
	 * This value is meaningful for interrupt endpoints only.
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public byte   Interval;           // in ms, for interrupt pipe
	/**
	 * Specifies the index of the interface the pipe belongs to.
	 * The value is equal to the field InterfaceNumber of the corresponding
	 * USBIO_INTERFACE_CONFIGURATION_INFO structure.
	 */
	public byte   InterfaceNumber;    // interface that the EP belongs to
	/** Reserved field, set to zero.*/
	public byte   reserved1;   // reserved field, set to zero
	/** Reserved field, set to zero.*/
	public byte   reserved2;   // reserved field, set to zero
	/** Reserved field, set to zero.*/
	public byte   reserved3;   // reserved field, set to zero

	/**
	 * Standard constructor of the USBIO_PIPE_CONFIGURATION_INFO class.
	 */
	public USBIO_PIPE_CONFIGURATION_INFO() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.PipeType = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.MaximumTransferSize = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.MaximumPacketSize = (short)((Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.EndpointAddress = Bytes[10];
			this.Interval = Bytes[11];
			this.InterfaceNumber = Bytes[12];
			this.reserved1 = Bytes[13];
			this.reserved2 = Bytes[14];
			this.reserved3 = Bytes[15];
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((PipeType) & 0xFF);
		tempbuffer[1] = (byte) ((PipeType >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((PipeType >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((PipeType >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((MaximumTransferSize) & 0xFF);
		tempbuffer[5] = (byte) ((MaximumTransferSize >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((MaximumTransferSize >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((MaximumTransferSize >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((MaximumPacketSize) & 0xFF);
		tempbuffer[9] = (byte) ((MaximumPacketSize >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((EndpointAddress) & 0xFF);
		tempbuffer[11] = (byte) ((Interval) & 0xFF);
		tempbuffer[12] = (byte) ((InterfaceNumber) & 0xFF);
		tempbuffer[13] = (byte) ((reserved1) & 0xFF);
		tempbuffer[14] = (byte) ((reserved2) & 0xFF);
		tempbuffer[15] = (byte) ((reserved3) & 0xFF);
		return tempbuffer;
	}
}