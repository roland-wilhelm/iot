package de.thesycon.usbio.structs;

/**
 * The USBIO_INTERFACE_SETTING class provides information used to
 * configure an interface and its endpoints.
 * This structure provides input parameters for the IOCTL_USBIO_SET_INTERFACE
 * and the IOCTL_USBIO_SET_CONFIGURATION operation.
 */
public class USBIO_INTERFACE_SETTING extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 8;

	/**
	 * Specifies the interface number of the interface to be configured.
	 * The values are defined by the device.
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public short InterfaceIndex;
	/**
	 * Specifies the alternate setting to be set for the interface.
	 * The values are defined by the device.
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public short AlternateSettingIndex;
	/**
	 * Specifies the maximum length, in bytes, of data transfers to or from endpoints of this interface.
	 * The value is user-defined and is valid for all endpoints of this interface.
	 * If no special requirement exists a value of 4096 (4K) should be used.
	 */
	public int   MaximumTransferSize;

	/**
	 * Standard constructor of the USBIO_INTERFACE_SETTING class.
	 */
	public USBIO_INTERFACE_SETTING() {
		Size = SIZE;
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((InterfaceIndex) & 0xFF);
		tempbuffer[1] = (byte) ((InterfaceIndex >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((AlternateSettingIndex) & 0xFF);
		tempbuffer[3] = (byte) ((AlternateSettingIndex >> 8) & 0xFF);
		tempbuffer[4] = (byte) ((MaximumTransferSize) & 0xFF);
		tempbuffer[5] = (byte) ((MaximumTransferSize >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((MaximumTransferSize >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((MaximumTransferSize >> 24) & 0xFF);
		return tempbuffer;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.InterfaceIndex = (short)((Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.AlternateSettingIndex = (short)((Bytes[3] & 0xFF) << 8 | (Bytes[2] & 0xFF));
			this.MaximumTransferSize = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
		}
	}
}