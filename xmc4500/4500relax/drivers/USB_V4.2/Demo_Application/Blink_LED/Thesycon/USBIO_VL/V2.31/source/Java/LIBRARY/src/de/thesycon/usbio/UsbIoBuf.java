package de.thesycon.usbio;

/**
 * This class is used as a buffer descriptor of
 * buffers used for read and write operations.
 *
 * @author Thesycon
 * @version 2.0
 */
public class UsbIoBuf {

	protected int Handle;

	/**
	 * Reference to the Buffer.
	 */
	public byte[] BufferMem;

	/**
	 * This public member contains the size, in bytes, of the memory block that is attached to
	 * the UsbIoBuf object.
	 * The value is zero if no memory block is attached.
	 */
	public int Size;

	/** This public member indicates the completion status of
	 * a read or write operation.
	 * <p>
	 * Note that this member will be set after a read or write operation
	 * is completed.
	 */
	public int Status;

	/** This public member specifies the number of bytes to be transferred
	 * to or from the buffer in a subsequent read or write operation.
	 * <p>
	 * Note that this member has to be set before the read or write operation
	 * is initiated by means of {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write}.
	 */
	public int NumberOfBytesToTransfer;

	/** This public member indicates the number of bytes successfully transferred
	 * to or from the buffer during a read or write operation.
	 * <p>
	 * Note that this member will be set after a read or write operation
	 * is completed.
	 */
	public int BytesTransferred;

	/**
	 * This public member is used as a flag.
	 * If it is set to <code>true</code> then it indicates that the
	 * data transfer operation is finished altogether.
	 * Read or write processing will be terminated by
	 * UsbIoReader or UsbIoWriter.
	 */
	public boolean OperationFinished;

	/**
	 * Construct a UsbIoBuf object and allocate a buffer internally.
	 *
	 * @param Size Specifies the size, in bytes, of the buffer
	 * to be allocated and attached to the descriptor object.
	 */
	public UsbIoBuf(int Size) {
		BufferMem = new byte[Size];
		this.Size = Size;
	}
}