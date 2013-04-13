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
** @FILENAME@:       usb_iil_cfg.H
** @VERSION@:        4.2
** @DATE@:           23/01/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents:  This file contains functions that use the USBD module.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/01/2006     Jayashree (IFIN CSW AIM)   
**                                        
** @CHANGE_HISTORY@ The product ID has been changed to 0x1F to support USBIO Light
**                Dannabaum Udo          Hidden string has been added
** =============================================================================
*/


#ifndef _USB_IIL_CFG_H_
#define _USB_IIL_CFG_H_

#include "compiler.h"
#include "usb_iil_setup.h"
#include "usb_iil_common.h"





/*
@topic1 USB ENUMERATION CONSTANTS in file USB_IIL_CFG.H |
All the set-up process descriptors according to USB1.1 specifications are
initialized in this file USB_IIL_CFG.H. The application can configure this file
according to requirement. Also see file USB_IIL_SETUP.H file for all  
the field definitions.  
For more details please refer to USB1.1 specifications. 
*/
#define EPLSB_SZ(epPktSize)		(epPktSize&0xFF)       /*LSB 8 bits*/
#define EPMSB_SZ(epPktSize)		(epPktSize>>8)         /*Next 2 bits*/


/*--------------------------------------------------------------------------
@head2 Device descriptor initialization |
--------------------------------------------------------------------------*/

/*
@def CONFIG_USB_DEVICE_DESCRIPTOR |
Device descriptor according to USB_DEVICE_DESCRIPTOR fields.
*/
#define CONFIG_USB_DEVICE_DESCRIPTOR \
    0x12,    /*  bLength */\
    0x01,    /* field bDescriptorType */\
    0x0110,  /* field bcdUSB USB Version 1.1 */\
    0x00,    /* field bDeviceClass */\
    0x00,    /* field bDeviceSubclass */\
    0x00,    /* field bDeviceProtocol */\
    0x08,    /* field bMaxPacketSize for EP0: 64 bytes */\
    0x058B,  /* field idVendor assigned by USB forum. */\
    0x001F,  /* field ProductId assigned by Infineon */\
    0x001F,  /* field bcdDevice */\
    0x01,    /* field iManufacturer String Index: 1 */\
    0x02,    /* field iProduct String Index */\
    0x03,    /* field iSerialNumber String Index */\
    0x01    /* field bNumberConfigurations */


/*--------------------------------------------------------------------------
@head2 Configuration descriptor initialization |
--------------------------------------------------------------------------*/
/* @def CONFIG_USB_NUMBER_OF_CONFIGURATIONS |
Number of configurations supported by this USB device. EP0 is supported on
configuration 0 and all others are on CF1.
*/
#define CONFIG_USB_NUMBER_OF_CONFIGURATIONS      1


/* @def CONFIG_USB_CONFIGURATION_DESCRIPTOR |
Configuration descriptor according to USB_CONFIGURATION_DESCRIPTOR fields.
The user needs to change the wTotalLenght field if CONFIG_USB_TOTBYTES
macro below changes.Also if any change is done to bNumInterfaces,
change the CONFIG_USB_TOTAL macro accordingly. Currenlty there are four
interfaces supported by this device.
*/
#define CONFIG_USB_CONFIGURATION_DESCRIPTOR \
    0x09,       /*  bLength */\
    0x02,       /* field bDescriptorType */\
    0x56,0x00,  /* wTotalLenght. See CONFIG_USB_TOTBYTES below */\
    0x04,       /* 4 bNumInterfaces */\
    0x01,       /* bConfigurationValue */\
    0x00,       /* iConfiguration */\
    0x80,       /* bmAttributes 0xE0 if remote wakeup is supported else 0xC0 */\
    0x0F       /* MaxPower */


/*--------------------------------------------------------------------------
@head2 Interface 0 initialization |
--------------------------------------------------------------------------*/
/* @def CONFIG_USB_INTERFACE_DESCRIPTOR_IF0AS0 |
Interface-0 AlternateSetting-0 descriptor according to USB_INTERFACE_DESCRIPTOR 
fields. The user need not change any field here.
*/
/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF0AS0 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF0AS0 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x00,		/* bInterfaceNumber */\
   0x00,		/* bAlternateSetting */\
   0x00,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */

