package de.thesycon.usbio;

public interface UsbIoErrorCodes {

	//
	// USBIO Error Codes
	//
	/**
	 * The operation has been successfully completed.
	*/
	public static final int	USBIO_ERR_SUCCESS                              = 0x00000000;
	/**
	 * A CRC error has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_CRC                                  = 0xE0000001;
	/**
	 * A bit stuffing error has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_BTSTUFF                              = 0xE0000002;
	/**
	 * A DATA toggle mismatch (DATA0/DATA1 tokens) has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_DATA_TOGGLE_MISMATCH                 = 0xE0000003;
	/**
	 * A STALL PID has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_STALL_PID                            = 0xE0000004;
	/**
	 * The USB device is not responding.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_DEV_NOT_RESPONDING                   = 0xE0000005;
	/**
	 * A PID check has failed.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_PID_CHECK_FAILURE                    = 0xE0000006;
	/**
	 * An unexpected PID has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_UNEXPECTED_PID                       = 0xE0000007;
	/**
	 * A data overrun error has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_DATA_OVERRUN                         = 0xE0000008;
	/**
	 * A data underrun error has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_DATA_UNDERRUN                        = 0xE0000009;
	/**
	 * This error code is reserved by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_RESERVED1                            = 0xE000000A;
	/**
	 * This error code is reserved by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_RESERVED2                            = 0xE000000B;
	/**
	 * A buffer overrun has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_BUFFER_OVERRUN                       = 0xE000000C;
	/**
	 * A buffer underrun has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_BUFFER_UNDERRUN                      = 0xE000000D;
	/**
	 * A data buffer was not accessed.
	 * This error is reported by the USB host controller driver.
	 * An isochronous data buffer was scheduled too late.
	 * The specified frame number does not match the actual frame number.
	*/
	public static final int	USBIO_ERR_NOT_ACCESSED                         = 0xE000000F;
	/**
	 * A FIFO error has been detected.
	 * This error is reported by the USB host controller driver.
	 * The PCI bus latency was too long.
	*/
	public static final int	USBIO_ERR_FIFO                                 = 0xE0000010;
	/**
	 * A XACT error has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_XACT_ERROR                           = 0xE0000011;
	/**
	 * A device is babbling.
	 * This error is reported by the USB host controller driver.
	 * The data transfer phase exceeds the USB frame length.
	*/
	public static final int	USBIO_ERR_BABBLE_DETECTED                      = 0xE0000012;
	/**
	 * A data buffer error has been detected.
	 * This error is reported by the USB host controller driver.
	*/
	public static final int	USBIO_ERR_DATA_BUFFER_ERROR                    = 0xE0000013;

