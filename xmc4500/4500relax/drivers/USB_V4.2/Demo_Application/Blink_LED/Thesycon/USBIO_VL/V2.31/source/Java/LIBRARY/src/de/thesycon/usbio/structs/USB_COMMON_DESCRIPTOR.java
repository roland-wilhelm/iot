package de.thesycon.usbio.structs;

/**
 * The USB_COMMON_DESCRIPTOR class contains the head of a descriptor.
 */
public class USB_COMMON_DESCRIPTOR {

	protected int Size;

	/** Specifies the length of the descriptor.*/
	public int bLength;			// 8bit
	/** Specifies the type of the descriptor.*/
	public int bDescriptorType;	// 8bit

	/*
	 * Returns the size of the descriptor.
	 */
	public int getSize() {return Size;}
}