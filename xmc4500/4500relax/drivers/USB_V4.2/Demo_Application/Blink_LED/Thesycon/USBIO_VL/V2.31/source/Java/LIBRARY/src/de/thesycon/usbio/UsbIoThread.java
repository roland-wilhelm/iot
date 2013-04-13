package de.thesycon.usbio;

import java.util.LinkedList;

/** This class provides a basic implementation of a worker-thread
 * that is used to continuously perform I/O operations.
 * UsbIoThread is a base class for the UsbIoReader and
 * UsbIoWriter worker-thread implementations.
 * <p>
 * The UsbIoThread class contains pure virtual functions.
 * Consequently, it is not possible to create an instance of the class.
 * <p>
 * Note that UsbIoThread is derived from UsbIoPipe.
 * Thus, all USBIO functions can be executed
 * on an instance of UsbIoThread.
 */

public abstract class UsbIoThread extends UsbIoPipe implements Runnable {

	protected Thread T;
	protected UsbIoBufPool BufPool;
	protected LinkedList PendingList;
	protected int MaxErrorCount;

	/** Constructs a UsbIoThread object.
	 */
	public UsbIoThread() {
		BufPool = new UsbIoBufPool();
		PendingList = new LinkedList();
	}

	public abstract void processBuffer(UsbIoBuf Buf);

	public void processData(UsbIoBuf Buf) {
	}

	public abstract void bufErrorHandler(UsbIoBuf Buf);

	public abstract void onThreadExit();

	public abstract void run();

	/**
	 * Allocate the internal buffer pool.
	 * <p>
	 * The function initializes an internal UsbIoBufPool object.
	 * For more information on the parameters and the behavior of the
	 * function refer to the description of {@link de.thesycon.usbio.UsbIoBufPool#allocate(int, int) allocate}.
	 *
	 * @param SizeOfBuffer Specifies the size, in bytes, of the buffers to be allocated internally.
	 *
	 * @param NumberOfBuffers Specifies the number of buffers to be allocated internally.
	 *
	 * @return Returns <code>true</code> in case of success, <code>false</code> otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoThread#freeBuffers()
	 * @see de.thesycon.usbio.UsbIoBufPool#allocate(int, int)
	 */
	public boolean allocateBuffers(int SizeOfBuffer, int NumberOfBuffers) {
		return BufPool.allocate(SizeOfBuffer, NumberOfBuffers);
	}

	/**
	 * Free the internal buffer pool.
	 * <p>
	 * The function frees the buffers allocated by the internal
	 * UsbIoBufPool object.
	 * For more information on the behavior of the
	 * function refer to the description of {@link de.thesycon.usbio.UsbIoBufPool#free() free}.
	 *
	 * @see de.thesycon.usbio.UsbIoThread#allocateBuffers(int, int)
	 * @see de.thesycon.usbio.UsbIoBufPool#free()
	 */
	public void freeBuffers() {
		BufPool.free();
	}

	/**
	 * Start the internal worker-thread.
	 * <p>
	 * The internal worker-thread will be created.
	 * Possibly, it starts its execution before this function returns.
	 * <p>
	 * The error limit specified in MaxIoErrorCount prevents
	 * an end-less loop in the worker-thread
	 * that can occur when the device permanently fails data transfer requests.
	 * <p>
	 * The internal buffer pool must have been initialized by means of
	 * {@link de.thesycon.usbio.UsbIoThread#allocateBuffers(int, int) allocateBuffers} before this function is called.
	 *
	 * @param MaxIoErrorCount Specifies the maximum number of I/O errors caused by read or write
	 * operations that will be tolerated by the thread.
	 * The thread will terminate itself when the specified limit is reached.
	 *
	 * @see de.thesycon.usbio.UsbIoThread#allocateBuffers(int, int)
	 * @see de.thesycon.usbio.UsbIoThread#freeBuffers()
	 * @see de.thesycon.usbio.UsbIoThread#shutdownThread()
	 */
	public void startThread(int MaxIoErrorCount) {
		if (T == null) {
			MaxErrorCount = MaxIoErrorCount;
			T = new Thread(this);
			T.start();
		}
	}

	/**
	 * Terminate the internal worker-thread.
	 * <p>
	 * ShutdownThread blocks until the worker-thread has been terminated
	 * by the operating system.
	 * <p>
	 * It is not an error to call ShutdownThread when the internal thread
	 * is not started.
	 * The function does nothing in this case.
	 *
	 * @see de.thesycon.usbio.UsbIoThread#startThread(int)
	 */
	public void shutdownThread() {
		try {
			if (T != null) {
				abortPipe();
				T.interrupt();
				T.join();
				T = null;
				onThreadExit();
			}
		}
		catch (InterruptedException ex) {
		}
	}
}