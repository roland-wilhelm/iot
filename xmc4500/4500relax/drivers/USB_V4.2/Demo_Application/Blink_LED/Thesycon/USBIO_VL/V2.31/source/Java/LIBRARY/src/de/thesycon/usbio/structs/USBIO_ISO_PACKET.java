package de.thesycon.usbio.structs;

/**
 * The USBIO_ISO_PACKET class defines the size and location of a single
 * isochronous data packet within an isochronous data transfer buffer.
 */
public class USBIO_ISO_PACKET extends USBIO_BASE_STRUCT
{
	public final static int SIZE = 12;

	/**
	 * Specifies the offset, in bytes, of the isochronous packet, relative to the start of
	 * the data buffer.
	 * This parameter has to be specified by the caller for isochronous read and write operations.
	 */
	public int    Offset;
	/**
	 * Specifies the size, in bytes, of the isochronous packet.
	 * This parameter has to be specified by the caller for write operations.
	 * On read operations this field is set by the USBIO driver when the read request is completed.
	 */
	public int    Length;
	/**
	 * After the isochronous read or write request is completed by the USBIO driver this
	 * field specifies the completion status of the isochronous packet.
	 */
	public int    Status;

	/**
	 * Standard constructor of the USBIO_ISO_PACKET class.
	 */
	public USBIO_ISO_PACKET() {
		Size = SIZE;
	}

	public void parseByteArray(byte[] Bytes) {
		if (Bytes.length == Size) {
			this.Offset = (int)((Bytes[3] & 0xFF) << 24 | (Bytes[2] & 0xFF) << 16 | (Bytes[1] & 0xFF) << 8 | (Bytes[0] & 0xFF));
			this.Length = (int)((Bytes[7] & 0xFF) << 24 | (Bytes[6] & 0xFF) << 16 | (Bytes[5] & 0xFF) << 8 | (Bytes[4] & 0xFF));
			this.Status = (int)((Bytes[11] & 0xFF) << 24 | (Bytes[10] & 0xFF) << 16 | (Bytes[9] & 0xFF) << 8 | (Bytes[8] & 0xFF));
		}
	}

	public byte[] buildByteArray() {
		byte[] tempbuffer = new byte[Size];
		tempbuffer[0] = (byte) ((Offset) & 0xFF);
		tempbuffer[1] = (byte) ((Offset >> 8) & 0xFF);
		tempbuffer[2] = (byte) ((Offset >> 16) & 0xFF);
		tempbuffer[3] = (byte) ((Offset >> 24) & 0xFF);
		tempbuffer[4] = (byte) ((Length) & 0xFF);
		tempbuffer[5] = (byte) ((Length >> 8) & 0xFF);
		tempbuffer[6] = (byte) ((Length >> 16) & 0xFF);
		tempbuffer[7] = (byte) ((Length >> 24) & 0xFF);
		tempbuffer[8] = (byte) ((Status) & 0xFF);
		tempbuffer[9] = (byte) ((Status >> 8) & 0xFF);
		tempbuffer[10] = (byte) ((Status >> 16) & 0xFF);
		tempbuffer[11] = (byte) ((Status >> 24) & 0xFF);
		return tempbuffer;
	}
}