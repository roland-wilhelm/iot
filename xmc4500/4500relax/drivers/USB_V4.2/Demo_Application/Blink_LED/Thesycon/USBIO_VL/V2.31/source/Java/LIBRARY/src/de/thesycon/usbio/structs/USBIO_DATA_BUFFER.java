package de.thesycon.usbio.structs;

/**
 * The USBIO_DATA_BUFFER class is used for buffer input/output operations
 * with the UsbIo Java Interface.
 */
public class USBIO_DATA_BUFFER
{
	protected int[] buffersize = new int[1];
	protected int[] BytesTransferred = new int[1];
	protected int[] NumberOfBytesToTransfer = new int[1];
	protected byte[] bufferarray;

	/**
	 * Construct a USBIO_DATA_BUFFER object and allocate a buffer internally.
	 *
	 * @param size Specifies the size, in bytes, of the buffer
	 * to be allocated and attached to the descriptor object.
	 */
	public USBIO_DATA_BUFFER (int size) {
		this.setSize(size);
	}

	/**
	 * Get a Reference to the Buffer.
	 */
	public byte[] Buffer() {
		return this.bufferarray;
	}

	/**
	 * This function indicates the number of bytes successfully transferred
	 * to or from the buffer during a read or write operation.
	 * <p>
	 * Note that this member will be set after a read or write operation
	 * is completed.
	 */
	public int getBytesTransferred() {
		return this.BytesTransferred[0];
	}

	/**
	 * This function is used internally to set the number of transferred bytes.
	 *
	 * @param BytesTransferred Number of transferred bytes.
	 */
	public void setBytesTransferred(int BytesTransferred) {
		this.BytesTransferred[0] = BytesTransferred;
	}

	/**
	 * This function returns the number of bytes to be transferred
	 * to or from the buffer in a subsequent read or write operation.
	 */
	public int getNumberOfBytesToTransfer() {
		return this.NumberOfBytesToTransfer[0];
	}

	/**
	 * This function returns sets the number of bytes to transfer.
	 *
	 * @param NumberOfBytesToTransfer Number of bytes to transfer.
	 */
	public void setNumberOfBytesToTransfer(int NumberOfBytesToTransfer) {
		this.NumberOfBytesToTransfer[0] = NumberOfBytesToTransfer;
	}

	/**
	 * Get the size of the internal buffer.
	 */
	public int getSize() {
		return this.buffersize[0];
	}

	/**
	 * Set the size of the internal buffer.
	 *
	 * @param size Size of the internal buffer.
	 */
	public void setSize(int size) {
		this.bufferarray = new byte[size];
		this.buffersize[0] = size;
		this.BytesTransferred[0] = 0;
		this.NumberOfBytesToTransfer[0] = 0;
	}
}