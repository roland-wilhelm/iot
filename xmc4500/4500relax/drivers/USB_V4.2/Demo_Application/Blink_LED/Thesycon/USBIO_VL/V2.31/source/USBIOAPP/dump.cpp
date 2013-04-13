#include "stdafx.h"
#include "global.h"
#include "dump.h"


static char DumpHexDigits[] = "0123456789ABCDEF";
static char HexDumpStrBuffer[HEX_DUMP_STR_BUFFER_SIZE];

static long DumpState = 0;

#define DUMP_BYTE_TO_ASC(b,str)                                  \
    {                                                           \
      *(str)++ = DumpHexDigits[ ((unsigned char)(b)) >> 4 ];     \
      *(str)++ = DumpHexDigits[ ((unsigned char)(b)) & 0x0F ];   \
    }

#define PRINTOUT PrintOut

static
int
MakeInt3(unsigned char *ptr)
{
  int ret=0;
  ret+=*ptr++;
  ret+=((int)(*ptr++)) * 256;
  ret+=((int)(*ptr)) * 256 * 256;
  return ret;
}

void 
DumpHex(
  void *data, 
  unsigned long length
  ) 
{
  char *p, *pp;
  unsigned char *datap = (unsigned char *)data;
  unsigned long *dptr;
  int i;
  union {
    unsigned long ofs;
    unsigned char ofsb[4];
  } uu;
  unsigned char b;

  p = pp = HexDumpStrBuffer;
  uu.ofs = 0;
  
  if ( !length ) {
    PRINTOUT("HexDump buffer length: 0"NL);
  } else {

    while ( length-- ) {
  
      b = *datap++;
  
      if ( (uu.ofs & 0x000F) == 0 ) {
        /* fill line with spaces */
        for (i=20,dptr=(unsigned long*)HexDumpStrBuffer; i--; ) *dptr++ = 0x20202020;
        p = HexDumpStrBuffer;
        pp = p + (4+1+1+(4*(4*3+1))) + 1;
        /* write ofs */
        DUMP_BYTE_TO_ASC(uu.ofsb[1],p);
        DUMP_BYTE_TO_ASC(uu.ofsb[0],p);
        *p++ = ':';
        *p++ = ' ';
      }
  
      /* write byte (hex) */
      DUMP_BYTE_TO_ASC(b,p);
      *p++ = ' ';
      /* write byte (ascii) */
      *pp++ = ( (b>=0x20) && (b<=0x7F) ) ? b : '.';     //lint !e734
  
      if ( (uu.ofs & 0x0003) == 0x0003 ) {
        /* dword complete */
        *p++ = ' ';
      }
  
      uu.ofs++;
    
      if ( (uu.ofs & 0x000F) == 0 ) {
        /* end of line */
        //*pp++ = '\n';
        *pp = '\0';
        PRINTOUT("%s"NL,HexDumpStrBuffer);
      }
  
    } // while
  
    if ( (uu.ofs & 0x000F) != 0 ) {
      /* terminate last line */
      //*pp++ = '\n';
      *pp = '\0';
      PRINTOUT("%s"NL,HexDumpStrBuffer);
    }
  }
}


