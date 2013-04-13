package de.thesycon.usbio;
import java.util.*;

/**
 * This class implements a pool of UsbIoBuf objects.
 * It is used by UsbIoReader and UsbIoWriter
 * to simplify management of buffer pools.
 *
 * @author Thesycon
 * @version 2.0
 */
public class UsbIoBufPool {

	private UsbIoBuf[] BufArray;
	private int count;
	private Stack mStack;

	/**
	 * Allocate all elements of the buffer pool.
	 * <p>
	 * The function allocates the required number of buffer descriptors
	 * (UsbIoBuf objects).
	 * Then it allocates the specified amount of buffer memory.
	 * The total number of bytes to allocate is calculated as follows.
	 * <p>
	 * The function fails by returning <code>false</code> when an internal pool is already
	 * allocated.
	 *
	 * @param SizeOfBuffer Specifies the size, in bytes, of the buffers to be allocated internally.
	 *
	 * @param NumberOfBuffers Specifies the number of buffers to be allocated internally.
	 *
	 * @return Returns <code>true</code> in case of success, <code>false</code> otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoBufPool#free()
	*/
	public boolean allocate(int SizeOfBuffer, int NumberOfBuffers) {
		if (BufArray != null) {
			return false;
		}
		BufArray = new UsbIoBuf[NumberOfBuffers];
		count = NumberOfBuffers;
		mStack = new Stack();

		for (int i = 0 ; i < NumberOfBuffers ; i++) {
			BufArray[i] = new UsbIoBuf(SizeOfBuffer);
			//BufArray[i].BufferMem = new byte[SizeOfBuffer];
			//BufArray[i].Size = SizeOfBuffer;
			mStack.push(BufArray[i]);
		}
		return true;
	}

	/**
	 * Get current number of buffers in the pool.
	 *
	 * @return The function returns the current number of buffers stored in the pool.
	 *
	 * @see de.thesycon.usbio.UsbIoBufPool#get()
	 * @see de.thesycon.usbio.UsbIoBufPool#put(UsbIoBuf)
	*/
	public int getCurrentCount() {
		return count;
	}

	/**
	 * Get a buffer from the pool.
	 * <p>
	 * The function removes a buffer from the pool and returns a reference to the
	 * associated descriptor.
	 * The caller is responsible for releasing the buffer, see {@link de.thesycon.usbio.UsbIoBufPool#put(UsbIoBuf) put}.
	 *
	 * @return The function returns a reference to the buffer descriptor removed from
	 * the pool, or null if the pool is exhausted.
	 *
	 * @see de.thesycon.usbio.UsbIoBufPool#getCurrentCount()
	 * @see de.thesycon.usbio.UsbIoBufPool#put(UsbIoBuf)
	*/
	public UsbIoBuf get() {
		if (count>0) {
			count--;
			return (UsbIoBuf)mStack.pop();
		} else {
			return null;
		}
	}


	/**
	 * Put a buffer back to the pool.
	 * <p>
	 * This function is called to release a buffer that was
	 * returned by {@link de.thesycon.usbio.UsbIoBufPool#get() get}.
	 *
	 * @param Buf Reference to the buffer descriptor that was returned by {@link de.thesycon.usbio.UsbIoBufPool#get() get}.
	 *
	 * @see de.thesycon.usbio.UsbIoBufPool#getCurrentCount()
	 * @see de.thesycon.usbio.UsbIoBufPool#get()
	*/
	public void put(UsbIoBuf Buf) {
		if (Buf != null) {
			count++;
			mStack.push(Buf);
		}
	}


	/**
	 * Free all elements of the buffer pool.
	 * <p>
	 * The function frees all buffer descriptors and all the buffer
	 * memory allocated by a call to {@link de.thesycon.usbio.UsbIoBufPool#allocate(int, int) allocate}.
	 * The pool is empty after this call.
	 * <p>
	 * A call to Free on an empty pool is allowed.
	 * The function does nothing in this case.
	 * <p>
	 * Note that after a call to Free, another pool can be allocated by means of
	 * {@link de.thesycon.usbio.UsbIoBufPool#allocate(int, int) allocate}.
	 *
	 * @see de.thesycon.usbio.UsbIoBufPool#allocate(int, int)
	*/
	public void free() {
		mStack = null;
		BufArray = null;
	}
}