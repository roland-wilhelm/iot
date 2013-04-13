package de.thesycon.usbio.structs;


/**
 * The USBIO_SET_CONFIGURATION class provides information used to set
 * the device configuration.
 * This structure provides the input parameters for the IOCTL_USBIO_SET_CONFIGURATION operation.
 */
public class USBIO_SET_CONFIGURATION extends USBIO_BASE_STRUCT
{
	public final static int USBIO_MAX_INTERFACES = 32;

	public final static int SIZE = 4 + (USBIO_MAX_INTERFACES * USBIO_INTERFACE_SETTING.SIZE);

	/**
	 * Specifies the configuration to be set as a zero-based index.
	 * The given index is used to query the associated configuration descriptor
	 * (by means of a GET_DESCRIPTOR request).
	 * The configuration value that is contained in the configuration descriptor is used
	 * for the SET_CONFIGURATION request.
	 * The configuration value is defined by the device.
	 * <p>
	 * For single-configuration devices the only valid value for ConfigurationIndex is zero.
	 * <p>
	 * Refer to the Universal Serial Bus Specification 1.1, Chapter 9 for more information.
	 */
	public short ConfigurationIndex;
	/**
	 * Specifies the number of interfaces in this configuration.
	 * This is the number of valid entries in InterfaceList.
	 */
	public short NbOfInterfaces;
	/**
	 * An array of USBIO_INTERFACE_SETTING structures that describes each
	 * interface in the configuration.
	 * There have to be NbOfInterfaces valid entries in this array.
	 */
	public USBIO_INTERFACE_SETTING[] InterfaceList = new USBIO_INTERFACE_SETTING[USBIO_MAX_INTERFACES];

	/**
	 * Standard constructor of the USBIO_SET_CONFIGURATION class.
	 */
	public USBIO_SET_CONFIGURATION() {
		Size = SIZE;
		for (int i = 0;i < USBIO_MAX_INTERFACES;i++) {
			InterfaceList[i] = new USBIO_INTERFACE_SETTING();
		}
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.ConfigurationIndex = (short)((Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.NbOfInterfaces = (short)((Bytes[3] & 0xFF) << 8 | (Bytes[2] & 0xFF));
			byte[] data = new byte[USBIO_INTERFACE_SETTING.SIZE];
			for (int i = 0; i < USBIO_MAX_INTERFACES;i++) {
				System.arraycopy(Bytes,4 + (i*USBIO_INTERFACE_SETTING.SIZE),data,0,USBIO_INTERFACE_SETTING.SIZE);
				InterfaceList[i].parseByteArray(data);
			}
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((ConfigurationIndex) & 0xFF);
		tempbuffer[1] = (byte) ((ConfigurationIndex >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((NbOfInterfaces) & 0xFF);
		tempbuffer[3] = (byte) ((NbOfInterfaces >> 8) & 0xFF);
		for (int i = 0; i < USBIO_MAX_INTERFACES; i++) {
			byte[] buffer = InterfaceList[i].buildByteArray();
			for (int k = 0;k < buffer.length; k++) {
				tempbuffer[4 + i*buffer.length + k] = buffer[k];
			}
		}
		return tempbuffer;
	}
}