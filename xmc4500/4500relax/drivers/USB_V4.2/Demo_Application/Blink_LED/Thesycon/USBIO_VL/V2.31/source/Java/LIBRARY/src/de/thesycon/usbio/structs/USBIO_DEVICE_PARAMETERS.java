package de.thesycon.usbio.structs;

/**
 * The USBIO_DEVICE_PARAMETERS class contains USBIO driver settings related to a device.
 * This structure is intended to be used with the
 * IOCTL_USBIO_GET_DEVICE_PARAMETERS and the IOCTL_USBIO_SET_DEVICE_PARAMETERS operations.
 */
public class USBIO_DEVICE_PARAMETERS extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 8;

	/**
	 * This field contains zero or any combination (bit-wise or) of the following values.
	 * <ul>
	 * <li> USBIO_RESET_DEVICE_ON_CLOSE -
	 * If this option is set then the USBIO driver generates a USB device reset
	 * after the last handle for a device has been closed by the application.
	 * If this option is active then the USBIO_UNCONFIGURE_ON_CLOSE flag will be
	 * ignored.
	 * <br>
	 * The default state of this option is defined by the registry parameter ResetDeviceOnClose.
	 * <li> USBIO_UNCONFIGURE_ON_CLOSE -
	 * If this option is set then the USBIO driver sets the USB device to its
	 * unconfigured state after the last handle for the device has been closed by the application.
	 * <br>
	 * The default state of this option is defined by the registry parameter UnconfigureOnClose.
	 * <li> USBIO_ENABLE_REMOTE_WAKEUP -
	 * If this option is set and the USB device supports the Remote Wakeup feature the USBIO driver
	 * will support Remote Wakeup for the operating system.
	 * That means the USB device is able to awake the system from a sleep state.
	 * The Remote Wakeup feature is defined by the USB 1.1 specification.
	 * <br>
	 * The Remote Wakeup feature requires that the device is opened by an application
	 * and that a USB configuration is set (device is configured).
	 * <br>
	 * The default state of this option is defined by the registry parameter EnableRemoteWakeup.
	 * </ul>
	 */
	public int Options;
	/**
	 * Specifies the time-out interval, in milliseconds, to be used for synchronous operations.
	 * A value of zero means an infinite interval (time-out disabled).
	 * <br>
	 * The default time-out value is defined by the registry parameter RequestTimeout.
	 */
	public int RequestTimeout;   // in ms

	/**
	 * Standard constructor of the USBIO_DEVICE_PARAMETERS class.
	 */
	public USBIO_DEVICE_PARAMETERS() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.Options = (Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF);
			this.RequestTimeout = ((Bytes[7] & 0xFF) << 24) | ((Bytes[6] & 0xFF) << 16) | ((Bytes[5] & 0xFF) << 8) | (Bytes[4] & 0xFF);
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((Options) & 0xFF);
		tempbuffer[1] = (byte) ((Options >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((Options >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((Options >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((RequestTimeout) & 0xFF);
		tempbuffer[5] = (byte) ((RequestTimeout >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((RequestTimeout >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((RequestTimeout >> 24) & 0xFF);
		return tempbuffer;
	}
}