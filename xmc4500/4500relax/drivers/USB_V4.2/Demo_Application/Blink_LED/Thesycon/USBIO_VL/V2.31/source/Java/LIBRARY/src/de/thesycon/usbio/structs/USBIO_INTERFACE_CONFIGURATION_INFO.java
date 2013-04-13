package de.thesycon.usbio.structs;

/**
 * The USBIO_INTERFACE_CONFIGURATION_INFO class provides information about an interface.
 * This structure returns results of the IOCTL_USBIO_GET_CONFIGURATION_INFO operation.
 * It is a substructure within the USBIO_CONFIGURATION_INFO structure.
 */
public class USBIO_INTERFACE_CONFIGURATION_INFO extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 8;

	/**
	 * Specifies the index of the interface as reported by the device
	 * in the configuration descriptor.
	 */
	public byte   InterfaceNumber;
	/**
	 * Specifies the index of the alternate setting as reported by the device
	 * in the configuration descriptor.
	 * The default alternate setting of an interface is zero.
	 */
	public byte   AlternateSetting;
	/**
	 * Specifies the class code as reported by the device in the configuration descriptor.
	 * The meaning of this value is defined by USB device class specifications.
	 */
	public byte   _Class;
	/**
	 * Specifies the subclass code as reported by the device in the configuration descriptor.
	 * The meaning of this value is defined by USB device class specifications.
	 */
	public byte   SubClass;
	/**
	 * Specifies the protocol code as reported by the device in the configuration descriptor.
	 * The meaning of this value is defined by USB device class specifications.
	 */
	public byte   Protocol;
	/** Specifies the number of pipes that belong to this interface and alternate setting.*/
	public byte   NumberOfPipes;
	/** Reserved field, set to zero.*/
	public byte   reserved1;  // reserved field, set to zero
	/** Reserved field, set to zero.*/
	public byte   reserved2;  // reserved field, set to zero

	/**
	 * Standard constructor of the USBIO_INTERFACE_CONFIGURATION_INFO class.
	 */
	public USBIO_INTERFACE_CONFIGURATION_INFO() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.InterfaceNumber = Bytes[0];
			this.AlternateSetting = Bytes[1];
			this._Class = Bytes[2];
			this.SubClass = Bytes[3];
			this.Protocol = Bytes[4];
			this.NumberOfPipes = Bytes[5];
			this.reserved1 = Bytes[6];
			this.reserved2 = Bytes[7];
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((InterfaceNumber) & 0xFF);
		tempbuffer[1] = (byte) ((AlternateSetting) & 0xFF);
		tempbuffer[2] = (byte) ((_Class) & 0xFF);
		tempbuffer[3] = (byte) ((SubClass) & 0xFF);
		tempbuffer[4] = (byte) ((Protocol) & 0xFF);
		tempbuffer[5] = (byte) ((NumberOfPipes) & 0xFF);
		tempbuffer[6] = (byte) ((reserved1) & 0xFF);
		tempbuffer[7] = (byte) ((reserved2) & 0xFF);
		return tempbuffer;
	}
}