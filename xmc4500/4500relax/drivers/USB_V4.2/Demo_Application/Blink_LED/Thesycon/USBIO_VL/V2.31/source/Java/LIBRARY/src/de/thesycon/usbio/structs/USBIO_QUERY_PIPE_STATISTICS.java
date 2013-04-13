package de.thesycon.usbio.structs;

/**
 * The USBIO_QUERY_PIPE_STATISTICS class provides options that modify the behaviour
 * of the IOCTL_USBIO_QUERY_PIPE_STATISTICS operation.
 * This structure provides the input parameters for the IOCTL_USBIO_QUERY_PIPE_STATISTICS operation.
 * <p>
 * See also the description of the USBIO_PIPE_STATISTICS data structure
 * for more information on pipe statistics.
 */
public class USBIO_QUERY_PIPE_STATISTICS extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 4;

	/**
	 * This field contains zero or any combination (bit-wise or) of the following values.
	 * <ul>
	 * <li> USBIO_QPS_FLAG_RESET_BYTES_TRANSFERRED -
	 * If this flag is specified then the BytesTransferred counter will be reset to zero
	 * after its current value has been captured.
	 * The BytesTransferred counter is an unsigned 64 bit integer.
	 * It counts the total number of bytes transferred on a pipe, modulo 2^64.
	 * <li> USBIO_QPS_FLAG_RESET_REQUESTS_SUCCEEDED -
	 * If this flag is specified then the RequestsSucceeded counter will be reset to zero
	 * after its current value has been captured.
	 * The RequestsSucceeded counter is an unsigned 32 bit integer.
	 * It counts the total number of read or write requests that have been completed successfully
	 * on a pipe, modulo 2^32.
	 * <li> USBIO_QPS_FLAG_RESET_REQUESTS_FAILED -
	 * If this flag is specified then the RequestsFailed counter will be reset to zero
	 * after its current value has been captured.
	 * The RequestsFailed counter is an unsigned 32 bit integer.
	 * It counts the total number of read or write requests that have been completed with
	 * an error status on a pipe, modulo 2^32.
	 * <li> USBIO_QPS_FLAG_RESET_ALL_COUNTERS -
	 * This value combines the three flags described above.
	 * If USBIO_QPS_FLAG_RESET_ALL_COUNTERS is specified then all three counters
	 * BytesTransferred, RequestsSucceeded, and RequestsFailed
	 * will be reset to zero after their current values have been captured.
	 * </ul>
	 */
	public int    Flags;

	/**
	 * Standard constructor of the USBIO_QUERY_PIPE_STATISTICS class.
	 */
	public USBIO_QUERY_PIPE_STATISTICS() {
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