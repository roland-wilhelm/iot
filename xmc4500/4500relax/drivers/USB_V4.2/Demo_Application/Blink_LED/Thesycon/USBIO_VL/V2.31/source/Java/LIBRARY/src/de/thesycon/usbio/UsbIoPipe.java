package de.thesycon.usbio;

import de.thesycon.usbio.structs.*;

/**
 * This class implements the interface to an USB pipe that is exported
 * by the USBIO device driver.
 * It provides all pipe-related functions that can be executed
 * on a file handle that is bound to an USB endpoint.
 * Particularly, it provides the functions needed for a data transfer
 * from or to an endpoint.
 * <p>
 * Note that this class is derived from UsbIo.
 * All general and device-related functions can be executed
 * on an instance of UsbIoPipe as well.
 *
 * @author Thesycon
 * @version 2.0
 */
public class UsbIoPipe extends UsbIo

{
	private native int bind(HANDLE Handle,int DeviceNumber,byte EndpointAddress,int DeviceList,String InterfaceGuid);

	private native int unbind(HANDLE Handle);

	private native int abortPipe(HANDLE Handle);

	private native int resetPipe(HANDLE Handle);

	private native int resetPipeStatistics(HANDLE Handle);

	private native int setupPipeStatistics(HANDLE Handle, int AveragingInterval);

	private native int queryPipeStatistics(HANDLE Handle, byte[] PipeStatistics, int flags);

	private native int getPipeParameters(HANDLE Handle, byte[] PipeParameters);

	private native int setPipeParameters(HANDLE Handle, byte[] PipeParameters);

	private native int readSync(HANDLE Handle, byte[] data, int[] bytecount, int timeout);

	private native int read(HANDLE Handle, UsbIoBuf Buffer);

	private native int writeSync(HANDLE Handle, byte[] data, int[] bytecount, int timeout);

	private native int write(HANDLE Handle, UsbIoBuf Buffer);

	private native int waitForCompletion(HANDLE Handle, UsbIoBuf Buffer, int timeout);

	private native int pipeControlTransferIn(HANDLE Handle, byte[] data, int[] count, byte[] ControlTransfer);

	private native int pipeControlTransferOut(HANDLE Handle, byte[] data, int[] count, byte[] ControlTransfer);


