/************************************************************************
 *
 *  Module:       usbspec.h
 *  Long name:    USB Specification 1.1 and 2.0
 *  Description:  
 *
 *  Runtime Env.: any
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef _USBSPEC_H_
#define _USBSPEC_H_


// pack the following structures                                                     
#include <PSHPACK1.H>

// In Borland C++, we have to force byte alignment.
// This is necessary because there seems to be a problem with the
// implementations of pshpackX.h and poppack.h.
#ifdef __BORLANDC__
#pragma pack(1)
#endif

//
// descriptor types
//
#define USB_DEVICE_DESCRIPTOR_TYPE                    0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE             0x02
#define USB_STRING_DESCRIPTOR_TYPE                    0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE                 0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE                  0x05
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE          0x06
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE 0x07
#define USB_HID_DESCRIPTOR_TYPE                       0x21



//
// device descriptor
//
typedef struct _USB_DEVICE_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  USHORT  bcdUSB;
  UCHAR   bDeviceClass;
  UCHAR   bDeviceSubClass;
  UCHAR   bDeviceProtocol;
  UCHAR   bMaxPacketSize0;
  USHORT  idVendor;
  USHORT  idProduct;
  USHORT  bcdDevice;
  UCHAR   iManufacturer;
  UCHAR   iProduct;
  UCHAR   iSerialNumber;
  UCHAR   bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;


//
// configuration descriptor
//
typedef struct _USB_CONFIGURATION_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  USHORT  wTotalLength;
  UCHAR   bNumInterfaces;
  UCHAR   bConfigurationValue;
  UCHAR   iConfiguration;
  UCHAR   bmAttributes;
  UCHAR   MaxPower;
} USB_CONFIGURATION_DESCRIPTOR;


//
// interface descriptor
//
typedef struct _USB_INTERFACE_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  UCHAR   bInterfaceNumber;
  UCHAR   bAlternateSetting;
  UCHAR   bNumEndpoints;
  UCHAR   bInterfaceClass;
  UCHAR   bInterfaceSubClass;
  UCHAR   bInterfaceProtocol;
  UCHAR   iInterface;
} USB_INTERFACE_DESCRIPTOR;


//
// endpoint descriptor
//
typedef struct _USB_ENDPOINT_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  UCHAR   bEndpointAddress;
  UCHAR   bmAttributes;
  USHORT  wMaxPacketSize;
  UCHAR   bInterval;
} USB_ENDPOINT_DESCRIPTOR;


//
// string descriptor
//
typedef struct _USB_STRING_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  WCHAR   bString[1]; // variable size
} USB_STRING_DESCRIPTOR;

//
// device qualifier descriptor
//
typedef struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  USHORT  bcdUSB;
  UCHAR   bDeviceClass;
  UCHAR   bDeviceSubClass;
  UCHAR   bDeviceProtocol;
  UCHAR   bMaxPacketSize0;
  UCHAR   bNumConfigurations;
  UCHAR   bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR;

//
// HID descriptor
//
typedef struct _USB_HID_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  USHORT  bcdHID; 
  UCHAR   bCountryCode;
  UCHAR   bNumDescriptors;
  UCHAR   bDescriptorType1;
  USHORT  wDescriptorLength1; 
} USB_HID_DESCRIPTOR;


//
// common descriptor header
//
typedef struct _USB_COMMON_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
} USB_COMMON_DESCRIPTOR;




//
// Audio Descriptors
//

#define AUDIO_CS_INTERFACE_TYPE           0x24
#define AUDIO_CS_ENDPOINT_TYPE            0x25

#define AUDIO_CS_SUBTYPE_HEADER           0x01
#define AUDIO_CS_SUBTYPE_INPUT_TERMINAL   0x02
#define AUDIO_CS_SUBTYPE_OUTPUT_TERMINAL  0x03
// #define AUDIO_CS_SUBTYPE_MIXER_UNIT        0x04
// #define AUDIO_CS_SUBTYPE_SELECTOR_UNIT   0x05
#define AUDIO_CS_SUBTYPE_FEATUR_UNIT      0x06
#define AUDIO_CS_SUBTYPE_PROCESSING_UNIT  0x07
#define AUDIO_CS_SUBTYPE_EXTENSION_UNIT   0x08

//
// common audio descriptor header
//
typedef struct _AUDIO_COMMON_INTERFACE_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  UCHAR   bDescriptorSubtypeType;
} AUDIO_COMMON_INTERFACE_DESCRIPTOR;

//
// Header
//
typedef struct _AUDIO_INTERFACE_HEADER_DESCRIPTOR {
  USHORT  bcdADC;
  USHORT  bTotalLength;
  UCHAR   blnCollection;
  // UCHAR baInterfaceNr[];
} AUDIO_INTERFACE_HEADER_DESCRIPTOR;

//
// Input Terminal
//
typedef struct _AUDIO_INTERFACE_INPUT_TERMINAL_DESCRIPTOR {
  UCHAR   bTerminalId;
  USHORT  wTerminalType;
  UCHAR   bAssocTerminal;
  UCHAR   bNrChannels;
  USHORT  wChannelConfig;
  UCHAR   iChannelNames;
  UCHAR   iTerminal;
} AUDIO_INTERFACE_INPUT_TERMINAL_DESCRIPTOR;

//
// Output Terminal
//
typedef struct _AUDIO_INTERFACE_OUTPUT_TERMINAL_DESCRIPTOR {
  UCHAR   bTerminalId;
  USHORT  wTerminalType;
  UCHAR   bAssocTerminal;
  UCHAR   bSourceID;
  UCHAR   iTerminal;
} AUDIO_INTERFACE_OUTPUT_TERMINAL_DESCRIPTOR;

//
// Feature Unit
//
typedef struct _AUDIO_INTERFACE_FEATURE_UNIT_DESCRIPTOR {
  UCHAR   bUnitID;
  UCHAR   bSourceID;
  UCHAR   bControlSize;
  // UCHAR    bmaControls[];
} AUDIO_INTERFACE_FEATURE_UNIT_DESCRIPTOR;

//
// AS General
//
typedef struct _AUDIO_INTERFACE_AS_GENERAL_DESCRIPTOR {
  UCHAR   bTerminalLink;
  UCHAR   bDelay;
  USHORT  wFormatTag;
} AUDIO_INTERFACE_AS_GENERAL_DESCRIPTOR;

//
// AS Format Type 1
//
typedef struct _AUDIO_FORMAT_TYPE_I_DESCRIPTOR {
  UCHAR   bFormatType;
  UCHAR   bNrChannels;
  UCHAR   bSubframeSize;
  UCHAR   bBitResolution;
  UCHAR   bSamFreqType;
} AUDIO_FORMAT_TYPE_I_DESCRIPTOR;



//
// CS Endpoint
//

typedef struct _AUDIO_CS_ENDPOINT_DESCRIPTOR {
  UCHAR   bLength;
  UCHAR   bDescriptorType;
  UCHAR   bDescriptorSubtypeType;
  UCHAR   bmAttributes;   
  UCHAR   bLockDelayUnits;    
  USHORT  wLockDelay;   
} AUDIO_CS_ENDPOINT_DESCRIPTOR;


// restore previous settings
#ifdef __BORLANDC__
#pragma pack()
#endif

// restore packing
#include <POPPACK.H>


#endif  // _USBSPEC_H_

/*************************** EOF **************************************/
