package de.thesycon.usbio.structs;

/**
 * The USBIO_PIPE_STATISTICS class contains statistical data related to a pipe.
 */
public class USBIO_PIPE_STATISTICS extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 32;

	/**
	 * A time averaging algorithm is used to continuously compute the mean value of the
	 * data transfer rate.
	 * This field specifies the actual time interval, in milliseconds, that was used to calculate the average
	 * data rate returned in AverageRate.
	 * Normally, this value corresponds to the interval that has been configured by means
	 * of the IOCTL_USBIO_SETUP_PIPE_STATISTICS operation.
	 * However, if the capacity of the internal averaging filter is not sufficient for the
	 * interval set then ActualAveragingInterval can be less than the
	 * averaging interval that has been configured.
	 * <p>
	 * If ActualAveragingInterval is zero then the data rate computation is disabled.
	 * The AverageRate field of this structure is always set to zero in this case.
	 */
	public int    ActualAveragingInterval;  // in ms, 0 = statistics off
	/**
	 * Specifies the current average data rate of the pipe, in bytes per second.
	 * The average data rate will be continuously calculated if the ActualAveragingInterval
	 * field of this structure is not null.
	 * If ActualAveragingInterval is null then the data rate computation is disabled and
	 * this field is always set to zero.
	 * <p>
	 * The computation of the average data rate has to be enabled and to be configured
	 * explicitly by an application.
	 * This has to be done by means of the IOCTL_USBIO_SETUP_PIPE_STATISTICS request.
	 */
	public int    AverageRate;              // in bytes/s
	/**
	 * Specifies the lower 32 bits of the current value of the BytesTransferred counter.
	 * The BytesTransferred counter is an unsigned 64 bit integer.
	 * It counts the total number of bytes transferred on a pipe, modulo 2^64.
	 */
	public int    BytesTransferred_L; // total number of bytes transferred, lower 32 bits
	/**
	 * Specifies the upper 32 bits of the current value of the BytesTransferred counter.
	 * The BytesTransferred counter is an unsigned 64 bit integer.
	 * It counts the total number of bytes transferred on a pipe, modulo 2^64.
	 */
	public int    BytesTransferred_H; // total number of bytes transferred, upper 32 bits
	/**
	 * Specifies the current value of the RequestsSucceeded counter.
	 * The RequestsSucceeded counter is an unsigned 32 bit integer.
	 * It counts the total number of read or write requests that have been completed successfully
	 * on a pipe, modulo 2^32.
	 * <p>
	 * On a bulk or interrupt pipe the term request corresponds to a buffer that is submitted
	 * to perform a read or write operation.
	 * Thus, this counter will be incremented by one for each buffer that was successfully transferred.
	 * <p>
	 * On an isochronous pipe the term request corresponds to an isochronous data frame.
	 * Each buffer that is submitted to perform a read or write operation contains several isochronous data frames.
	 * This counter will be incremented by one for each isochronous data frame that was successfully transferred.
	 */
	public int    RequestsSucceeded;  // total number of I/O requests succeeded
	/**
	 * Specifies the current value of the RequestsFailed counter.
	 * The RequestsFailed counter is an unsigned 32 bit integer.
	 * It counts the total number of read or write requests that have been completed with
	 * an error status on a pipe, modulo 2^32.
	 * <p>
	 * On a bulk or interrupt pipe the term request corresponds to a buffer that is submitted
	 * to perform a read or write operation.
	 * Thus, this counter will be incremented by one for each buffer that is completed with an error status.
	 * <p>
	 * On an isochronous pipe the term request corresponds to an isochronous data frame.
	 * Each buffer that is submitted to perform a read or write operation contains several isochronous data frames.
	 * This counter will be incremented by one for each isochronous data frame that is completed with an error status.
	 */
	public int    RequestsFailed;     // total number of I/O requests failed
	/** This member is reserved for future use.*/
	public int    reserved1;          // reserved for future use
	/** This member is reserved for future use.*/
	public int    reserved2;          // reserved for future use

	/**
	 * Standard constructor of the USBIO_PIPE_STATISTICS class.
	 */
	public USBIO_PIPE_STATISTICS() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.ActualAveragingInterval = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.AverageRate = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.BytesTransferred_L = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
			this.BytesTransferred_H = (int)((Bytes[15] & 0xFF) << 24 | (Bytes[14] & 0xFF) << 16 | (Bytes[13] & 0xFF) << 8 | (Bytes[12] & 0xFF));
			this.RequestsSucceeded = (int)((Bytes[19] & 0xFF) << 24 | (Bytes[18] & 0xFF) << 16 | (Bytes[17] & 0xFF) << 8 | (Bytes[16] & 0xFF));
			this.RequestsFailed = (int)((Bytes[23] & 0xFF) << 24 | (Bytes[22] & 0xFF) << 16 | (Bytes[21] & 0xFF) << 8 | (Bytes[20] & 0xFF));
			this.reserved1 = (int)((Bytes[27] & 0xFF) << 24 | (Bytes[26] & 0xFF) << 16 | (Bytes[25] & 0xFF) << 8 | (Bytes[24] & 0xFF));
			this.reserved2 = (int)((Bytes[31] & 0xFF) << 24 | (Bytes[30] & 0xFF) << 16 | (Bytes[29] & 0xFF) << 8 | (Bytes[28] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((ActualAveragingInterval) & 0xFF);
		tempbuffer[1] = (byte) ((ActualAveragingInterval >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((ActualAveragingInterval >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((ActualAveragingInterval >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((AverageRate) & 0xFF);
		tempbuffer[5] = (byte) ((AverageRate >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((AverageRate >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((AverageRate >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((BytesTransferred_L) & 0xFF);
		tempbuffer[9] = (byte) ((BytesTransferred_L >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((BytesTransferred_L >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((BytesTransferred_L >> 24) & 0xFF);
		tempbuffer[12] = (byte) ((BytesTransferred_H) & 0xFF);
		tempbuffer[13] = (byte) ((BytesTransferred_H >> 8) & 0xFF);
		tempbuffer[14] = (byte) ((BytesTransferred_H >> 16) & 0xFF);
		tempbuffer[15] = (byte) ((BytesTransferred_H >> 24) & 0xFF);
		tempbuffer[16] = (byte) ((RequestsSucceeded) & 0xFF);
		tempbuffer[17] = (byte) ((RequestsSucceeded >> 8) & 0xFF);
		tempbuffer[18] = (byte) ((RequestsSucceeded >> 16) & 0xFF);
		tempbuffer[19] = (byte) ((RequestsSucceeded >> 24) & 0xFF);
		tempbuffer[20] = (byte) ((RequestsFailed) & 0xFF);
		tempbuffer[21] = (byte) ((RequestsFailed >> 8) & 0xFF);
		tempbuffer[22] = (byte) ((RequestsFailed >> 16) & 0xFF);
		tempbuffer[23] = (byte) ((RequestsFailed >> 24) & 0xFF);
		tempbuffer[24] = (byte) ((reserved1) & 0xFF);
		tempbuffer[25] = (byte) ((reserved1 >> 8) & 0xFF);
		tempbuffer[26] = (byte) ((reserved1 >> 16) & 0xFF);
		tempbuffer[27] = (byte) ((reserved1 >> 24) & 0xFF);
		tempbuffer[28] = (byte) ((reserved2) & 0xFF);
		tempbuffer[29] = (byte) ((reserved2 >> 8) & 0xFF);
		tempbuffer[30] = (byte) ((reserved2 >> 16) & 0xFF);
		tempbuffer[31] = (byte) ((reserved2 >> 24) & 0xFF);
		return tempbuffer;
	}
}