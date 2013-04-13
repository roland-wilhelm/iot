#ifndef _DUMP_H_
#define _DUMP_H_

#define HEX_DUMP_STR_BUFFER_SIZE     2048


void DumpHex(void *data, unsigned long length);
void DumpDescriptor(void *data, unsigned long length);
void DumpDeviceDescriptor(void *data, unsigned long length);
void DumpDeviceQualifierDescriptor(void *data, unsigned long length);
void DumpConfigurationDescriptor(void *data, unsigned long length);
void DumpInterfaceDescriptor(void *data, unsigned long length);
void DumpEndpointDescriptor(void *data, unsigned long length);
void DumpStringDescriptor(void *data, unsigned long length);
void DumpHIDDescriptor(void *data, unsigned long length);
void DumpAudioDescriptor(void* data, unsigned long length);
void DumpAudioEndpointDescriptor(void* data, unsigned long length);

void DumpConfigInfo(const USBIO_CONFIGURATION_INFO *Info);


#endif // _DUMP_H_