	/**
	 * The endpoint has been halted by the USB bus driver USBD.
	 * This error is reported by the USB bus driver USBD.
	 * A pipe will be halted by USBD when a data transmission error (CRC, bit stuff, DATA toggle) occurs.
	 * In order to re-enable a halted pipe a IOCTL_USBIO_RESET_PIPE request has to be issued
	 * on that pipe.
	*/
	public static final int	USBIO_ERR_ENDPOINT_HALTED                      = 0xE0000030;
	/**
	 * A memory allocation attempt has failed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_NO_MEMORY                            = 0xE0000100;
	/**
	 * An invalid URB function code has been passed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INVALID_URB_FUNCTION                 = 0xE0000200;
	/**
	 * An invalid parameter has been passed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INVALID_PARAMETER                    = 0xE0000300;
	/**
	 * There are data transfer requests pending for the device.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_ERROR_BUSY                           = 0xE0000400;
	/**
	 * A request has failed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_REQUEST_FAILED                       = 0xE0000500;
	/**
	 * An invalid pipe handle has been passed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INVALID_PIPE_HANDLE                  = 0xE0000600;
	/**
	 * There is not enough bandwidth available.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_NO_BANDWIDTH                         = 0xE0000700;
	/**
	 * An internal host controller error has been detected.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INTERNAL_HC_ERROR                    = 0xE0000800;
	/**
	 * A short transfer has been detected.
	 * This error is reported by the USB bus driver USBD.
	 * If the pipe is not configured accordingly a short packet sent by the device causes this error.
	 * Support for short packets has to be enabled explicitly.
	*/
	public static final int	USBIO_ERR_ERROR_SHORT_TRANSFER                 = 0xE0000900;
	/**
	 * A bad start frame has been specified.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_BAD_START_FRAME                      = 0xE0000A00;
	/**
	 * An isochronous request has failed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_ISOCH_REQUEST_FAILED                 = 0xE0000B00;
	/**
	 * The USB frame control is currently owned.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_FRAME_CONTROL_OWNED                  = 0xE0000C00;
	/**
	 * The USB frame control is currently not owned.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_FRAME_CONTROL_NOT_OWNED              = 0xE0000D00;
	/**
	 * The operation is not supported.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_NOT_SUPPORTED                        = 0xE0000E00;
	/**
	 * An invalid configuration descriptor was reported by the device.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INVALID_CONFIGURATION_DESCRIPTOR     = 0xE0000F00;

	/**
	 * There are not enough resources available to complete the operation.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INSUFFICIENT_RESOURCES               = 0xE8001000;
	/**
	 * The set configuration request has failed.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_SET_CONFIG_FAILED                    = 0xE0002000;
	/**
	 * The buffer is too small.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_USBD_BUFFER_TOO_SMALL                = 0xE0003000;
	/**
	 * The interface was not found.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_USBD_INTERFACE_NOT_FOUND             = 0xE0004000;
	/**
	 * Invalid pipe flags have been specified.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_INVALID_PIPE_FLAGS                   = 0xE0005000;
	/**
	 * The operation has been timed out.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_USBD_TIMEOUT                         = 0xE0006000;
	/**
	 * The USB device is gone.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_DEVICE_GONE                          = 0xE0007000;
	/**
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_STATUS_NOT_MAPPED                    = 0xE0008000;

	/**
	 * The operation has been cancelled.
	 * This error is reported by the USB bus driver USBD.
	 * If the data transfer requests pending on a pipe are aborted by means
	 * of IOCTL_USBIO_ABORT_PIPE or CancelIo then the operations
	 * will be completed with this error code.
	*/
	public static final int	USBIO_ERR_CANCELED                             = 0xE0010000;
	/**
	 * The isochronous data buffer was not accessed by the USB host controller.
	 * This error is reported by the USB bus driver USBD.
	 * An isochronous data buffer was scheduled too late.
	 * The specified frame number does not match the actual frame number.
	*/
	public static final int	USBIO_ERR_ISO_NOT_ACCESSED_BY_HW               = 0xE0020000;
	/**
	 * The USB host controller reported an error in a transfer descriptor.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_ISO_TD_ERROR                         = 0xE0030000;
	/**
	 * An isochronous data packet was submitted in time but failed to reach the
	 * USB host controller in time.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_ISO_NA_LATE_USBPORT                  = 0xE0040000;
	/**
	 * An isochronous data packet was submitted too late.
	 * This error is reported by the USB bus driver USBD.
	*/
	public static final int	USBIO_ERR_ISO_NOT_ACCESSED_LATE                = 0xE0050000;

