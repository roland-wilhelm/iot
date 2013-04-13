package de.thesycon.usbio.structs;

/**
 * The USBIO_BASE_STRUCT class is the base class of USBIO struct classes.
 */
public abstract class USBIO_BASE_STRUCT {

	protected int Size;

	/**
	 * Parse the byte array unf fill out the members of the USBIO struct.
	 *
	 * @param Bytes The byte array with the raw data.
 	 */
	public abstract void parseByteArray(byte[] Bytes);

	/**
	 * Builds a byte array from the members of the USBIO struct.
 	 */
	public abstract byte[] buildByteArray();

	/**
	 * Returns the size in bytes of the USBIO struct.
 	 */
	public int getSize() {return Size;}
}