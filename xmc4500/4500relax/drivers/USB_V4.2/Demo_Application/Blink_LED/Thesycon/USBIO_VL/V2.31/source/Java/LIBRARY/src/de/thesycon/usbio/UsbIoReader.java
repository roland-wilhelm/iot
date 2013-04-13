package de.thesycon.usbio;

/**
 * This class implements a worker-thread that
 * continuously reads a data stream from a pipe.
 * <p>
 * Note that this class is derived from UsbIoThread which
 * provides the basic handling of the internal worker-thread.
 *
 * @author Thesycon
 * @version 2.0
 */
public abstract class UsbIoReader extends UsbIoThread {

	/** Constructs a UsbIoReader object.
	 */
	public UsbIoReader() {
		super();
	}

	/** The main routine that is executed by the worker-thread.
	 * <p>
	 * This function implements the main loop of the worker-thread.
	 * It submits all buffers from the internal buffer pool to the driver
	 * and waits for the completion of the first buffer.
	 * <p>
	 * ThreadRoutine can be overloaded by a derived class to implement
	 * a different behavior.
	 */
	public void run() {
		UsbIoBuf Buf;
		int Status;
		int ErrorCounter=0;

		if ( BufPool.getCurrentCount() == 0 ) {
			// no BufPool is allocated !
			return;
		}

		while (!Thread.interrupted()) {

			if ( ErrorCounter > MaxErrorCount ) {
				// max number of io errors reached
				break;
			}
			// submit all available buffers to the driver
			Buf = BufPool.get();
			while (Buf != null) {
				// get transfer count
				processBuffer(Buf);
				if ((!Buf.OperationFinished) && (Buf.NumberOfBytesToTransfer > 0)) {
					// issue read request
					read(Buf);
					// chain buffer to pending list
					PendingList.add(Buf);
				} else {
					BufPool.put(Buf);
					break;
				}
				Buf = BufPool.get();
			}
			if (PendingList.size()==0) {
				// no pending request, break loop
				break;
			}
			// wait for completion on the first pending buffer
			Buf = (UsbIoBuf)PendingList.getFirst();
			Status = waitForCompletion(Buf); //INFINITE
			if (Status != USBIO_ERR_SUCCESS) {
				if (Status != USBIO_ERR_POWER_DOWN) {
					ErrorCounter++;
				}
				bufErrorHandler(Buf);
			} else {
				ErrorCounter = 0;
			}
			// remove buffer from pending list
			PendingList.removeFirst();
			// process data
			processData(Buf);
			// put the buffer back to pool
			BufPool.put(Buf);
		}
		// wait for all pending buffers to complete
		while (PendingList.size()>0) {
			Buf = (UsbIoBuf)PendingList.getFirst();
			Status = waitForCompletion(Buf); //INFINITE
			PendingList.removeFirst();
			BufPool.put(Buf);
		}
	}

}