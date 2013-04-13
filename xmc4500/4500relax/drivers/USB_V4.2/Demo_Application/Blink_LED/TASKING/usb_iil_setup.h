/* =============================================================================
** Copyright (C) 2006 Infineon Technologies.
**
** All rights reserved.
** =============================================================================
**
** =============================================================================
**
** This document contains proprietary information belonging to Infineon 
** Technologies. Passing on and copying of this document, and communication of 
** its contents is not permitted without prior written authorisation.
**
** =============================================================================
*/
/* =============================================================================
**
** Revision Information :
** @FILENAME@:       USB_IIL_SETUP.H
** @VERSION@:        4.2
** @DATE@:           23/01/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Contains USB1.1 enumeration definitions.
**            
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004     Ranganatha (DC BA)               
**
**               Jayashree (IFIN CSW AIM) String descriptor support for index 5 
**                                      removed.
** 17/01/2006    Jayashree (IFIN CSW AIM) USB_RQ_CLASS_REQUEST_UPLOAD has been 
**                                      added to support service of class request.                 
** @CHANGE_HISTORY@
** =============================================================================
*/

#ifndef _USB_IIL_SETUP_H_
#define _USB_IIL_SETUP_H_

#include "compiler.h"
#include "usbd_idl_macro.h"
#include "usb_iil_common.h" 

/*------------------------------------------------------------------------
 *  @topic1 USB ENUMERATION Definitions |
 *   All the set-up process descriptors according to USB1.1 specification
 *   are defined in this file USB_IIL_SETUP.H. User need not modify any
 *   field here unless specified. The user can initialize all these 
 *   descriptors in a separate file USB_IIL_CFG.H .
 *------------------------------------------------------------------------*/

/*
  USB_setup_request | 
  setup request descriptor
*/
volatile typedef struct {
	IFX_UINT8 bmRequestType; /* USB request type. Defines characteristics of request */
	IFX_UINT8 bRequest;      /* Specific request            */
	IFX_UINT16 wValue;			 /* vaires according to request */
	IFX_UINT16 wIndex;			 /* varies according to request */
	IFX_UINT16 wLength;			 /* Number of bytes to transfer, if data stage */
} USB_setup_request;

volatile typedef struct {
	IFX_UINT32 SUTL;					/* Set Up token low bytes*/
	IFX_UINT32 SUTH;					/* Set Up token high bytes*/
} USB_SETUP_RQ_U;

/*
  USB_setup_request | setup request structure.
*/
typedef union{
  USB_SETUP_RQ_U    usb_SUP;           
	USB_setup_request usbSetUpPackets;	/* Set Up packets fields*/
}USB_SETUP_PACKET;				


 /* Setup request constants. */
#define USB_SETUP_RQ_DIRECTION_MASK     0x80
#define USB_SETUP_RQ_TYPE_MASK          0x60
#define USB_SETUP_RQ_RECIPIENT_MASK     0x1F

#define USB_RQ_DIRECTION_OUT            ( 0x00 << 7 )
#define USB_RQ_DIRECTION_IN             ( 0x01 << 7 )

#define USB_RQ_TYPE_STANDARD            ( 0x00 << 5 )
#define USB_RQ_TYPE_CLASS               ( 0x01 << 5 )
#define USB_RQ_TYPE_VENDOR              ( 0x02 << 5 )

#define USB_RQ_RECIPIENT_DEVICE         0x00 
#define USB_RQ_RECIPIENT_INTERFACE      0x01
#define USB_RQ_RECIPIENT_ENDPOINT       0x02
#define USB_RQ_RECIPIENT_OTHER          0x03

#define USB_RQ_GET_DESCRIPTOR           0x06      
#define USB_RQ_SET_DESCRIPTOR           0x07
#define USB_RQ_SYNCH_FRAME              0x0C
#define USB_RQ_VENDOR_DATA              0x00
#define USB_RQ_CLASS_REQUEST_UPLOAD     0x02


/*@def USB_DEVICE_DESCRIPTOR_TYPE |
  Device descriptor constant */
#define USB_DEVICE_DESCRIPTOR_TYPE          0x01

/*@def USB_CONFIGURATION_DESCRIPTOR_TYPE |
  configuration descriptor constant */
#define USB_CONFIGURATION_DESCRIPTOR_TYPE   0x02

/*@def USB_STRING_DESCRIPTOR_TYPE |
  String descriptor constant */
#define USB_STRING_DESCRIPTOR_TYPE          0x03

/*@def USB_INTERFACE_DESCRIPTOR_TYPE |
  Interface descriptor constant */
#define USB_INTERFACE_DESCRIPTOR_TYPE       0x04

/*@def USB_ENDPOINT_DESCRIPTOR_TYPE |
  Endpoint descriptor constant */
#define USB_ENDPOINT_DESCRIPTOR_TYPE        0x05