// dump descriptor to output window
void 
DumpDescriptor(
  void *Data, 
  unsigned long length
  )
{
  USB_COMMON_DESCRIPTOR *Desc;
  unsigned long rl = length;
  unsigned long DescLength;
  char *data= (char*)Data;

  if (rl == 0) {
    PRINTOUT("Device returned a Zero packet (length=0) to the request"NL); 
  }
  while (rl > 0) {
    Desc=(USB_COMMON_DESCRIPTOR*)data;
    DescLength=Desc->bLength;
    if ( (DescLength > rl) || (DescLength == 0)) {
      // length remaining to short
      DumpHex(data,rl);
      rl=0;
    } else {
      switch(Desc->bDescriptorType) {
      case USB_DEVICE_DESCRIPTOR_TYPE:
        DumpDeviceDescriptor((void*)data, DescLength);
        break;
      case USB_CONFIGURATION_DESCRIPTOR_TYPE:
        DumpConfigurationDescriptor((void*)data, DescLength);
        break;
      case USB_STRING_DESCRIPTOR_TYPE:
        DumpStringDescriptor((void*)data, DescLength);
        break;
      case USB_INTERFACE_DESCRIPTOR_TYPE:
        DumpInterfaceDescriptor((void*)data, DescLength);
        break;
      case USB_ENDPOINT_DESCRIPTOR_TYPE:
        DumpEndpointDescriptor((void*)data, DescLength);
        break;
			case USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:
        DumpDeviceQualifierDescriptor((void*)data, DescLength);
				break;
			case USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE:
        DumpConfigurationDescriptor((void*)data, DescLength);
				break;
      case USB_HID_DESCRIPTOR_TYPE:
        DumpHIDDescriptor((void*)data, DescLength);
        break;
      case AUDIO_CS_INTERFACE_TYPE:
        DumpAudioDescriptor((void*)data, DescLength);
        break;
      case AUDIO_CS_ENDPOINT_TYPE:
        DumpAudioEndpointDescriptor((void*)data, DescLength);
        break;

      default:
        PRINTOUT(NL);
        PRINTOUT("Unknown Descriptor:"NL);
        PRINTOUT("Descriptor length:   %02d"NL,DescLength);
        PRINTOUT("Descriptor Type:   0x%02X"NL,Desc->bDescriptorType);
        DumpHex(data,DescLength);
      } // switch
      data += DescLength;
      rl -= DescLength;
    }
  }//while
}