	/**
	 * The operation has failed.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_FAILED                               = 0xE0001000;
	/**
	 * An invalid input buffer has been passed to an IOCTL operation.
	 * This error is reported by the USBIO driver.
	 * Make sure the input buffer matches the type and size requirements
	 * specified for the IOCTL operation.
	*/
	public static final int	USBIO_ERR_INVALID_INBUFFER                     = 0xE0001001;
	/**
	 * An invalid output buffer has been passed to an IOCTL operation.
	 * This error is reported by the USBIO driver.
	 * Make sure the output buffer matches the type and size requirements
	 * specified for the IOCTL operation.
	*/
	public static final int	USBIO_ERR_INVALID_OUTBUFFER                    = 0xE0001002;
	/**
	 * There is not enough system memory available to complete the operation.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_OUT_OF_MEMORY                        = 0xE0001003;
	/**
	 * There are read or write requests pending.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_PENDING_REQUESTS                     = 0xE0001004;
	/**
	 * The USB device is already configured.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_ALREADY_CONFIGURED                   = 0xE0001005;
	/**
	 * The USB device is not configured.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_NOT_CONFIGURED                       = 0xE0001006;
	/**
	 * There are open pipes.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_OPEN_PIPES                           = 0xE0001007;
	/**
	 * Either the handle is already bound to a pipe or
	 * the specified pipe is already bound to another handle.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_ALREADY_BOUND                        = 0xE0001008;
	/**
	 * The handle is not bound to a pipe.
	 * This error is reported by the USBIO driver.
	 * The operation that has been failed with this error code is related to a pipe.
	 * Therefore, the handle has to be bound to a pipe before the operation can be executed.
	*/
	public static final int	USBIO_ERR_NOT_BOUND                            = 0xE0001009;
	/**
	 * The USB device has been removed from the system.
	 * This error is reported by the USBIO driver.
	 * An application should close all handles for the device.
	 * After it receives a Plug and Play notification it should perform
	 * a re-enumeration of devices.
	*/
	public static final int	USBIO_ERR_DEVICE_NOT_PRESENT                   = 0xE000100A;
	/**
	 * The specified control code is not supported.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_CONTROL_NOT_SUPPORTED                = 0xE000100B;
	/**
	 * The operation has been timed out.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_TIMEOUT                              = 0xE000100C;
	/**
	 * An invalid recipient has been specified.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_INVALID_RECIPIENT                    = 0xE000100D;
	/**
	 * Either an invalid request type has been specified or the
	 * operation is not supported by that pipe type.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_INVALID_TYPE                         = 0xE000100E;
	/**
	 * An invalid IOCTL code has been specified.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_INVALID_IOCTL                        = 0xE000100F;
	/**
	 * The direction of the data transfer request is not supported by that pipe.
	 * This error is reported by the USBIO driver.
	 * On IN pipes read requests are supported only.
	 * On OUT pipes write requests are supported only.
	*/
	public static final int	USBIO_ERR_INVALID_DIRECTION                    = 0xE0001010;
	/**
	 * The number of isochronous data packets specified in an isochronous read or write
	 * request exceeds the maximum number of packets supported by the USBIO driver.
	 * This error is reported by the USBIO driver.
	 * Note that the maximum number of packets allowed per isochronous data buffer
	 * can be adjusted by means of the registry parameter MaxIsoPackets.
	*/
	public static final int	USBIO_ERR_TOO_MUCH_ISO_PACKETS                 = 0xE0001011;
	/**
	 * The memory resources are exhausted.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_POOL_EMPTY                           = 0xE0001012;
	/**
	 * The specified pipe was not found in the current configuration.
	 * This error is reported by the USBIO driver.
	 * Note that only endpoints that are included in the current configuration
	 * can be used to transfer data.
	*/
	public static final int	USBIO_ERR_PIPE_NOT_FOUND                       = 0xE0001013;
	/**
	 * An invalid isochronous data packet has been specified.
	 * This error is reported by the USBIO driver.
	 * An isochronous data buffer contains an isochronous data packet with invalid
	 * Offset and/or Length parameters.
	*/
	public static final int	USBIO_ERR_INVALID_ISO_PACKET                   = 0xE0001014;
	/**
	 * There are not enough system resources to complete the operation.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_OUT_OF_ADDRESS_SPACE                 = 0xE0001015;
	/**
	 * The specified interface was not found in the current configuration or
	 * in the configuration descriptor.
	 * This error is reported by the USBIO driver.
	 * Note that only interfaces that are included in the current configuration
	 * can be used.
	*/
	public static final int	USBIO_ERR_INTERFACE_NOT_FOUND                  = 0xE0001016;
	/**
	 * The operation cannot be executed while the USB device is in the current state.
	 * This error is reported by the USBIO driver.
	 * It is not allowed to submit requests to the device while it is in a power
	 * down state.
	*/
	public static final int	USBIO_ERR_INVALID_DEVICE_STATE                 = 0xE0001017;
	/**
	 * An invalid parameter has been specified with an IOCTL operation.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_INVALID_PARAM                        = 0xE0001018;
	/**
	 * The evaluation interval of the USBIO DEMO version has expired.
	 * This error is reported by the USBIO driver.
	 * The USBIO DEMO version is limited in runtime.
	 * After the DEMO evaluation period has expired every operation will be
	 * completed with this error code.
	 * After the system is rebooted the USBIO DEMO driver can be used for another
	 * evaluation interval.
	*/
	public static final int	USBIO_ERR_DEMO_EXPIRED                         = 0xE0001019;
	/**
	 * An invalid power state has been specified.
	 * This error is reported by the USBIO driver.
	 * Note that it is not allowed to switch from one power down state to another.
	 * The device has to be set to D0 before it can be set to another power down state.
	*/
	public static final int	USBIO_ERR_INVALID_POWER_STATE                  = 0xE000101A;
	/**
	 * The device has entered a power down state.
	 * This error is reported by the USBIO driver.
	 * When the USB device leaves power state D0 and enters a power down state
	 * then all pending read and write requests will be
	 * cancelled and completed with this error status.
	 * If an application detects this error status it can re-submit the read or write requests
	 * immediately.
	 * The requests will be queued by the USBIO driver internally.
	*/
	public static final int	USBIO_ERR_POWER_DOWN                           = 0xE000101B;
	/**
	 * The API version reported by the USBIO driver does not match the expected version.
	 * This error is reported by the USBIO C++ class library USBIOLIB.
	 * See IOCTL_USBIO_GET_DRIVER_INFO for more information on USBIO version numbers.
	*/
	public static final int	USBIO_ERR_VERSION_MISMATCH                     = 0xE000101C;
	/**
	 * The set configuration operation has failed.
	 * This error is reported by the USBIO driver.
	*/
	public static final int	USBIO_ERR_SET_CONFIGURATION_FAILED             = 0xE000101D;
	/**
	 * An additional event object that has been passed to a function, was signalled.
	*/
	public static final int	USBIO_ERR_ADDITIONAL_EVENT_SIGNALLED           = 0xE000101E;

	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The LIGHT version does not support the Vendor ID reported by the USB device.
	*/
	public static final int	USBIO_ERR_VID_RESTRICTION                      = 0xE0001080;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The LIGHT version does not support isochronous transfers.
	*/
	public static final int	USBIO_ERR_ISO_RESTRICTION                      = 0xE0001081;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The LIGHT version does not support bulk transfers.
	*/
	public static final int	USBIO_ERR_BULK_RESTRICTION                     = 0xE0001082;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The LIGHT version does not support class or vendor specific SETUP requests
	 * or the data transfer length exceeds the limit.
	*/
	public static final int	USBIO_ERR_EP0_RESTRICTION                      = 0xE0001083;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The number of endpoints active in the current configuration exceeds the limit
	 * enforced by the LIGHT version.
	*/
	public static final int	USBIO_ERR_PIPE_RESTRICTION                     = 0xE0001084;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The FIFO size of an endpoint of the current configuration exceeds the limit
	 * enforced by the LIGHT version.
	*/
	public static final int	USBIO_ERR_PIPE_SIZE_RESTRICTION                = 0xE0001085;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The LIGHT version does not support control endpoints besides EP0.
	*/
	public static final int	USBIO_ERR_CONTROL_RESTRICTION                  = 0xE0001086;
	/**
	 * The operation has failed due to a restriction of the USBIO LIGHT version.
	 * This error is reported by the USBIO driver.
	 * The LIGHT version does not support interrupt transfers.
	*/
	public static final int	USBIO_ERR_INTERRUPT_RESTRICTION                = 0xE0001087;

