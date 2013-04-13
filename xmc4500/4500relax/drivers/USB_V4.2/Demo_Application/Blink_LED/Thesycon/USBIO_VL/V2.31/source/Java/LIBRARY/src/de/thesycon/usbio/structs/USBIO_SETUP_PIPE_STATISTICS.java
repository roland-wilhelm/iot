package de.thesycon.usbio.structs;

/**
 * The USBIO_SETUP_PIPE_STATISTICS class contains information used to configure
 * the statistics maintained by the USBIO driver for a pipe.
 */
public class USBIO_SETUP_PIPE_STATISTICS extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 12;

	/**
	 * Specifies the time interval, in milliseconds, that is used to calculate the average
	 * data rate of the pipe.
	 * A time averaging algorithm is used to continuously compute the mean value of the
	 * data transfer rate.
	 * The USBIO driver internally allocates memory to implement an averaging filter.
	 * There are 2048 bytes of memory required per second of the averaging interval.
	 * To limit the memory consumption the maximum supported value of
	 * AveragingInterval is 5000 milliseconds (5 seconds).
	 * If a longer interval is specified then the IOCTL_USBIO_SETUP_PIPE_STATISTICS
	 * request will fail with an error status of USBIO_ERR_INVALID_PARAMETER.
	 * It is recommended to use an averaging interval of 1000 milliseconds.
	 * <p>
	 * If AveragingInterval is set to zero then the average data rate
	 * computation is disabled.
	 * This is the default state.
	 * An application should only enable the average data rate computation if it is needed.
	 * This will save resources (kernel memory and CPU cycles).
	 * <p>
	 * See also IOCTL_USBIO_QUERY_PIPE_STATISTICS and USBIO_PIPE_STATISTICS
	 * for more information on pipe statistics.
	 */
	public int    AveragingInterval;
	/**
	 * This member is reserved for future use.
	 * It has to be set to zero.
	 */
	public int    reserved1;
	/**
	 * This member is reserved for future use.
	 * It has to be set to zero.
	 */
	public int    reserved2;

	/**
	 * Standard constructor of the USBIO_SETUP_PIPE_STATISTICS class.
	 */
	public USBIO_SETUP_PIPE_STATISTICS() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.AveragingInterval = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.reserved1 = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.reserved2 = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((AveragingInterval) & 0xFF);
		tempbuffer[1] = (byte) ((AveragingInterval >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((AveragingInterval >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((AveragingInterval >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((reserved1) & 0xFF);
		tempbuffer[5] = (byte) ((reserved1 >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((reserved1 >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((reserved1 >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((reserved2) & 0xFF);
		tempbuffer[9] = (byte) ((reserved2 >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((reserved2 >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((reserved2 >> 24) & 0xFF);
		return tempbuffer;
	}
}