/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF1AS0 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF1AS0 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x01,		/* bInterfaceNumber */\
   0x00,		/* bAlternateSetting */\
   0x00,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */

/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF1AS1 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF1AS1 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x01,		/* bInterfaceNumber */\
   0x01,		/* bAlternateSetting */\
   0x02,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */

#define CONFIG_USB_ENDPOINT_DESCRIPTOR_IF1AS1EP1 \
   0x07,		/* bLength */\
   0x05,		/* bDescriptorType */\
   ( ( EP_IN << 0x07 ) | EP1 ),		/*bEndPointAddress (8:)*/\
   ( EP_TYPE_BULK),		/* bmAttributes  0x00 : CONTROL, 0x01 : iso, 0x02 : BULK, 0x03 : INTR */\
   EPLSB_SZ(64), EPMSB_SZ(64),		/* wMaxPacketSize */\
   0x01		/* bIntervall */


#define CONFIG_USB_ENDPOINT_DESCRIPTOR_IF1AS1EP2 \
   0x07,		/* bLength */\
   0x05,		/* bDescriptorType */\
   ( ( EP_OUT << 0x07 ) | EP2 ),		/*bEndPointAddress (8:)*/\
   ( EP_TYPE_BULK),		/* bmAttributes  0x00 : CONTROL, 0x01 : iso, 0x02 : BULK, 0x03 : INTR */\
   EPLSB_SZ(64), EPMSB_SZ(64),		/* wMaxPacketSize */\
   0x01		/* bIntervall */

/*                  
 * If the configuration for EP1 and EP2 need to be changed, the ISR these EP needs also to be adapted for the new settings!   
 *                   
*/
/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF2AS0 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF2AS0 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x02,		/* bInterfaceNumber */\
   0x00,		/* bAlternateSetting */\
   0x00,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */

/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF2AS1 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF2AS1 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x02,		/* bInterfaceNumber */\
   0x01,		/* bAlternateSetting */\
   0x00,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */

/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF3AS0 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF3AS0 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x03,		/* bInterfaceNumber */\
   0x00,		/* bAlternateSetting */\
   0x00,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */

/*@def CONFIG_USB_INTERFACE_DESCRIPTOR_IF3AS1 |*/

#define CONFIG_USB_INTERFACE_DESCRIPTOR_IF3AS1 \
   0x09,		/* bLength */\
   0x04,		/* bDescriptorType */\
   0x03,		/* bInterfaceNumber */\
   0x01,		/* bAlternateSetting */\
   0x00,		/* bNumEndpoints */\
   0xFF,		/* bInterfaceClass */\
   0xFF,		/* bInterfaceSubClass */\
   0xFF,		/* bInterfaceProtocol */\
   0x00			/* iInterface */





/*--------------------------------------------------------------------------
@head2 All descriptors |
---------------------------------------------------------------------------*/
/* @def   CONFIG_USB_TOTAL |
   The CONFIG_USB_TOTAL contains all the descriptors supported by this device.
   i.e., Configuration + Interface0+ Interface1+ interface2 + Interface3 defined
   above.  Place the descriptors in order. i.e,	Interface number - its alternate
   setting - endpoints belonging to this alternate setting.
   Currently the device driver doesnot support alternate setting AS2/AS1 on same
   interface.
   If you alter this configuration make sure to alter CONFIG_USB_TOTBYTES.
   Also the USBD ( usb device ) configuration needs to be changed
   in USB_IDL_CFG.H file which is spcecific to TC1130.
*/
#define CONFIG_USB_TOTAL CONFIG_USB_CONFIGURATION_DESCRIPTOR,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF0AS0,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF1AS0,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF1AS1,\
			CONFIG_USB_ENDPOINT_DESCRIPTOR_IF1AS1EP1,\
			CONFIG_USB_ENDPOINT_DESCRIPTOR_IF1AS1EP2,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF2AS0,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF2AS1,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF3AS0,\
			CONFIG_USB_INTERFACE_DESCRIPTOR_IF3AS1


/* @def   CONFIG_USB_TOTBYTES |
   CONFIG_USB_TOTBYTES contains total number of bytes in CONFIG_USB_TOTAL.
   Calculation is as follows. Total Bytes
   = (Number of endpoint descriptor defined in CONFIG_USB_TOTAL * 7 ) +
   (Number of other descriptors * 9).
*/
#define CONFIG_USB_TOTBYTES 	0x0056


