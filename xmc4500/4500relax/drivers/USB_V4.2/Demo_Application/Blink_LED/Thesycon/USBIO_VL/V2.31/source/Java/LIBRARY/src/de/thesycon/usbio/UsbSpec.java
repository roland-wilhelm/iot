package de.thesycon.usbio;

public interface UsbSpec {

	// descriptor types
	public static final int	USB_DEVICE_DESCRIPTOR_TYPE                = 0x01;
	public static final int	USB_CONFIGURATION_DESCRIPTOR_TYPE         = 0x02;
	public static final int	USB_STRING_DESCRIPTOR_TYPE                = 0x03;
	public static final int	USB_INTERFACE_DESCRIPTOR_TYPE             = 0x04;
	public static final int	USB_ENDPOINT_DESCRIPTOR_TYPE              = 0x05;

	// descriptor types defined by DWG documents
	public static final int	USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE              = 0x06;
	public static final int	USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE     = 0x07;
	public static final int	USB_INTERFACE_POWER_DESCRIPTOR_TYPE               = 0x08;
	public static final int	USB_HID_DESCRIPTOR_TYPE                           = 0x21;
	public static final int	AUDIO_CS_INTERFACE_TYPE                           = 0x24;
	public static final int	AUDIO_CS_ENDPOINT_TYPE                            = 0x25;
}