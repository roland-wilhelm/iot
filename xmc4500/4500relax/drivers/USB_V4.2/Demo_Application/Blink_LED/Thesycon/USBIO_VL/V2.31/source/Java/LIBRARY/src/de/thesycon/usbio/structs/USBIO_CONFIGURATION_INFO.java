package de.thesycon.usbio.structs;

/**
 * The USBIO_CONFIGURATION_INFO class provides information about the
 * interfaces and pipes available in the current configuration.
 * This structure returns the results of the IOCTL_USBIO_GET_CONFIGURATION_INFO operation.
 * <p>
 * Note that the data structure includes only those interfaces and pipes that are
 * activated by the current configuration according to the configuration descriptor.
 */
public class USBIO_CONFIGURATION_INFO extends USBIO_BASE_STRUCT
{
	public final static int USBIO_MAX_INTERFACES = 32;
	public final static int USBIO_MAX_PIPES = 32;

	public final static int SIZE = 8 + (USBIO_MAX_INTERFACES * USBIO_INTERFACE_CONFIGURATION_INFO.SIZE) + (USBIO_MAX_PIPES * USBIO_PIPE_CONFIGURATION_INFO.SIZE);

	/**
	 * Specifies the number of interfaces active in the current configuration.
	 * This value corresponds to the number of valid entries in the InterfaceInfo array.
	 */
	public int NbOfInterfaces;
	/**
	 * Specifies the number of pipes active in the current configuration.
	 * This value corresponds to the number of valid entries in the PipeInfo array.
	 */
	public int NbOfPipes;
	/**
	 * An array of USBIO_INTERFACE_CONFIGURATION_INFO structures that describes
	 * the interfaces that are active in the current configuration.
 	 * There are NbOfInterfaces valid entries in this array.
 	 */
	public USBIO_INTERFACE_CONFIGURATION_INFO[] InterfaceInfo = new USBIO_INTERFACE_CONFIGURATION_INFO[USBIO_MAX_INTERFACES];
	/**
	 * An array of USBIO_PIPE_CONFIGURATION_INFO structures that describes the
	 * pipes that are active in the current configuration.
	 * There are NbOfPipes valid entries in this array.
	 */
	public USBIO_PIPE_CONFIGURATION_INFO[] PipeInfo = new USBIO_PIPE_CONFIGURATION_INFO[USBIO_MAX_PIPES];

	/**
	 * Standard constructor of the USBIO_CONFIGURATION_INFO class.
	 */
	public USBIO_CONFIGURATION_INFO() {
		Size = SIZE;
		for (int i = 0;i < USBIO_MAX_INTERFACES;i++) {
			InterfaceInfo[i] = new USBIO_INTERFACE_CONFIGURATION_INFO();
		}
		for (int j = 0;j < USBIO_MAX_PIPES;j++) {
			PipeInfo[j] = new USBIO_PIPE_CONFIGURATION_INFO();
		}
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.NbOfInterfaces = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.NbOfPipes = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			byte[] data = new byte[USBIO_INTERFACE_CONFIGURATION_INFO.SIZE];
			for (int i = 0; i < USBIO_MAX_INTERFACES;i++) {
				System.arraycopy(Bytes,8 + (i*USBIO_INTERFACE_CONFIGURATION_INFO.SIZE),data,0,USBIO_INTERFACE_CONFIGURATION_INFO.SIZE);
				InterfaceInfo[i].parseByteArray(data);
			}
			byte[] data1 = new byte[USBIO_PIPE_CONFIGURATION_INFO.SIZE];
			for (int j = 0; j < USBIO_MAX_PIPES;j++) {
				System.arraycopy(Bytes,8 + (USBIO_MAX_INTERFACES * USBIO_INTERFACE_CONFIGURATION_INFO.SIZE) + (j*USBIO_PIPE_CONFIGURATION_INFO.SIZE),data1,0,USBIO_PIPE_CONFIGURATION_INFO.SIZE);
				PipeInfo[j].parseByteArray(data1);
			}
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((NbOfInterfaces) & 0xFF);
		tempbuffer[1] = (byte) ((NbOfInterfaces >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((NbOfInterfaces >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((NbOfInterfaces >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((NbOfPipes) & 0xFF);
		tempbuffer[5] = (byte) ((NbOfPipes >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((NbOfPipes >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((NbOfPipes >> 24) & 0xFF);
		for (int i = 0; i < USBIO_MAX_INTERFACES; i++) {
			byte[] buffer = InterfaceInfo[i].buildByteArray();
			for (int k = 0;k < buffer.length; k++) {
				tempbuffer[8 + i*buffer.length + k] = buffer[k];
			}
		}
		for (int j = 0; j < USBIO_MAX_PIPES; j++) {
			byte[] buffer = PipeInfo[j].buildByteArray();
			for (int l = 0;l < buffer.length; l++) {
				tempbuffer[8 + (USBIO_MAX_INTERFACES * USBIO_INTERFACE_CONFIGURATION_INFO.SIZE) + j*buffer.length + l] = buffer[l];
			}
		}
		return tempbuffer;
	}
}