/*--------------------------------------------------------------------------
@head2 String descriptors Initialization |
---------------------------------------------------------------------------*/
/*
@struct	 LANGID_Descriptor |
Holds the initialization parameters for language id descriptor
USBD_LANG_DESCRIPTOR. Currnetly set for US english.
*/
static USBD_LANG_DESCRIPTOR LANGID_Descriptor =
{
   sizeof(LANGID_Descriptor),	/* bLength */
   USB_STRING_DESCRIPTOR_TYPE,	/* bDescriptorType */
   0x0409				/* LANGID US English */
};


/*
@struct	Manufacturer_Descriptor |
Holds the initialization parameters for manufacturer descriptor.
@comm The user can change the manufacturer string 
here, but should remember to change the MANUFACTURER_STRING_LENGTH field.
Currently MANUFACTURER_STRING_LENGTH is set to 50.
*/
static const USB_MANUFACTURER_DESCRIPTOR Manufacturer_Descriptor = 
{
    (sizeof(Manufacturer_Descriptor)),    /* @field bLength */
    (USB_STRING_DESCRIPTOR_TYPE),         /* @field bDescriptorType */
    {                                     /* INFINEON TECHNOLOGIES*/
    'I', 0,
    'N', 0,
    'F', 0,
    'I', 0,
    'N', 0,
    'E', 0,
    'O', 0,
    'N', 0,
    ' ', 0,
    'T', 0,
    'E', 0,
    'C', 0,
    'H', 0,
    'N', 0,
    'O', 0,
    'L', 0,
    'O', 0,
    'G', 0,
    'I', 0,
    'E', 0,
    'S', 0
    }
};


/*
@struct	Product_Descriptor |
Holds the initialization parameters for manufacturer descriptor.
@comm The user can change the product string (TC1130 USB) here, but 
remember to change the PRODUCT_STRING_LENGTH field.
Currently PRODUCT_STRING_LENGTH is set to 30.
*/
static USB_PRODUCT_STRING Product_Descriptor = 
{
    sizeof(Product_Descriptor),     /* @field bLength */
    USB_STRING_DESCRIPTOR_TYPE,     /* @field bDescriptorType */
    {                               /* TC1130 USB*/
    'T', 0,
    'C', 0,
    '1', 0,
    '1', 0,
    '3', 0,
    '0', 0,
    ' ', 0,
    'U', 0,
    'S', 0,
    'B', 0
    }
};


/*
@struct	USB_Serial_Descriptor |
Holds the initialization parameters for product serial number.
@comm The user can change the serial string here, but
remember to change the SERIAL_STRING_LENGTH field also.
Currently SERIAL_STRING_LENGTH is set to 30.
*/
static USB_SERIAL_NUMBER_DESCRIPTOR USB_Serial_number_descriptor =
{
    sizeof(USB_Serial_number_descriptor),      /* @field bLength */
    USB_STRING_DESCRIPTOR_TYPE,                /* @field bDescriptorType */
    {                                          /* TC1130A USB*/
    'T', 0,
    'C', 0,
    '1', 0,
    '1', 0,
    '3', 0,
    '0', 0,
    'B', 0,
    ' ', 0,
    'U', 0,
    'S', 0,
    'B', 0
    }
};

/*
@struct	USB_Hidden_Descriptor |
Holds the initialization parameters for product serial number.
@comm The user can change the serial string here, but
remember to change the SERIAL_STRING_LENGTH field also.
Currently SERIAL_STRING_LENGTH is set to 30.
*/
static USB_HIDDEN_STRING_DESCRIPTOR USB_Hidden_string_descriptor =
{
    sizeof(USB_Hidden_string_descriptor),      /* @field bLength */
    USB_STRING_DESCRIPTOR_TYPE,                /* @field bDescriptorType */
    {                                          /* TC1130A USB*/
    '7', 0,
    '9', 0,
    '4', 0,
    '2', 0,
    'F', 0,
    '3', 0,
    '0', 0,
    'A', 0
    }
};


#endif  /* _USB_IIL_CFG_H_ */