/*
  @struct USB_DEVICE_DESCRIPTOR | 
  @comm The usb device descriptor. For initialization see 
  CONFIG_USB_DEVICE_DESCRIPTOR macro. If any field is changed like iProduct
  ..., the application should take care to modify the USB_IIL_SETUP.C file
  accordingly.
*/
typedef struct {
	IFX_UINT8 bLength;          		/*@field size of this device descriptor in bytes */
	IFX_UINT8 bDescriptorType;		/*@field Device descriptor type: 01h const */ 
	IFX_UINT16 bcdUSB ;			/*@field USB Spec release number: ver1.0 is 0100, ver1.1 is 0110 */	
	IFX_UINT8 bDeviceClass;		  	/*@field Class code: FFh means vendor specifc      */
	IFX_UINT8 bDeviceSubClass;		/*@field Sub class code: FFh means vendor specifc  */
	IFX_UINT8 bDeviceProtocol;		/*@field protocol code:  FFh means vendor specifc  */
	IFX_UINT8 bMaxPacketSize0;		/*@field max payload for EP0 */
	IFX_UINT16 idVendor;		  	/*@field Vendor ID assigned by USB forum */
	IFX_UINT16 idProduct;		  	/*@field Product ID assigned by Manufacturer */
	IFX_UINT16 bcdDevice;		   	/*@field Device Release number in BCD */
	IFX_UINT8 iManufacturer;	 	/*@field Index of String descriptor describing Manufacturer */
	IFX_UINT8 iProduct;			/*@field Index of String descriptor describing Product */
	IFX_UINT8 iSerialNumber;	 	/*@field Index of String descriptor describing device's Serial number */	
	IFX_UINT8 bNumConfigurations;		/*@field Number of possible configurations on this device */
} USB_DEVICE_DESCRIPTOR;



/*
  @struct USB_ENDPOINT_DESCRIPTOR | USB endpoint descriptor
  All the endpoint descriptors declared in USB_IIL_SETUP.H should use the 
  following fields.
  @comm Not to be confused with on-chip USB device endpoints. 
*/
typedef struct {
	IFX_UINT8 bLength;			     	/*@field size of thid descriptor in bytes*/
	IFX_UINT8 bDescriptorType;    			/*@field endpoint descriptor type- 05h const*/
	IFX_UINT8 bEndpointAddress;   			/*@field endpoint number & direction; "Bit 7: Direction(0:OUT, 1: IN),Bit 6-4:Res,Bit 3-0:EP no"*/
	IFX_UINT8 bmAttributes;		  		/*@field Bit 1-0: Transfer Type 00:Control,01:Isochronous,10: Bulk, 11: Interrupt */
	IFX_UINT8 wMaxPacketSizeLSB;			/*@field LSB of Maximum Packet Size for this EP*/	
	IFX_UINT8 wMaxPacketSizeMSB;			/*@field MSB of Maximum Packet Size for this EP*/	
	IFX_UINT8 bInterval;		      		/*@field  Interval for polling EP, applicable for Interrupt and Isochronous data transfer only */
} USB_ENDPOINT_DESCRIPTOR;



/*
  @struct USB_CONFIGURATION_DESCRIPTOR | 
  USB device configuration descriptor. The application can specify the device 
  capablities like remote wake-up, power consumption, number of configuration
  and interfaces supported. 
  @comm For initialization see CONFIG_USB_CONFIGURATION_DESCRIPTOR
*/
typedef struct {
    IFX_UINT8 bLength;					/*@field size of thid descriptor in bytes*/
	IFX_UINT8 bDescriptorType;			/*@field Configuration descriptor type - 02h const*/
	IFX_UINT8 wTotalLengthLSB;  			/*@field LSB Total length of data for this configuration*/
	IFX_UINT8 wTotalLengthMSB;  			/*@field MSB Total length of data for this configuration*/
	IFX_UINT8 bNumInterfaces;	  		/*@field Nos of Interface supported by this configuration*/
	IFX_UINT8 bConfigurationValue;  		/*@field Identifies the configuration in Get_configuration & Set_Configuration */
	IFX_UINT8 iConfiguration;		 	/*@field Index to the string that describes the configuration */
	IFX_UINT8 bmAttributes;			 	/*@field Config Characteristcs bitmap "D7,D4-D0: Res, D6: Self Powered,D5: Remote Wakeup*/
	IFX_UINT8 MaxPower;				/*@field Max Power Consumption of the USB device */
} USB_CONFIGURATION_DESCRIPTOR;


