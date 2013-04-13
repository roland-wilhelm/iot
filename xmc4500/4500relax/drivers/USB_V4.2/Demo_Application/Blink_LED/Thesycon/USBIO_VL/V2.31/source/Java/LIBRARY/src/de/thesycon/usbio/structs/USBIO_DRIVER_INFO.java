package de.thesycon.usbio.structs;

/**
 * The USBIO_DRIVER_INFO class contains version information about
 * the USBIO programming interface (API) and the USBIO driver executable.
 * This structure returns the results of the IOCTL_USBIO_GET_DRIVER_INFO operation.
 */
public class USBIO_DRIVER_INFO extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 12;

	/**
	 * Contains the version number of the application programming interface (API) the driver supports.
	 * The format is as follows: upper 8 bit = major version, lower 8 bit = minor version.
	 * The numbers are encoded in BCD format.
	 * For example, V1.41 is represented by a numerical value of 0x0141.
	 * <p>
	 * The API version number will be incremented if changes are made at the API level.
	 * An application should check the API version at runtime.
	 * Refer to the description of the IOCTL_USBIO_GET_DRIVER_INFO request for detailed
	 * information on how this should be implemented.
	 */
	public short APIVersion;    // [MAJOR][MINOR] (BCD format)
	/**
	 * Contains the version number of the driver executable.
	 * The format is as follows: upper 8 bit = major version, lower 8 bit = minor version.
	 * For example, V1.41 is represented by a numerical value of 0x0129.
	 * <p>
	 * The driver version number will be incremented for each USBIO release.
	 * Typically, an application uses the driver version number for informational purposes only.
	 * Refer to the description of the IOCTL_USBIO_GET_DRIVER_INFO request for more information.
	 */
	public short DriverVersion; // [MAJOR][MINOR]
	/* Contains the build number of the driver executable.
	 * This number will be incremented for each build of the USBIO driver executable.
	 * The driver build number should be understand as an extension of the driver version number.
	 */
	public int  DriverBuildNumber;
	/**
	 * This field contains zero if the USBIO driver executable is a full version release build
	 * without any restrictions.
	 * Otherwise, this field contains any combination (bit-wise or) of the following values.
	 * <ul>
	 * <li>USBIO_INFOFLAG_CHECKED_BUILD -
	 * If this flag is set then the driver executable is a checked (debug) build.
	 * The checked driver executable provides additional tracing and debug features.
	 * <li>USBIO_INFOFLAG_DEMO_VERSION -
	 * If this flag is set then the driver executable is a DEMO version.
	 * The DEMO version has some restrictions.
	 * Refer to the file ReadMe.txt included in the USBIO package for a detailed description
	 * of these restrictions.
	 * <li>USBIO_INFOFLAG_LIGHT_VERSION -
	 * If this flag is set then the driver executable is a LIGHT version.
	 * The LIGHT version has some restrictions.
	 * Refer to the file ReadMe.txt included in the USBIO package for a detailed description
	 * of these restrictions.
	 * <li>USBIO_INFOFLAG_VS_LIGHT_VERSION -
	 * If this flag is set in addition to USBIO_INFOFLAG_LIGHT_VERSION the driver executable
	 * is a Vendor-Specific LIGHT version that has specific restrictions.
	 * Refer to the file ReadMe.txt included in the USBIO package for a detailed description
	 * of these restrictions.
	 * </ul>
	 */
	public int  Flags;

	/**
	 * Standard constructor of the USBIO_DRIVER_INFO class.
	 */
	public USBIO_DRIVER_INFO() {
		Size = SIZE;
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((APIVersion) & 0xFF);
		tempbuffer[1] = (byte) ((APIVersion >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((DriverVersion) & 0xFF);
		tempbuffer[3] = (byte) ((DriverVersion >> 8) & 0xFF);
		tempbuffer[4] = (byte) ((DriverBuildNumber) & 0xFF);
		tempbuffer[5] = (byte) ((DriverBuildNumber >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((DriverBuildNumber >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((DriverBuildNumber >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((Flags) & 0xFF);
		tempbuffer[9] = (byte) ((Flags >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((Flags >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((Flags >> 24) & 0xFF);
		return tempbuffer;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.APIVersion = (short)((Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.DriverVersion = (short)((Bytes[3] & 0xFF) << 8 | (Bytes[2] & 0xFF));
			this.DriverBuildNumber = (Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF);
			this.Flags = (Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF);
		}
	}
}