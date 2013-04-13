package de.thesycon.usbio.structs;

import java.io.*;

/**
 * USB string descriptor class.
 */
public class USB_STRING_DESCRIPTOR extends USB_COMMON_DESCRIPTOR
{
	public final static int MAX_DESCRIPTOR_BUFFER_SIZE = 2047;
	public final static int SIZE = MAX_DESCRIPTOR_BUFFER_SIZE;

	/** The string provides a readable description.*/
	public String Str = "";
	/** Byte array representation the string.*/
	public byte[] ByteArray = new byte[MAX_DESCRIPTOR_BUFFER_SIZE];

	/**
	 * Standard constructor of the USB_STRING_DESCRIPTOR class.
	 */
	public USB_STRING_DESCRIPTOR() {
		Size = MAX_DESCRIPTOR_BUFFER_SIZE;
	}

	public void parseByteArray(byte[] Bytes, int length) {
		try {
			if ((length >= 2) && (length <= Bytes.length)) {
				this.bLength = Bytes[0];
				this.bDescriptorType = Bytes[1];
				int len;
				if (Bytes.length < MAX_DESCRIPTOR_BUFFER_SIZE) {
					len = Bytes.length;
				} else {
					len = MAX_DESCRIPTOR_BUFFER_SIZE;
				}
				System.arraycopy(Bytes,0,this.ByteArray,0,len);
				this.Str = new String(this.ByteArray,2,length - 2,"UTF-16LE");
			}
		}
		catch (UnsupportedEncodingException ex) {
			System.out.println(ex);
		}
	}
}