	/**
	 * The specified device object does not exist.
	 * This error is reported by the USBIO C++ class library USBIOLIB.
	 * The USB device is not connected to the system or it has been removed
	 * by the user.
	*/
	public static final int	USBIO_ERR_DEVICE_NOT_FOUND                     = 0xE0001100;
	/**
	 * No device object was opened.
	 * There is no valid handle to execute the operation.
	 * This error is reported by the USBIO} C++ class library USBIOLIB.
	*/
	public static final int	USBIO_ERR_DEVICE_NOT_OPEN                      = 0xE0001102;
	/**
	 * The enumeration of the specified devices has failed.
	 * There are no devices of the specified type available.
	 * This error is reported by the USBIO C++ class library USBIOLIB.
	*/
	public static final int	USBIO_ERR_NO_SUCH_DEVICE_INSTANCE              = 0xE0001104;
	/**
	 * An invalid parameter has been passed to a function.
	 * This error is reported by the USBIO C++ class library USBIOLIB.
	*/
	public static final int	USBIO_ERR_INVALID_FUNCTION_PARAM               = 0xE0001105;
	/**
	 * The library setupapi.dll could not be loaded.
	 * This error is reported by the USBIO C++ class library USBIOLIB.
	 * The Setup API that is exported by the system-provided setupapi.dll
	 * is part of the Win32 API.
	 * It is available in Windows 98 and later systems.
	*/
	public static final int	USBIO_ERR_LOAD_SETUP_API_FAILED                = 0xE0001106;

}