	/**
	 * Generates a control transfer (SETUP token) on the pipe with a data phase in
	 * device to host (IN) direction.
	 * <p>
	 * This function is used to send a SETUP token to a Control type endpoint.
	 * <p>
	 * Note: This function cannot be used to send a SETUP request
	 * to the default endpoint 0.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_PIPE_CONTROL_TRANSFER_IN operation.
	 *
	 * @param BufDesc Reference to a caller-provided buffer descriptor.
	 * The buffer receives the data transferred in the IN data phase.
	 * When the function is called the buffer descriptor specifies the size, in bytes, of the
	 * buffer.
	 * After the function successfully returned the buffer descriptor contains
	 * the number of valid bytes returned in the buffer.
	 *
	 * @param ControlTransfer Reference to a caller-provided variable that defines the request to be generated.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#pipeControlTransferOut(USBIO_DATA_BUFFER, USBIO_PIPE_CONTROL_TRANSFER)
	 * @see de.thesycon.usbio.structs.USBIO_PIPE_CONTROL_TRANSFER#USBIO_PIPE_CONTROL_TRANSFER USBIO_PIPE_CONTROL_TRANSFER
	*/
	public int pipeControlTransferIn(USBIO_DATA_BUFFER BufDesc, USBIO_PIPE_CONTROL_TRANSFER ControlTransfer) {
		if (BufDesc == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		if (BufDesc.Buffer() == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		if (ControlTransfer == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		byte[] ContTransfer = ControlTransfer.buildByteArray();
		int[] bytecount = new int[1];
		bytecount[0] = BufDesc.getNumberOfBytesToTransfer();
		int Status = pipeControlTransferIn(Handle, BufDesc.Buffer(), bytecount, ContTransfer);
		BufDesc.setBytesTransferred(bytecount[0]);
		ControlTransfer.parseByteArray(ContTransfer);
		return Status;
	}

	/**
	 * Generates a control transfer (SETUP token) on the pipe with a data phase in
	 * host to device (OUT) direction.
	 * <p>
	 * This function is used to send a SETUP token to a Control type endpoint.
	 * <p>
	 * Note: This function cannot be used to send a SETUP request
	 * to the default endpoint 0.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_PIPE_CONTROL_TRANSFER_OUT operation.
	 *
	 * @param BufDesc to a caller-provided buffer descriptor that contains the data
	 * to be transferred in the OUT data phase.
	 * When the function is called the buffer descriptor specifies the size, in bytes, of the
	 * buffer.
	 * After the function successfully returned the buffer descriptor contains
	 * the number of bytes transferred.
	 *
	 * @param ControlTransfer Reference to a caller-provided variable that defines the request to be generated.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#pipeControlTransferIn(USBIO_DATA_BUFFER, USBIO_PIPE_CONTROL_TRANSFER)
	 * @see de.thesycon.usbio.structs.USBIO_PIPE_CONTROL_TRANSFER#USBIO_PIPE_CONTROL_TRANSFER USBIO_PIPE_CONTROL_TRANSFER
	*/
	public int pipeControlTransferOut(USBIO_DATA_BUFFER BufDesc, USBIO_PIPE_CONTROL_TRANSFER ControlTransfer) {
		if (BufDesc == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		if (BufDesc.Buffer() == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		if (ControlTransfer == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		byte[] ContTransfer = ControlTransfer.buildByteArray();
		int[] bytecount = new int[1];
		bytecount[0] = BufDesc.getNumberOfBytesToTransfer();
		int Status = pipeControlTransferOut(Handle, BufDesc.Buffer(), bytecount, ContTransfer);
		BufDesc.setBytesTransferred(bytecount[0]);
		ControlTransfer.parseByteArray(ContTransfer);
		return Status;
	}

	/**
	 * Reset the statistics counters of the pipe.
	 * <p>
	 * The USBIO driver internally maintains some statistical data per pipe object.
	 * This function resets the counters BytesTransferred, RequestsSucceeded, and RequestsFailed
	 * to zero.
	 * <p>
	 * Note that this function calls {@link de.thesycon.usbio.UsbIoPipe#queryPipeStatistics(USBIO_PIPE_STATISTICS, int) queryPipeStatistics} to
	 * reset the counters.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#setupPipeStatistics(int)
	 * @see de.thesycon.usbio.UsbIoPipe#queryPipeStatistics(USBIO_PIPE_STATISTICS, int)
	*/
	public int resetPipeStatistics() {
		return resetPipeStatistics(Handle);
	}

	/**
	 * Enables or disables a statistical analysis
	 * of the data transfer on the pipe.
	 * <p>
	 * The USBIO driver is able to analyse the data transfer (outgoing or incoming) on a pipe
	 * and to calculate the average data rate on that pipe.
	 * A time averaging algorithm is used to continuously compute the mean value of the
	 * data transfer rate.
	 * In order to save resources (kernel memory and CPU cycles) the average data rate
	 * computation is disabled by default.
	 * It has to be enabled and to be configured by means of this function
	 * before it is available to an application.
	 * See also QueryPipeStatistics and USBIO_PIPE_STATISTICS
	 * for more information on pipe statistics.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_SETUP_PIPE_STATISTICS operation.
	 *
	 * @param AveragingInterval Specifies the time interval, in milliseconds, that is used to calculate the average
	 * data rate of the pipe.
	 * A time averaging algorithm is used to continuously compute the mean value of the
	 * data transfer rate.
	 * If AveragingInterval is set to zero then the average data rate
	 * computation is disabled.
	 * This is the default state.
	 * An application should only enable the average data rate computation if it is needed.
	 * This will save resources (kernel memory and CPU cycles).
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#queryPipeStatistics(USBIO_PIPE_STATISTICS, int)
	*/
	public int setupPipeStatistics(int AveragingInterval) {
		return setupPipeStatistics(Handle, AveragingInterval);
	}

	/**
	 * Returns statistical data related to the pipe.
	 * <p>
	 * The USBIO driver internally maintains some statistical data per pipe object.
	 * This function allows an application to query the actual values of the
	 * various statistics counters.
	 * Optionally, individual counters can be reset to zero after queried.
	 * See also {@link de.thesycon.usbio.UsbIoPipe#setupPipeStatistics(int) setupPipeStatistics} and USBIO_PIPE_STATISTICS
	 * for more information on pipe statistics.
	 * <p>
	 * The USBIO driver is able to analyse the data transfer (outgoing or incoming) on a pipe
	 * and to calculate the average data rate on that pipe.
	 * In order to save resources (kernel memory and CPU cycles) this feature
	 * is disabled by default.
	 * It has to be enabled and to be configured by means of the function
	 * {@link de.thesycon.usbio.UsbIoPipe#setupPipeStatistics(int) setupPipeStatistics} before it is available to an application.
	 * Thus, before an application starts to (periodically) query the value of
	 * AverageRate} that is included in the data structure USBIO_PIPE_STATISTICS
	 * it has to enable the continuous computation of this value by a call to
	 * {@link de.thesycon.usbio.UsbIoPipe#setupPipeStatistics(int) setupPipeStatistics}.
	 * The other statistical counters contained in the USBIO_PIPE_STATISTICS structure
	 * will be updated by default and do not need to be enabled explicitly.
	 * <p>
	 * Note that the statistical data is maintained for each pipe object separately.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_QUERY_PIPE_STATISTICS operation.
	 *
	 * @param PipeStatistics Reference to a caller-provided variable that receives the statistical data.
	 *
	 * @param Flags This parameter is set to zero or any combination (bit-wise or) of the following values.
	 * USBIO_QPS_FLAG_RESET_BYTES_TRANSFERRED, USBIO_QPS_FLAG_RESET_REQUESTS_SUCCEEDED, USBIO_QPS_FLAG_RESET_REQUESTS_FAILED
	 * and USBIO_QPS_FLAG_RESET_ALL_COUNTERS.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#setupPipeStatistics(int)
	*/
	public int queryPipeStatistics(USBIO_PIPE_STATISTICS PipeStatistics, int Flags) {
		if (PipeStatistics == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		byte[] data = PipeStatistics.buildByteArray();
		int Status =  queryPipeStatistics(Handle, data, Flags);
		PipeStatistics.parseByteArray(data);
		return Status;
	}

	/**
	 * Set pipe-related parameters in the USBIO device driver.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_SET_PIPE_PARAMETERS operation.
	 *
	 * @param PipeParameters Reference to a caller-provided variable that specifies the
	 * parameters to be set.
	 *
	 * @return The function returns 0 if successful, an USBIO error codeotherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#getPipeParameters(USBIO_PIPE_PARAMETERS)
	 * @see de.thesycon.usbio.structs.USBIO_PIPE_PARAMETERS#USBIO_PIPE_PARAMETERS
	*/
	public int setPipeParameters(USBIO_PIPE_PARAMETERS PipeParameters) {
		if (PipeParameters == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		byte[] data = PipeParameters.buildByteArray();
		int Status =  setPipeParameters(Handle, data);
		PipeParameters.parseByteArray(data);
		return Status;
	}

	/**
	 * Query pipe-related parameters from the USBIO device driver.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_GET_PIPE_PARAMETERS operation.
	 *
	 * @param PipeParameters Reference to a caller-provided variable that receives the
	 * current parameter settings.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#setPipeParameters(USBIO_PIPE_PARAMETERS)
	 * @see de.thesycon.usbio.structs.USBIO_PIPE_PARAMETERS#USBIO_PIPE_PARAMETERS
	*/
	public int getPipeParameters(USBIO_PIPE_PARAMETERS PipeParameters) {
		if (PipeParameters == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		byte[] data = PipeParameters.buildByteArray();
		int Status =  getPipeParameters(Handle, data);
		PipeParameters.parseByteArray(data);
		return Status;
	}

	/**
	 * Submit a read request on the pipe and wait for its completion.
	 * <p>
	 * The function transfers data from the endpoint attached to the object
	 * to the specified buffer.
	 * The function does not return to the caller until the data transfer
	 * has been finished or aborted due to a timeout.
	 * It behaves in a synchronous manner.
	 * <p>
	 * Optionally, a timeout interval for the synchronous read operation may be specified.
	 * When the interval elapses before the operation is
	 * finished the function aborts the operation and returns with a special
	 * status of USBIO_ERR_TIMEOUT.
	 * In this case, it is not possible to determine the number of bytes already
	 * transferred.
	 * After a timeout error occurred {@link de.thesycon.usbio.UsbIoPipe#resetPipe() resetPipe} should be called.
	 * <p>
	 * Note that there is some overhead involved when this function is used.
	 * This is due to a temporary Win32 Event object that is created and destroyed
	 * internally.
	 * <p>
	 * Note: Using synchronous read requests does make sense in
	 * rare cases only and can lead to unpredictable results.
	 * It is recommended to handle read operations asynchronously by means of
	 * {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} and {@link de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf) waitForCompletion}.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param BufDesc Reference to a caller-provided buffer descriptor.
	 * The buffer receives the data transferred from the device.
	 * When the function is called the buffer descriptor specifies the size, in bytes, of the
	 * buffer.
	 * After the function succeeds the buffer descriptor contains
	 * the number of bytes successfully read.
	 *
	 * @param Timeout Specifies a timeout interval, in milliseconds.
	 * If the interval elapses and the read operation is not yet finished
	 * the function aborts the operation and returns with USBIO_ERR_TIMEOUT
	 * When INFINITE is specified then the interval never elapses.
	 * The function does not return until the read operation is finished.
	 *
	 * @return The function returns USBIO_ERR_TIMEOUT if the timeout interval elapsed
	 * and the read operation was aborted.
	 * If the read operation has been finished the return value is
	 * the completion status of the operation which is 0 for success,
	 * or an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#writeSync(USBIO_DATA_BUFFER, int)
	 * @see de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#resetPipe()
	*/
	public int readSync(USBIO_DATA_BUFFER BufDesc, int Timeout) {
		if (BufDesc == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		if (BufDesc.Buffer() == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		int[] bytecount = new int[1];
		bytecount[0] = BufDesc.getNumberOfBytesToTransfer();
		int Status = readSync(Handle, BufDesc.Buffer(), bytecount, Timeout);
		BufDesc.setBytesTransferred(bytecount[0]);
		return Status;
	}

	/**
	 * Submit a read request on the pipe and wait for its completion.
	 * <p>
	 * The function transfers data from the endpoint attached to the object
	 * to the specified buffer.
	 * The function does not return to the caller until the data transfer
	 * has been finished or aborted due to a timeout.
	 * It behaves in a synchronous manner.
	 * <p>
	 * The timeout interval for the synchronous read operation may is INFINITE.
	 * <p>
	 * Note that there is some overhead involved when this function is used.
	 * This is due to a temporary Win32 Event object that is created and destroyed
	 * internally.
	 * <p>
	 * Note: Using synchronous read requests does make sense in
	 * rare cases only and can lead to unpredictable results.
	 * It is recommended to handle read operations asynchronously by means of
	 * {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} and {@link de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf) waitForCompletion}.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param BufDesc Reference to a caller-provided buffer descriptor.
	 * The buffer receives the data transferred from the device.
	 * When the function is called the buffer descriptor specifies the size, in bytes, of the
	 * buffer.
	 * After the function succeeds the buffer descriptor contains
	 * the number of bytes successfully read.
	 *
	 * @return If the read operation has been finished the return value is
	 * the completion status of the operation which is 0 for success,
	 * or an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#writeSync(USBIO_DATA_BUFFER)
	 * @see de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#resetPipe()
	*/
	public int readSync(USBIO_DATA_BUFFER BufDesc) {
		return readSync(BufDesc, INFINITE);
	}

	/**
	 * Submit a write request on the pipe and wait for its completion.
	 * <p>
	 * The function transfers data from the endpoint attached to the object
	 * to the specified buffer.
	 * The function does not return to the caller until the data transfer
	 * has been finished or aborted due to a timeout.
	 * It behaves in a synchronous manner.
	 * <p>
	 * Optionally, a timeout interval for the synchronous write operation may be specified.
	 * When the interval elapses before the operation is
	 * finished the function aborts the operation and returns with a special
	 * status of USBIO_ERR_TIMEOUT.
	 * In this case, it is not possible to determine the number of bytes already
	 * transferred.
	 * After a timeout error occurred {@link de.thesycon.usbio.UsbIoPipe#resetPipe() resetPipe} should be called.
	 * <p>
	 * Note that there is some overhead involved when this function is used.
	 * This is due to a temporary Win32 Event object that is created and destroyed
	 * internally.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param BufDesc Reference to a caller-provided buffer descriptor that contains the data to be
	 * transferred to the device.
	 * When the function is called the buffer descriptor specifies the size, in bytes, of the
	 * buffer.
	 * After the function succeeds the buffer descriptor contains
	 * the number of bytes successfully written.
	 *
	 * @param Timeout Specifies a timeout interval, in milliseconds.
	 * If the interval elapses and the write operation is not yet finished
	 * the function aborts the operation and returns with USBIO_ERR_TIMEOUT.
	 * When INFINITE is specified then the interval never elapses.
	 * The function does not return until the write operation is finished.
	 *
	 * @return The function returns USBIO_ERR_TIMEOUT if the timeout interval elapsed
	 * and the read operation was aborted.
	 * If the read operation has been finished the return value is
	 * the completion status of the operation which is 0 for success,
	 * or an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#readSync(USBIO_DATA_BUFFER, int)
	 * @see de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#resetPipe()
	*/
	public int writeSync(USBIO_DATA_BUFFER BufDesc, int Timeout) {
		if (BufDesc == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		if (BufDesc.Buffer() == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		int[] bytecount = new int[1];
		bytecount[0] = BufDesc.getNumberOfBytesToTransfer();
		int Status = writeSync(Handle, BufDesc.Buffer(), bytecount, Timeout);
		BufDesc.setBytesTransferred(bytecount[0]);
		return Status;
	}

	/**
	 * Submit a write request on the pipe and wait for its completion.
	 * <p>
	 * The function transfers data from the endpoint attached to the object
	 * to the specified buffer.
	 * The function does not return to the caller until the data transfer
	 * has been finished or aborted due to a timeout.
	 * It behaves in a synchronous manner.
	 * <p>
	 * The timeout interval for the synchronous write operation may is INFINITE.
	 * <p>
	 * Note that there is some overhead involved when this function is used.
	 * This is due to a temporary Win32 Event object that is created and destroyed
	 * internally.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param BufDesc Reference to a caller-provided buffer descriptor that contains the data to be
	 * transferred to the device.
	 * When the function is called the buffer descriptor specifies the size, in bytes, of the
	 * buffer.
	 * After the function succeeds the buffer descriptor contains
	 * the number of bytes successfully written.
	 *
	 * @return If the read operation has been finished the return value is
	 * the completion status of the operation which is 0 for success,
	 * or an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#readSync(USBIO_DATA_BUFFER)
	 * @see de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#resetPipe()
	*/
	public int writeSync(USBIO_DATA_BUFFER BufDesc) {
		return writeSync(BufDesc, INFINITE);
	}


	/**
	 * Bind the object to an endpoint of the USB device.
	 * <p>
	 * If an USB device has not already been opened this function calls
	 * {@link de.thesycon.usbio.UsbIo#open(int, int, String) open} to attach the object to a device.
	 * It passes the parameters DeviceNumber, DeviceList,
	 * and InterfaceGuid unmodified to {@link de.thesycon.usbio.UsbIo#open(int, int, String) open}.
	 * Thus, a device and an endpoint can be attached to the object in one step.
	 * <p>
	 * Alternatively, an application can attach a device first by means
	 * of {@link de.thesycon.usbio.UsbIo#open(int, int, String) open} (derived from UsbIo, and then in a second
	 * step attach an endpoint by means of Bind.
	 * The parameters DeviceNumber, DeviceList,
	 * and InterfaceGuid will be ignored in this case.
	 * <p>
	 * The device must be set to the configured state before an endpoint can be bound,
	 * see {@link de.thesycon.usbio.UsbIo#setConfiguration(USBIO_SET_CONFIGURATION) setConfiguration}.
	 * Only endpoints that are included in the active configuration can be
	 * bound by this function and subsequently used for a data transfer.
	 * <p>
	 * Note that an instance of the UsbIoPipe class can be bound to exactly
	 * one endpoint only.
	 * Consequently, one instance has to be created for each endpoint to be
	 * activated.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_BIND_PIPE operation.
	 *
	 * @param DeviceNumber Specifies the index number of the USB Device.
	 * The index is zero-based.
	 * Note that the association between this number and the USB device
	 * can change with each call to {@link de.thesycon.usbio.UsbIo#createDeviceList(String) createDeviceList}.
	 * For more details see also {@link de.thesycon.usbio.UsbIo#open(int, int, String) open}.
	 * Note that this parameter is ignored if the device has already been opened.
	 *
	 * @param EndpointAddress Specifies the address of the endpoint to bind the object to.
	 * The endpoint address is specified as reported in the
	 * corresponding endpoint descriptor.
	 * The endpoint address includes the direction flag at bit position 7 (MSB).
	 * For example, an IN endpoint with endpoint number 1 has the endpoint address 0x81.
	 *
	 * @param DeviceList A handle to the internal device list which was returned by the function
	 * {@link de.thesycon.usbio.UsbIo#createDeviceList(String) createDeviceList} or 0.
	 * For more details see also {@link de.thesycon.usbio.UsbIo#open(int, int, String) open}.
	 * Note that this parameter is ignored if the device has already been opened.
	 *
	 * @param InterfaceGuid The provided GUID is the predefined interface GUID of the USBIO device driver,
	 * or a user-defined GUID which has to be defined in the USBIO.INF file.
	 * For more details see also {@link de.thesycon.usbio.UsbIo#open(int, int, String) open}.
	 * Note that this parameter is ignored if the device has already been opened.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#unbind()
	 * @see de.thesycon.usbio.UsbIo#createDeviceList(String)
	 * @see de.thesycon.usbio.UsbIo#open(int, int, String)
	 * @see de.thesycon.usbio.UsbIo#close()
	 * @see de.thesycon.usbio.UsbIo#setConfiguration(USBIO_SET_CONFIGURATION)
	*/
	public int bind(int DeviceNumber,byte EndpointAddress, int DeviceList,String InterfaceGuid) {
		return bind(Handle, DeviceNumber, EndpointAddress, DeviceList, InterfaceGuid);
	}

	/**
	 * Delete the association between the object and an endpoint.
	 * <p>
	 * A call to this function causes all pending
	 * read and write requests to be aborted.
	 * <p>
	 * After this function was called the object can be bound
	 * to another endpoint.
	 * However, it is recommended to use a separate object for each endpoint.
	 * See also the comments on {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * It is not an error to call Unbind when no endpoint is currently bound.
	 * The function does nothing in this case.
	 * <p>
	 * Note that closing the device either by means of {@link de.thesycon.usbio.UsbIo#close() close}
	 * or by destructing the object will also cause an unbind.
	 * Thus, normally there is no need to call Unbind explicitly.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_UNBIND_PIPE operation.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
     * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
     * @see de.thesycon.usbio.UsbIo#close()
	*/
	public int unbind() {
		return unbind(Handle);
	}

	/**
	 * Cancel all pending read and write requests on this pipe.
	 * <p>
	 * This function is used to abort pending I/O operations on the pipe.
	 * All pending buffers will be returned to the application with an error status.
	 * Note that it is not possible to determine the number of bytes already transferred
	 * from or to an aborted buffer.
	 * <p>
	 * After a call to this function and before the data transfer is restarted
	 * the state of the pipe should be reset by means of {@link de.thesycon.usbio.UsbIoPipe#resetPipe() resetPipe}.
	 * See also the comments on {@link de.thesycon.usbio.UsbIoPipe#resetPipe() resetPipe}.
	 * <p>
	 * Note that it will take some milliseconds to cancel all buffers.
	 * Therefore, AbortPipe should not be called periodically.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_ABORT_PIPE operation.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
     * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
     * @see de.thesycon.usbio.UsbIoPipe#abortPipe()
	*/
	public int abortPipe() {
		return abortPipe(Handle);
	}

	/**
	 * Reset pipe.
	 * <p>
	 * This function resets the software state of a pipe in the USB driver stack.
	 * Besides, on a bulk or interrupt pipe a CLEAR_FEATURE Endpoint Stall request
	 * will be generated on the USB.
	 * This should reset the endpoint state in the device as well.
	 * <p>
	 * This function has to be used after an error condition occurred on the
	 * pipe and the pipe was halted by the USB drivers.
	 * <p>
	 * It is recommended to call ResetPipe every time
	 * a data transfer is initialized on the pipe.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 * <p>
	 * This function is a wrapper for the IOCTL_USBIO_RESET_PIPE operation.
	 *
	 * @return The function returns 0 if successful, an USBIO error code otherwise.
	 *
     * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
     * @see de.thesycon.usbio.UsbIoPipe#abortPipe()
	*/
	public int resetPipe() {
		return resetPipe(Handle);
	}

	/**
	 * Submit a read request on the pipe.
	 * <p>
	 * The function submits the buffer memory that is attached to Buffer
	 * to the USBIO device driver.
	 * The caller has to prepare the buffer descriptor pointed to by Buffer.
	 * Particularly, the NumberOfBytesToTransfer member has to be set
	 * to the number of bytes to read.
	 * <p>
	 * The call returns immediately (asynchronous behavior).
	 * After the function succeeded the read operation is pending.
	 * It will be completed later on by the USBIO driver when
	 * data is received from the device.
	 * To determine when the operation has been completed the function
	 * {@link de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf) waitForCompletion} should be called.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param Buffer Reference to a buffer descriptor the read buffer is attached to.
	 * The buffer descriptor has to be prepared by the caller.
	 *
	 * @return Returns <code>true</code> if the request was successfully submitted, <code>false</code> otherwise.
	 * If <code>false</code> is returned then the Status member of Buffer
	 * contains an error code.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#readSync(USBIO_DATA_BUFFER)
	 * @see de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf)
	*/
	public int read(UsbIoBuf Buffer) {
		if (Buffer == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		return read(Handle, Buffer);
	}

	/**
	 * Submit a write request on the pipe.
	 * <p>
	 * The function submits the buffer memory that is attached to Buffer
	 * to the USBIO device driver.
	 * The buffer contains the data to be written.
	 * The caller has to prepare the buffer descriptor pointed to by Buffer.
	 * Particularly, the NumberOfBytesToTransfer member has to be set
	 * to the number of bytes to write.
	 * <p>
	 * The call returns immediately (asynchronous behavior).
	 * After the function succeeded the write operation is pending.
	 * It will be completed later on by the USBIO driver when
	 * data has been sent to the device.
	 * To determine when the operation has been completed the function
	 * {@link de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf) waitForCompletion} should be called.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param Buffer Reference to a buffer descriptor the write buffer is attached to.
	 * The buffer descriptor has to be prepared by the caller.
	 *
	 * @return Returns <code>true</code> if the request was successfully submitted, <code>false</code> otherwise.
	 * If <code>false</code> is returned then the Status member of Buffer
	 * contains an error code.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#writeSync(USBIO_DATA_BUFFER)
	 * @see de.thesycon.usbio.UsbIoPipe#waitForCompletion(UsbIoBuf)
	*/
	public int write(UsbIoBuf Buffer) {
		if (Buffer == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		return write(Handle, Buffer);
	}

	/**
	 * Wait for completion of a pending read or write operation.
	 * <p>
	 * After a buffer was submitted to the USBIO device driver by means of
	 * {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write}
	 * this function is used to wait for the completion of the data transfer.
	 * Note that WaitForCompletion can be called regardless of the return status
	 * of the {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write} function.
	 * It returns always the correct status of the buffer.
	 * <p>
	 * Optionally, a timeout interval for the wait operation may be specified.
	 * When the interval elapses before the read or write operation is
	 * finished the function returns with a special status of USBIO_ERR_TIMEOUT.
	 * The data transfer operation is still pending in this case.
	 * WaitForCompletion should be called again until the operation is finished.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param Buffer Reference to the buffer descriptor that has been submitted by means of
	 * {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write}.
	 *
	 * @param Timeout Specifies a timeout interval, in milliseconds.
	 * The function returns with a status code of USBIO_ERR_TIMEOUT if
	 * the interval elapses and the read or write operation is still pending.
	 *
	 * @return The function returns USBIO_ERR_TIMEOUT if the timeout interval elapsed.
	 * It returns USBIO_ERR_ADDITIONAL_EVENT_SIGNALLED if an additional event object
	 * has been specified and this event was signalled before the buffer completed or
	 * the timeout interval elapsed.
	 * If the read or write operation has been finished the return value is
	 * the final completion status of the operation.
	 * Note that the Status member of Buffer will also be
	 * set to the final completion status in this case.
	 * The completion status is 0 if the read or write operation has been successfully
	 * finished, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf)
	*/
	public int waitForCompletion(UsbIoBuf Buffer, int Timeout) {
		if (Buffer == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		return waitForCompletion(Handle, Buffer, Timeout);
	}

	/**
	 * Wait for completion of a pending read or write operation.
	 * <p>
	 * After a buffer was submitted to the USBIO device driver by means of
	 * {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write}
	 * this function is used to wait for the completion of the data transfer.
	 * Note that WaitForCompletion can be called regardless of the return status
	 * of the {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write} function.
	 * It returns always the correct status of the buffer.
	 * <p>
	 * The timeout interval for the wait operation is INFINITE.
	 * <p>
	 * The device must have been opened and the object must have been bound to an endpoint
	 * before this function is called, see {@link de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String) bind}.
	 *
	 * @param Buffer Reference to the buffer descriptor that has been submitted by means of
	 * {@link de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf) read} or {@link de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf) write}.
	 *
	 * @return It returns USBIO_ERR_ADDITIONAL_EVENT_SIGNALLED if an additional event object
	 * has been specified and this event was signalled before the buffer completed or
	 * the timeout interval elapsed.
	 * If the read or write operation has been finished the return value is
	 * the final completion status of the operation.
	 * Note that the Status member of Buffer will also be
	 * set to the final completion status in this case.
	 * The completion status is 0 if the read or write operation has been successfully
	 * finished, an USBIO error code otherwise.
	 *
	 * @see de.thesycon.usbio.UsbIoPipe#bind(int, byte, int, String)
	 * @see de.thesycon.usbio.UsbIoPipe#read(UsbIoBuf)
	 * @see de.thesycon.usbio.UsbIoPipe#write(UsbIoBuf)
	*/
	public int waitForCompletion(UsbIoBuf Buffer) {
		if (Buffer == null) {
			return USBIO_ERR_INVALID_PARAM;
		}
		return waitForCompletion(Handle, Buffer, INFINITE);
	}
}