void 
DumpDeviceDescriptor(
  void *data, 
  unsigned long length
  )
{
  USB_DEVICE_DESCRIPTOR *Desc;

  Desc=(USB_DEVICE_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Device Descriptor:"NL);
  if (length != sizeof(USB_DEVICE_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bcdUSB             : 0x%04X"NL,Desc->bcdUSB);
    PRINTOUT("bDeviceClass       : 0x%02X"NL,Desc->bDeviceClass);
    PRINTOUT("bDeviceSubClass    : 0x%02X"NL,Desc->bDeviceSubClass);
    PRINTOUT("bDeviceProtocol    : 0x%02X"NL,Desc->bDeviceProtocol);
    PRINTOUT("bMaxPacketSize0    :   %02d"NL,Desc->bMaxPacketSize0);
    PRINTOUT("idVendor           : 0x%04X"NL,Desc->idVendor);
    PRINTOUT("idProduct          : 0x%04X"NL,Desc->idProduct);
    PRINTOUT("bcdDevice          : 0x%04X"NL,Desc->bcdDevice);
    PRINTOUT("iManufacturer      :   %02d"NL,Desc->iManufacturer);
    PRINTOUT("iProduct           :   %02d"NL,Desc->iProduct);
    PRINTOUT("iSerialNumber      :   %02d"NL,Desc->iSerialNumber);
    PRINTOUT("bNumConfigurations :   %02d"NL,Desc->bNumConfigurations);
  }

}


void 
DumpDeviceQualifierDescriptor(
  void *data, 
  unsigned long length
  )
{
  USB_DEVICE_QUALIFIER_DESCRIPTOR *Desc;

  Desc=(USB_DEVICE_QUALIFIER_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Device Qualifier Descriptor:"NL);
  if (length != sizeof(USB_DEVICE_QUALIFIER_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bcdUSB             : 0x%04X"NL,Desc->bcdUSB);
    PRINTOUT("bDeviceClass       : 0x%02X"NL,Desc->bDeviceClass);
    PRINTOUT("bDeviceSubClass    : 0x%02X"NL,Desc->bDeviceSubClass);
    PRINTOUT("bDeviceProtocol    : 0x%02X"NL,Desc->bDeviceProtocol);
    PRINTOUT("bMaxPacketSize0    :   %02d"NL,Desc->bMaxPacketSize0);
    PRINTOUT("bNumConfigurations :   %02d"NL,Desc->bNumConfigurations);
    PRINTOUT("bReserved          :   %02d"NL,Desc->bReserved);
  }

}

void 
DumpConfigurationDescriptor(
  void *data, 
  unsigned long length
  )
{
  USB_CONFIGURATION_DESCRIPTOR *Desc;

  Desc=(USB_CONFIGURATION_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Configuration Descriptor:"NL);
  if (length != sizeof(USB_CONFIGURATION_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("wTotalLength       :   %04d"NL,Desc->wTotalLength);
    PRINTOUT("bNumInterfaces     :   %02d"NL,Desc->bNumInterfaces);
    PRINTOUT("bConfigurationValue:   %02d"NL,Desc->bConfigurationValue);
    PRINTOUT("iConfiguration     :   %02d"NL,Desc->iConfiguration);
    PRINTOUT("bmAttributes       : 0x%02X"NL,Desc->bmAttributes);
    PRINTOUT("MaxPower           :   %02x"NL,Desc->MaxPower);
  }
}


void 
DumpInterfaceDescriptor(
  void *data, 
  unsigned long length
  )
{
  USB_INTERFACE_DESCRIPTOR *Desc;

  Desc=(USB_INTERFACE_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Interface Descriptor:"NL);
  if (length != sizeof(USB_INTERFACE_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bInterfaceNumber   :   %02d"NL,Desc->bInterfaceNumber);
    PRINTOUT("bAlternateSetting  :   %02d"NL,Desc->bAlternateSetting);
    PRINTOUT("bNumEndpoints      :   %02d"NL,Desc->bNumEndpoints);
    PRINTOUT("bInterfaceClass    : 0x%02X"NL,Desc->bInterfaceClass);
    PRINTOUT("bInterfaceSubClass : 0x%02X"NL,Desc->bInterfaceSubClass);
    PRINTOUT("bInterfaceProtocol : 0x%02X"NL,Desc->bInterfaceProtocol);
    PRINTOUT("iInterface         :   %02d"NL,Desc->iInterface);
  }
}

void 
DumpEndpointDescriptor(
  void *data,
  unsigned long length
  )
{
  USB_ENDPOINT_DESCRIPTOR *Desc;

  Desc=(USB_ENDPOINT_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Endpoint Descriptor:"NL);
  if (length < sizeof(USB_ENDPOINT_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bEndpointAddress   : 0x%02X"NL,Desc->bEndpointAddress);
    PRINTOUT("bmAttributes       : 0x%02X"NL,Desc->bmAttributes);
    PRINTOUT("wMaxPacketSize     :   %04d"NL,Desc->wMaxPacketSize);
    PRINTOUT("bInterval          :   %02d"NL,Desc->bInterval);
    if (length > sizeof(USB_ENDPOINT_DESCRIPTOR)) {
      PRINTOUT("Descriptor size is to large!"NL);
      DumpHex(Desc+1,length-sizeof(USB_ENDPOINT_DESCRIPTOR));
    }
  }
}

void 
DumpHIDDescriptor(
  void *data,
  unsigned long length
  )
{
  USB_HID_DESCRIPTOR *Desc;

  Desc=(USB_HID_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("HID Descriptor:"NL);
  if (length < sizeof(USB_HID_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            : 0x%02X"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bcdHID             : 0x%02X"NL,Desc->bcdHID);
    PRINTOUT("bCountryCode       : 0x%02X"NL,Desc->bCountryCode);
    PRINTOUT("bNumDescriptors    : 0x%02X"NL,Desc->bNumDescriptors);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType1);
    PRINTOUT("wDescriptorLength  : 0x%02X"NL,Desc->wDescriptorLength1);
    if (length > sizeof(USB_HID_DESCRIPTOR)) {
      PRINTOUT("Descriptor size is to large!"NL);
      DumpHex(Desc+1,length-sizeof(USB_HID_DESCRIPTOR));
    }
  }
}

void 
DumpStringDescriptor(
  void *data, 
  unsigned long length
  )
{
  USB_STRING_DESCRIPTOR *Desc;
  char* Ptr;
  unsigned int i;

  Desc=(USB_STRING_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("String Descriptor:"NL);
  PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
  PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
  PRINTOUT("DescriptorContents :   ");

  for (i=2,Ptr=(char*)data,Ptr+=2; i<length; i+=2,Ptr+=2 ) {
    PRINTOUT("%c",*Ptr);
  }
  PRINTOUT(NL);
}


void
DumpAudioEndpointDescriptor(
  void* data, 
  unsigned long length
  )
{
  AUDIO_CS_ENDPOINT_DESCRIPTOR *Desc;

  Desc=(AUDIO_CS_ENDPOINT_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Audio Endpoint Descriptor:"NL);
  if (length < sizeof(AUDIO_CS_ENDPOINT_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
  } else {
    PRINTOUT("bLength            : 0x%02X"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bDescSubtypeType   : 0x%02X"NL,Desc->bDescriptorSubtypeType);
    PRINTOUT("bmAttributes       : 0x%02X"NL,Desc->bmAttributes);
    PRINTOUT("bLockDelayUnits    : 0x%02X"NL,Desc->bLockDelayUnits);
    PRINTOUT("wLockDelay         : 0x%04X"NL,Desc->wLockDelay);
    if (length > sizeof(AUDIO_CS_ENDPOINT_DESCRIPTOR)) {
      PRINTOUT("Descriptor size is to large!"NL);
      DumpHex(Desc+1,length-sizeof(AUDIO_CS_ENDPOINT_DESCRIPTOR));
    }
  }
}

void
DumpAudioDescriptor(
  void* data, 
  unsigned long TotalLength
  )
{
  AUDIO_COMMON_INTERFACE_DESCRIPTOR *Desc;
  long length=TotalLength;
  int i;
  unsigned char *ptr;

  Desc=(AUDIO_COMMON_INTERFACE_DESCRIPTOR*)data;
  PRINTOUT(NL);
  PRINTOUT("Audio CS Interface Descriptor: ");
  if (length < sizeof(AUDIO_COMMON_INTERFACE_DESCRIPTOR)) {
    PRINTOUT("Invalid Descriptor size!"NL);
    DumpHex(data,length);
    length=0;
  } else {
    switch (Desc->bDescriptorSubtypeType) {
      case AUDIO_CS_SUBTYPE_HEADER:
        if (Desc->bLength == 7)           
          PRINTOUT("(AS Generale)"NL);
        else 
          PRINTOUT("(Header)"NL);
        break;
      case AUDIO_CS_SUBTYPE_INPUT_TERMINAL:   
        if (DumpState==1) {
          PRINTOUT("(Data Type Descriptor)"NL);
        } else {
          PRINTOUT("(Input Terminal)"NL);
        }
        break;
      case AUDIO_CS_SUBTYPE_OUTPUT_TERMINAL:  
        PRINTOUT("(Output Terminal)"NL);
        break;
      case AUDIO_CS_SUBTYPE_FEATUR_UNIT:      
        PRINTOUT("(Feature)"NL);
        break;
      case AUDIO_CS_SUBTYPE_PROCESSING_UNIT:  
        PRINTOUT("(Processing Unit)"NL);
        break;
      case AUDIO_CS_SUBTYPE_EXTENSION_UNIT:
        PRINTOUT("(Extension Unit)"NL);
        break;
      default:
        PRINTOUT(NL);
        break;
    }
    PRINTOUT("bLength            :   %02d"NL,Desc->bLength);
    PRINTOUT("bDescriptorType    : 0x%02X"NL,Desc->bDescriptorType);
    PRINTOUT("bDescSubtypeType   : 0x%02X"NL,Desc->bDescriptorSubtypeType);
    length-=sizeof(AUDIO_COMMON_INTERFACE_DESCRIPTOR);
    ptr=(unsigned char*)(Desc+1);
    switch (Desc->bDescriptorSubtypeType) {
      case AUDIO_CS_SUBTYPE_HEADER:           
        {
          AUDIO_INTERFACE_HEADER_DESCRIPTOR *aDesc=(AUDIO_INTERFACE_HEADER_DESCRIPTOR*)ptr;

          if (length < sizeof(AUDIO_INTERFACE_HEADER_DESCRIPTOR)) {
            // possible AS_GENERALE
            if (length == 4) {
              AUDIO_INTERFACE_AS_GENERAL_DESCRIPTOR *gDesc=(AUDIO_INTERFACE_AS_GENERAL_DESCRIPTOR*)ptr;
              PRINTOUT("bTerminalLink      : 0x%02X"NL,gDesc->bTerminalLink);
              PRINTOUT("bDelay             : 0x%02X"NL,gDesc->bDelay);
              PRINTOUT("wFormatTag         : 0x%04X"NL,gDesc->wFormatTag);
              length -=sizeof(AUDIO_INTERFACE_AS_GENERAL_DESCRIPTOR);
              ptr+=sizeof(AUDIO_INTERFACE_AS_GENERAL_DESCRIPTOR);
              DumpState=1;
            } else {
              PRINTOUT("Invalid Descriptor size!"NL);
              DumpHex(ptr,length);
              length=0;
            }
          } else {
            PRINTOUT("bcdADC             : 0x%02X"NL,aDesc->bcdADC);
            PRINTOUT("bTotalLength       : 0x%02X"NL,aDesc->bTotalLength);
            PRINTOUT("blnCollection      : 0x%02X"NL,aDesc->blnCollection);
            ptr=(unsigned char*)(aDesc+1);
            length-=sizeof(AUDIO_INTERFACE_HEADER_DESCRIPTOR);
            for (i=0;i<aDesc->blnCollection;i++) {
              PRINTOUT("baInterfaceNb      : 0x%02X"NL,*ptr++);   
              length--;
            }
          }
        }
        break;
      case AUDIO_CS_SUBTYPE_INPUT_TERMINAL: 
        if (DumpState==1) {
          DumpState=0;
          // Format type descriptor
          AUDIO_FORMAT_TYPE_I_DESCRIPTOR *aDesc=(AUDIO_FORMAT_TYPE_I_DESCRIPTOR*)ptr;

          if (length < sizeof(AUDIO_FORMAT_TYPE_I_DESCRIPTOR)) {
            PRINTOUT("Invalid Descriptor size!"NL);
            DumpHex(ptr,length);
            length=0;
          } else {
            PRINTOUT("bFormatType        : 0x%02X"NL,aDesc->bFormatType);
            PRINTOUT("bNrChannels        : 0x%02X"NL,aDesc->bNrChannels);
            PRINTOUT("bSubframeSize      : 0x%02X"NL,aDesc->bSubframeSize);
            PRINTOUT("bBitResolution     : 0x%02X"NL,aDesc->bBitResolution);
            PRINTOUT("bSamFreqType       : 0x%02X"NL,aDesc->bSamFreqType);

            ptr=(unsigned char*)(aDesc+1);
            length-=sizeof(AUDIO_FORMAT_TYPE_I_DESCRIPTOR);
            if (aDesc->bSamFreqType == 0 ) {
             // variable freq.
              if (length >= 6) {
                PRINTOUT("tLowerSamFreq      :   %d Hz"NL,MakeInt3(ptr));ptr+=3;
                PRINTOUT("tUpperSamFreq      :   %d Hz"NL,MakeInt3(ptr));ptr+=3;
              }
              length=0;
            } else {
              for (i=0;i<aDesc->bSamFreqType;i++) {
                PRINTOUT("tSamFreq           :   %d Hz"NL,MakeInt3(ptr));
                ptr+=3;
                length-=3;
              }
              length=0;
            }
          }
        }
        else 
        { 
          AUDIO_INTERFACE_INPUT_TERMINAL_DESCRIPTOR *aDesc=(AUDIO_INTERFACE_INPUT_TERMINAL_DESCRIPTOR*)ptr;

          if (length < sizeof(AUDIO_INTERFACE_INPUT_TERMINAL_DESCRIPTOR)) {
            PRINTOUT("Invalid Descriptor size!"NL);
            DumpHex(ptr,length);
            length=0;
          } else {
            PRINTOUT("bTerminalId        : 0x%02X"NL,aDesc->bTerminalId);
            PRINTOUT("wTerminalType      : 0x%04X"NL,aDesc->wTerminalType);
            PRINTOUT("bAssocTerminal     : 0x%02X"NL,aDesc->bAssocTerminal);
            PRINTOUT("bNrChannels        : 0x%02X"NL,aDesc->bNrChannels);
            PRINTOUT("wChannelConfig     : 0x%04X"NL,aDesc->wChannelConfig);
            PRINTOUT("iChannelNames      : 0x%02X"NL,aDesc->iChannelNames);
            PRINTOUT("iTerminal          : 0x%02X"NL,aDesc->iTerminal);       

            ptr=(unsigned char*)(aDesc+1);
            length-=sizeof(AUDIO_INTERFACE_INPUT_TERMINAL_DESCRIPTOR);
          }
        }
        break;
      case AUDIO_CS_SUBTYPE_OUTPUT_TERMINAL:
        { 
          AUDIO_INTERFACE_OUTPUT_TERMINAL_DESCRIPTOR *aDesc=(AUDIO_INTERFACE_OUTPUT_TERMINAL_DESCRIPTOR*)ptr;

          if (length < sizeof(AUDIO_INTERFACE_OUTPUT_TERMINAL_DESCRIPTOR)) {
            PRINTOUT("Invalid Descriptor size!"NL);
            DumpHex(ptr,length);
            length=0;
          } else {
            PRINTOUT("bTerminalId        : 0x%02X"NL,aDesc->bTerminalId);
            PRINTOUT("wTerminalType      : 0x%04X"NL,aDesc->wTerminalType);
            PRINTOUT("bAssocTerminal     : 0x%02X"NL,aDesc->bAssocTerminal);
            PRINTOUT("bSourceID          : 0x%02X"NL,aDesc->bSourceID);
            PRINTOUT("iTerminal          : 0x%02X"NL,aDesc->iTerminal);
  
            ptr=(unsigned char*)(aDesc+1);
            length-=sizeof(AUDIO_INTERFACE_OUTPUT_TERMINAL_DESCRIPTOR);
          }
        }
        break;
      case AUDIO_CS_SUBTYPE_FEATUR_UNIT:      
        { 
          AUDIO_INTERFACE_FEATURE_UNIT_DESCRIPTOR *aDesc=(AUDIO_INTERFACE_FEATURE_UNIT_DESCRIPTOR*)ptr;

          if (length < sizeof(AUDIO_INTERFACE_FEATURE_UNIT_DESCRIPTOR)) {
            PRINTOUT("Invalid Descriptor size!"NL);
            DumpHex(ptr,length);
            length=0;
          } else {
            PRINTOUT("bUnitID            : 0x%02X"NL,aDesc->bUnitID);
            PRINTOUT("bSourceID          : 0x%02X"NL,aDesc->bSourceID);
            PRINTOUT("bControlSize       : 0x%02X"NL,aDesc->bControlSize);
  
            ptr=(unsigned char*)(aDesc+1);
            length-=sizeof(AUDIO_INTERFACE_FEATURE_UNIT_DESCRIPTOR);
            for (i=0;i<aDesc->bControlSize;i++) {
              PRINTOUT("bmaControls        : 0x%02X"NL,*ptr++);   
              length--;
            }
          }
        }
        break;
      case AUDIO_CS_SUBTYPE_PROCESSING_UNIT:  
        break;
      case AUDIO_CS_SUBTYPE_EXTENSION_UNIT:
        break;
    }
    if (length > 0) {
      PRINTOUT("Descriptor size is to large!"NL);
      DumpHex(ptr,length);
    }
  }
  
}


void 
DumpConfigInfo(
  const USBIO_CONFIGURATION_INFO *Info
  )
{
  unsigned int i;
  
  PRINTOUT(NL);
  PRINTOUT("Configuration Information:"NL NL);
  PRINTOUT("NbOfInterfaces        :   %02d"NL NL,Info->NbOfInterfaces);
  for (i=0;i<Info->NbOfInterfaces;i++) {
    PRINTOUT("Interface %d Information:   "NL,i);
    PRINTOUT("InterfaceNumber     :   %02d"NL,Info->InterfaceInfo[i].InterfaceNumber);
    PRINTOUT("AlternateSetting    :   %02d"NL,Info->InterfaceInfo[i].AlternateSetting);
    PRINTOUT("Class               :   %02d"NL,Info->InterfaceInfo[i].Class);
    PRINTOUT("SubClass            :   %02d"NL,Info->InterfaceInfo[i].SubClass);
    PRINTOUT("Protocol            :   %02d"NL,Info->InterfaceInfo[i].Protocol);
    PRINTOUT("NumberOfPipes       :   %02d"NL,Info->InterfaceInfo[i].NumberOfPipes);
  }
  PRINTOUT(NL NL "NbOfPipes           :   %02d"NL,Info->NbOfPipes);
  for (i=0;i<Info->NbOfPipes;i++) {
    PRINTOUT(NL"Pipe %d Information:   "NL,i);
    PRINTOUT("MaximumPacketSize   :   %02d"NL,Info->PipeInfo[i].MaximumPacketSize);
    PRINTOUT("EndpointAddress     : 0x%02X"NL,Info->PipeInfo[i].EndpointAddress);
    PRINTOUT("Interval            :   %02d"NL,Info->PipeInfo[i].Interval);
    PRINTOUT("MaximumTransferSize :   %04d"NL,Info->PipeInfo[i].MaximumTransferSize);
    PRINTOUT("PipeType            : 0x%02X"NL,Info->PipeInfo[i].PipeType);
    PRINTOUT("InterfaceNumber     : 0x%02X"NL,Info->PipeInfo[i].InterfaceNumber);
  }

}


