package de.thesycon.usbio;

public interface UsbIoInterface {

	// const
	public static final int	INFINITE = 0xFFFFFFFF;

	public static final int	USBIO_INFOFLAG_CHECKED_BUILD      = 0x00000010;
	public static final int	USBIO_INFOFLAG_DEMO_VERSION       = 0x00000020;
	public static final int	USBIO_INFOFLAG_LIGHT_VERSION      = 0x00000100;
	public static final int	USBIO_INFOFLAG_VS_LIGHT_VERSION   = 0x00000200;

	public static final int	USBIO_RESET_DEVICE_ON_CLOSE   = 0x00000001;
	public static final int	USBIO_UNCONFIGURE_ON_CLOSE    = 0x00000002;
	public static final int	USBIO_ENABLE_REMOTE_WAKEUP    = 0x00000004;

	public static final int	USBIO_DEVICE_INFOFLAG_HIGH_SPEED	= 0x00100000;

	//
	// flags (pipe related)
	//
	public static final int	USBIO_SHORT_TRANSFER_OK       = 0x00010000;
	public static final int	USBIO_START_TRANSFER_ASAP     = 0x00020000;

	//
	// pipe type
	//
	public static final int	PipeTypeControl 				= 0;
	public static final int	PipeTypeIsochronous 			= 1;
	public static final int	PipeTypeBulk 					= 2;
	public static final int	PipeTypeInterrupt 				= 3;

	//
	// request recipient
	//
	public static final int	RecipientDevice 				= 0;
	public static final int	RecipientInterface 				= 1;
	public static final int	RecipientEndpoint 				= 2;
	public static final int	RecipientOther 					= 3;

	//
	// request type
	//
	public static final int	RequestTypeClass 				= 1;
	public static final int	RequestTypeVendor 				= 2;

	//
	// device power state
	//
	public static final int	DevicePowerStateD0 				= 0;
	public static final int	DevicePowerStateD1 				= 1;
	public static final int	DevicePowerStateD2 				= 2;
	public static final int	DevicePowerStateD3 				= 3;
}