/*
  @struct USB_INTERFACE_DESCRIPTOR | USB interface descriptor
  All the interfaces descriptors declared in USB_IIL_SETUP.H should use the 
  following fields.
*/
typedef struct {
		IFX_UINT8 bLength;			/*@field size of thid descriptor in bytes*/
		IFX_UINT8 bDescriptorType;		/*@field Interface Descriptor Type - 04h const*/
		IFX_UINT8 bInterfaceNumber;		/*@field Number of Interface */
		IFX_UINT8 bAlternateSetting;		/*@field Value used to select alternate setting*/	
		IFX_UINT8 bNumEndpoints;		/*@field Nos of Endpoints used by this Interface*/	
		IFX_UINT8 bInterfaceClass;		/*@field Class code assigned bu USB Forum "0xFF Vendor specific"*/
		IFX_UINT8 bInterfaceSubClass;		/*@field Subclass code assigned bu USB Forum "0xFF Vendor specific"*/
		IFX_UINT8 bInterfaceProtocol;		/*@field Protocol code assigned bu USB Forum "0xFF Vendor specific"*/
		IFX_UINT8 iInterface;			/*@field Index of String descriptor describing Interface*/	
} USB_INTERFACE_DESCRIPTOR;


/*
  @def MANUFACTURER_STRING_LENGTH |
  Maximum string length for manufacturer descritpor.
  @comm Change this if any modification is done to 
  Manufacturer_Descriptor structure.
*/
#define MANUFACTURER_STRING_LENGTH 50

/*
  @struct USB_MANUFACTURER_DESCRIPTOR |
  The application can change the manufacturer string here.
  Currently set to "Infineon Technologies". See Manufacturer_Descriptor to
  initialize according to requirement. 
*/
typedef struct USB_MANUFACTURER_DESCRIPTOR_t
{
    IFX_UINT8 bLength;					/*@field size of this descritor */
    IFX_UINT8 bDescriptorType; 				/*@field STRING descriptor type.*/
    IFX_UINT8 bString[MANUFACTURER_STRING_LENGTH];      /*@field string to be passed or captured*/   
} USB_MANUFACTURER_DESCRIPTOR;

/*
  @struct USBD_LANG_DESCRIPTOR | Language descriptor.
  The application can change the language type here.
  Currently set to US ENGLISH. See LANGID_Descriptor to
  initialize according to requirement. 
*/
typedef struct {
        IFX_UINT8 bLength;		     	 /*@field size of this descritor */
   	IFX_UINT8 bDescriptorType;		 /*@field STRING descriptor type. */
   	IFX_UINT16 wLANGID0;       		 /*@field Language Id*/
} USBD_LANG_DESCRIPTOR;


/*
  @def PRODUCT_STRING_LENGTH |
  Maximum string length used in USB_PRODUCT_STRING descritpor.
  @comm change this if string length exceeds 25 in Product_Descriptor. 
*/
#define PRODUCT_STRING_LENGTH 25


/*
  @struct USB_PRODUCT_STRING |
  USB product string. Currently initialized to "TC1130 USB" .
  @comm See Product_Descriptor to initialize according to requirement. 
*/
typedef struct {
    IFX_UINT8 bLength;			           /*@field size of this descritor */
    IFX_UINT8 bDescriptorType; 			   /*@field STRING descriptor type.*/
    IFX_UINT8 bString[PRODUCT_STRING_LENGTH];      /*@field string to be passed or captured*/   
}USB_PRODUCT_STRING;




/*
  @def SERIAL_STRING_LENGTH |
  Maximum serial number length for USB_SERIAL_NUMBER_DESCRIPTOR.
  @comm Change this if any modification is done to 
  USB_Serial_number_descriptor structure.
*/
#define SERIAL_STRING_LENGTH 25


/*
  @struct USB_SERIAL_NUMBER_DESCRIPTOR |
  Device/Product serial number. Currently initialized to "TC1130A USB".
  @comm See USB_Serial_number_descriptor to initialize accordingly.
*/
typedef struct {
    IFX_UINT8 bLength;					/*@field size of this descritor */
    IFX_UINT8 bDescriptorType;  			/*@field STRING descriptor type.*/
    IFX_UINT8 bString[SERIAL_STRING_LENGTH];     	/*@field string to be passed or captured*/   
} USB_SERIAL_NUMBER_DESCRIPTOR;

/*
  @def HIDDEN_STRING_LENGTH |
  Maximum serial number length for USB_SERIAL_NUMBER_DESCRIPTOR.
  @comm Change this if any modification is done to 
  USB_Serial_number_descriptor structure.
*/

#define HIDDEN_STRING_LENGTH 25

/*
  @struct USB_SERIAL_NUMBER_DESCRIPTOR |
  Device/Product serial number. Currently initialized to "TC1130 USB".
  @comm See USB_Serial_number_descriptor to initialize accordingly.
*/
typedef struct {
	IFX_UINT8 bLength;			/*@field size of this descritor */
    IFX_UINT8 bDescriptorType;  /*@field STRING descriptor type.*/
    IFX_UINT8 bString[HIDDEN_STRING_LENGTH];      /*@field string to be passed or captured*/   
} USB_HIDDEN_STRING_DESCRIPTOR;



#endif /*_USB_IIL_SETUP_H_*/

