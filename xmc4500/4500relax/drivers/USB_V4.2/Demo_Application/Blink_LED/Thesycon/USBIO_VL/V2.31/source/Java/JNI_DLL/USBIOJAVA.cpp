/************************************************************************
 *
 *  Module:       UsbioJava.cpp
 *  Long name:    Usbio Java Interface
 *  Description:  the interface between JNI DLL and Java classes
 *
 *  Runtime Env.: Win32
 *  Author(s):    Frank Hofmann
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#include "stdafx.h"
#include "USBIOJAVA.h"

#pragma warning (disable:4786)


//#define MAX_DESCRIPTOR_BUFFER_SIZE			2047
#define MAX_ERROR_TEXT_SIZE							1024

/*
 *	DbgMask
 * 1 - Warning
 * 2 - Info
 * 3 - DLL specific
 * 4 - function calls
 * 5 - Pipe specific and Statistics
 * 6 - PnP Notifications
 * 7 - Read
 * 8 - Write
 * 9 - Completion
 */

// registry path
#ifdef _DEBUG
	static const char sRegPath[] = "Software\\Thesycon\\USBIO\\USBIOJAVA";
	FILE *mDbgFile;
	CRegAcc Reg;
#endif

struct eqstr
{
  bool operator()(int i1, int i2) const
  {
    return i1 == i2;
  }
};

//
// global variables
//
int globalcounter = 1;
// protects the map
CRITICAL_SECTION CritSect;

JavaVM *vm = NULL;

static void NotifyCallback(void *context,int function);

std::hash_map<int, CPipe*, std::hash<INT>, eqstr> usb_instances;



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			#ifdef _DEBUG
				DWORD Mask;
				char FileName[1024];

				mDbgFile = NULL;
				// open key or create it
				Reg.OpenKey(HKEY_LOCAL_MACHINE,sRegPath,true); //lint !e534
				if (!Reg.GetDword("DbgMask",&Mask,7)) Reg.SetDword("DbgMask",Mask);              //lint !e534
				gTrace.SetMask(Mask);
				if (Reg.GetString("DbgFile",FileName,sizeof(FileName))) {
					if (strlen(FileName) > 0) {
						mDbgFile = fopen(FileName,"wt");
						gTrace.SetTarget(TRCTARGET_FILE,mDbgFile);
					}
				}
			#endif
			TRACE(3,tprint("DLL_PROCESS_ATTACH\n"));
			InitializeCriticalSection(&CritSect);
			break;
		case DLL_THREAD_ATTACH:
			TRACE(3,tprint("DLL_THREAD_ATTACH\n"));
			break;
		case DLL_THREAD_DETACH:
			TRACE(3,tprint("DLL_THREAD_DETACH\n"));
			break;
		case DLL_PROCESS_DETACH:
			TRACE(3,tprint("DLL_PROCESS_DETACH\n"));
			DeleteCriticalSection(&CritSect);
			break;
    }
    return TRUE;
} // DllMain


BOOL setObjHandle(JNIEnv *env,jobject* Handle, int value) {
	if (env->IsInstanceOf(*Handle, env->FindClass("de/thesycon/usbio/structs/HANDLE"))) {
		jclass cls = env->GetObjectClass(*Handle);
		jmethodID method = env->GetMethodID(cls, "setHANDLE", "(I)V");
		env->CallVoidMethod(*Handle,method,(jint)value);
		return true;
	} else {
		*Handle = NULL;
		return false;
	}
} // setObjHandle


BOOL getObjHandle(JNIEnv *env,jobject Handle, int* value) {
	if (Handle == NULL) {
		TRACE(1,tprint("Handle is NULL."));
		return false;
	}
	if (env->IsInstanceOf(Handle, env->FindClass("de/thesycon/usbio/structs/HANDLE"))) {
		jclass cls = env->GetObjectClass(Handle);
		jmethodID method = env->GetMethodID(cls, "getHANDLE", "()I");
		*value = env->CallIntMethod(Handle,method);
		return true;
	} else {
		*value = 0;
		return false;
	}
} // getObjHandle


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_createDeviceList
(JNIEnv *env, jclass obj, jstring InterfaceGuid)
{
	HRESULT result;
	HDEVINFO ret;
	
	TRACE(4,tprint("[CreateDeviceList\n"));
	if (InterfaceGuid == NULL) {
		TRACE(1,tprint("CreateDeviceList: InterfaceGuid is NULL."));
		return 0;
	}
	GUID Guid;

	WCHAR* guidWStr = (WCHAR*)env->GetStringChars(InterfaceGuid, 0);
	result = ::CLSIDFromString(guidWStr,&Guid);

	if (result != NOERROR) {
		TRACE(2,tprint("CreateDeviceList: Error convert String to Guid."));
		// error convert string to guid
		ret = 0;
	} else {
		ret = CUsbIo::CreateDeviceList(&Guid);
	}

	env->ReleaseStringChars(InterfaceGuid,guidWStr);
	TRACE(4,tprint("CreateDeviceList] ret: 0x%08X\n",ret));
	return (jint)ret;
} // Java_de_thesycon_usbio_UsbIo_CreateDeviceList


JNIEXPORT void JNICALL Java_de_thesycon_usbio_UsbIo_destroyDeviceList
(JNIEnv *env, jclass obj, jint DeviceList)
{
	TRACE(4,tprint("[DestroyDeviceList: DeviceList: 0x%08X\n",DeviceList));
	CUsbIo::DestroyDeviceList((HDEVINFO)DeviceList);
	TRACE(4,tprint("DestroyDeviceList]\n"));
} // Java_de_thesycon_usbio_UsbIo_DestroyDeviceList


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_cyclePort
(JNIEnv *env, jobject obj, jobject Handle)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[CyclePort\n"));
	// get handle
	if (getObjHandle(env,Handle,&value)) {
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->CyclePort();
		}
	}
	TRACE(4,tprint("CyclePort] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
  return Status;
} // Java_de_thesycon_usbio_UsbIo_CyclePort


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_open
(JNIEnv *env, jobject obj, jobject Handle, jint DeviceNumber, jint DeviceList, jstring InterfaceGuid)
{
  DWORD Status;
	int value;
	HRESULT result;

	TRACE(4,tprint("[Open\n"));

	if (InterfaceGuid == NULL) {
		TRACE(1,tprint("Open: InterfaceGuid is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	if (getObjHandle(env,Handle,&value)) {
		// no object handle available
		// create a new instance
		GUID Guid;

		WCHAR* guidWStr = (WCHAR*)env->GetStringChars(InterfaceGuid, 0);
		result = ::CLSIDFromString(guidWStr,&Guid);

		if (result != NOERROR) {
			TRACE(2,tprint("Open: Error convert String to Guid."));
			// error convert string to guid
			Status = USBIO_ERR_INVALID_PARAM;
		} else {
			// search next free index in map, wrap around
			while (usb_instances[globalcounter] != NULL) {
				globalcounter++;
				if (globalcounter == 0) {
					globalcounter++;
				}
			}
			// create a new pipe
			CPipe* UsbioPipe = new CPipe();
			if (UsbioPipe != NULL) {				
				Status = UsbioPipe->Open(DeviceNumber,(void*)DeviceList,&Guid);

				if (Status == USBIO_ERR_SUCCESS) {
					TRACE(4,tprint("Open: new CPipe instance globalcounter: %i\n",globalcounter));
					usb_instances[globalcounter] = UsbioPipe;
					if (!setObjHandle(env,&Handle,globalcounter)) {
						Status = USBIO_ERR_FAILED;
						usb_instances.erase(globalcounter);
						delete UsbioPipe;
					}
				} else {
					TRACE(2,tprint("Open: open failed %x.",Status));
					delete UsbioPipe;
				}
			} else {
				Status = USBIO_ERR_NO_MEMORY;
			}
		}
		env->ReleaseStringChars(InterfaceGuid,guidWStr);
	}
	LeaveCriticalSection(&CritSect);

	TRACE(4,tprint("Open] (0x%08X)\n",Status));
	return Status;
} // Java_de_thesycon_usbio_UsbIo_Open


JNIEXPORT void JNICALL Java_de_thesycon_usbio_UsbIo_close
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[Close\n"));
	// get handle
	if (getObjHandle(env,Handle,&value)) {
		CPipe* UsbioPipe = usb_instances[value];
		// get pointer to the UsbIoPipe class
		if (UsbioPipe != NULL) {
			TRACE(5,tprint("Close(%02X)\n",UsbioPipe->mDbgEndpointAddress));
			UsbioPipe->Close();
			TRACE(4,tprint("Close: delete CPipe instance value: %i\n",value));
			// free UsbIoPipe class
			delete UsbioPipe;
			usb_instances.erase(value); 
		} else {
			TRACE(2, tprint("Close: UsbioPipe is NULL\n"));
		}
	}
	TRACE(4,tprint("Close]\n"));
	LeaveCriticalSection(&CritSect);
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_acquireDevice
(JNIEnv *env, jobject obj, jobject Handle)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[Acquire\n"));
	// get handle
	if (getObjHandle(env,Handle,&value)) {
		CPipe* UsbioPipe = usb_instances[value];
		// get pointer to the UsbIoPipe class
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->AcquireDevice();
		} else {
			TRACE(2, tprint("AcquireDevice: UsbioPipe is NULL\n"));
		}
	}
	TRACE(4,tprint("Acquire] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_releaseDevice
(JNIEnv *env, jobject obj, jobject Handle)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[Release\n"));
	// get handle
	if (getObjHandle(env,Handle,&value)) {
		CPipe* UsbioPipe = usb_instances[value];
		// get pointer to the UsbIoPipe class
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->ReleaseDevice();
		} else {
			TRACE(2, tprint("ReleaseDevice: UsbioPipe is NULL\n"));
		}
	}
	TRACE(4,tprint("Release] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getStringDescriptor
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray StringDesc, jintArray count, jbyte Index, jint LanguageId)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (StringDesc == NULL) {
		TRACE(1,tprint("GetStringDescriptor: StringDesc is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("GetStringDescriptor: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetStringDescriptor\n"));

	// get handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count)>=1) {
				unsigned long* length = (unsigned long*)env->GetIntArrayElements(count,JNI_FALSE);
				if (env->GetArrayLength(StringDesc)>=(jsize)(*length)) {
					TRACE(4,tprint("GetStringDescriptor: length: %u, Index: %i,LanguageId: %i\n", length, Index, LanguageId));
					USB_STRING_DESCRIPTOR* Buffer = (USB_STRING_DESCRIPTOR*)env->GetByteArrayElements(StringDesc,JNI_FALSE);
					// get the string descriptor
					Status = UsbioPipe->GetStringDescriptor(Buffer,*length,(unsigned char)Index,(unsigned short)LanguageId);
					env->ReleaseByteArrayElements(StringDesc,(jbyte*)Buffer,0);
				} else {
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
				env->ReleaseIntArrayElements(count,(jint*)length,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetStringDescriptor] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getDriverInfo
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray DriverInfo)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (DriverInfo == NULL) {
		TRACE(1,tprint("GetDriverInfo: DriverInfo is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDriverInfo\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(DriverInfo) == sizeof(USBIO_DRIVER_INFO)) {
				USBIO_DRIVER_INFO* Buffer = (USBIO_DRIVER_INFO*)env->GetByteArrayElements(DriverInfo,JNI_FALSE);
				// get driver info
				Status = UsbioPipe->GetDriverInfo(Buffer);
				env->ReleaseByteArrayElements(DriverInfo,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetDriverInfo] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getDeviceDescriptor
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray DeviceDescriptor)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (DeviceDescriptor == NULL) {
		TRACE(1,tprint("GetDeviceDescriptor: DeviceDescriptor is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDeviceDescriptor\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(DeviceDescriptor) == sizeof(USB_DEVICE_DESCRIPTOR)) {
				USB_DEVICE_DESCRIPTOR* Buffer = (USB_DEVICE_DESCRIPTOR*)env->GetByteArrayElements(DeviceDescriptor,JNI_FALSE);
				// get driver info
				Status = UsbioPipe->GetDeviceDescriptor(Buffer);
				env->ReleaseByteArrayElements(DeviceDescriptor,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetDeviceDescriptor] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getDeviceParameters
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray DeviceParameters)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (DeviceParameters == NULL) {
		TRACE(1,tprint("GetDeviceParameters: DeviceParameters is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDeviceParameters\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(DeviceParameters) == sizeof(USBIO_DEVICE_PARAMETERS)) {
				USBIO_DEVICE_PARAMETERS* Buffer = (USBIO_DEVICE_PARAMETERS*)env->GetByteArrayElements(DeviceParameters,JNI_FALSE);
				// get driver info
				Status = UsbioPipe->GetDeviceParameters(Buffer);
				env->ReleaseByteArrayElements(DeviceParameters,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetDeviceParameters] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_setDeviceParameters
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray DeviceParameters)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (DeviceParameters == NULL) {
		TRACE(1,tprint("SetDeviceParameters: DeviceParameters is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetDeviceParameters\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(DeviceParameters) == sizeof(USBIO_DEVICE_PARAMETERS)) {
				USBIO_DEVICE_PARAMETERS* Buffer = (USBIO_DEVICE_PARAMETERS*)env->GetByteArrayElements(DeviceParameters,JNI_FALSE);
				// get driver info
				Status = UsbioPipe->SetDeviceParameters(Buffer);
				env->ReleaseByteArrayElements(DeviceParameters,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("SetDeviceParameters] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getDeviceInfo
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray DeviceInfo)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (DeviceInfo == NULL) {
		TRACE(1,tprint("GetDeviceInfo: DeviceInfo is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDeviceInfo\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(DeviceInfo) == sizeof(USBIO_DEVICE_INFO)) {
				USBIO_DEVICE_INFO* Buffer = (USBIO_DEVICE_INFO*)env->GetByteArrayElements(DeviceInfo,JNI_FALSE);
				// get driver info
				Status = UsbioPipe->GetDeviceInfo(Buffer);
				env->ReleaseByteArrayElements(DeviceInfo,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetDeviceInfo] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getBandwidthInfo
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray BandwidthInfo)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (BandwidthInfo == NULL) {
		TRACE(1,tprint("GetBandwidthInfo: BandwidthInfo is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetBandwidthInfo\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(BandwidthInfo) == sizeof(USBIO_BANDWIDTH_INFO)) {
				USBIO_BANDWIDTH_INFO* Buffer = (USBIO_BANDWIDTH_INFO*)env->GetByteArrayElements(BandwidthInfo,JNI_FALSE);
				// get bandwidth info
				Status = UsbioPipe->GetBandwidthInfo(Buffer);
				env->ReleaseByteArrayElements(BandwidthInfo,(signed char*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetBandwidthInfo] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getConfigurationInfo
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray Info)
{
  DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (Info == NULL) {
		TRACE(1,tprint("GetConfigurationInfo: Info is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetConfigurationInfo\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(Info) == sizeof(USBIO_CONFIGURATION_INFO)) {
				USBIO_CONFIGURATION_INFO* Buffer = (USBIO_CONFIGURATION_INFO*)env->GetByteArrayElements(Info,JNI_FALSE);
				// get bandwidth info
				Status = UsbioPipe->GetConfigurationInfo(Buffer);
				env->ReleaseByteArrayElements(Info,(signed char*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetConfigurationInfo] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jboolean JNICALL Java_de_thesycon_usbio_UsbIo_isOpen
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	BOOL ret = FALSE;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[IsOpen\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			ret = UsbioPipe->IsOpen();
		}
	}
	TRACE(4,tprint("IsOpen] %x\n",ret));
	LeaveCriticalSection(&CritSect);
	// return status
	return ret;
}


JNIEXPORT jboolean JNICALL Java_de_thesycon_usbio_UsbIo_isLightVersion
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	BOOL ret = FALSE;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[IsLightVersion\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			ret = UsbioPipe->IsLightVersion();
		}
	}
	TRACE(4,tprint("IsLightVersion] %x\n",ret));
	LeaveCriticalSection(&CritSect);
	// return status
	return ret;
}


JNIEXPORT jboolean JNICALL Java_de_thesycon_usbio_UsbIo_isDemoVersion
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	BOOL ret = FALSE;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[IsDemoVersion\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			ret = UsbioPipe->IsDemoVersion();
		}
	}
	TRACE(4,tprint("IsDemoVersion] %x\n",ret));
	LeaveCriticalSection(&CritSect);
	// return status
	return ret;
}


JNIEXPORT jboolean JNICALL Java_de_thesycon_usbio_UsbIo_isCheckedBuild
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	BOOL ret = FALSE;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[IsCheckedBuild\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			ret = UsbioPipe->IsCheckedBuild();
		}
	}
	TRACE(4,tprint("IsCheckedBuild] %x\n",ret));
	LeaveCriticalSection(&CritSect);
	// return status
	return ret;
}


JNIEXPORT jboolean JNICALL Java_de_thesycon_usbio_UsbIo_isOperatingAtHighSpeed
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	BOOL ret = FALSE;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[IsOperatingAtHighSpeed\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			ret = UsbioPipe->IsOperatingAtHighSpeed();
		}
	}
	TRACE(4,tprint("IsOperatingAtHighSpeed] %x\n",ret));
	LeaveCriticalSection(&CritSect);
	// return status
	return ret;
}


JNIEXPORT jstring JNICALL Java_de_thesycon_usbio_UsbIo_getDevicePathName
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	jstring ret = NULL;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDevicePathName\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			ret = env->NewStringUTF(UsbioPipe->GetDevicePathName());
		}
	}
	TRACE(4,tprint("GetDevicePathName]\n"));
	LeaveCriticalSection(&CritSect);
	// return status
	return ret;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_resetDevice
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	DWORD Status = USBIO_ERR_FAILED;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[ResetDevice\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->ResetDevice();
		}
	}
	TRACE(4,tprint("ResetDevice] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_unconfigureDevice
(JNIEnv *env, jobject obj, jobject Handle)
{
	int value;
	DWORD Status = USBIO_ERR_FAILED;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[UnconfigureDevice\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->UnconfigureDevice();
		}
	}
	TRACE(4,tprint("UnconfigureDevice] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_setConfiguration
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray Conf)
{
	USBIO_SET_CONFIGURATION* Configuration;
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (Conf == NULL) {
		TRACE(1,tprint("SetConfiguration: Conf is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetConfiguration\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(Conf) == sizeof(USBIO_SET_CONFIGURATION)) {
				Configuration = (USBIO_SET_CONFIGURATION*)env->GetByteArrayElements(Conf,JNI_FALSE);
				Status =UsbioPipe->SetConfiguration(Configuration);
				env->ReleaseByteArrayElements(Conf,(signed char*)Configuration,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("SetConfiguration] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_storeConfigurationDescriptor
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray Conf)
{
	USB_CONFIGURATION_DESCRIPTOR* Configuration;
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (Conf == NULL) {
		TRACE(1,tprint("StoreConfigurationDescriptor: Conf is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[StoreConfigurationDescriptor\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(Conf) == sizeof(USB_CONFIGURATION_DESCRIPTOR)) {
				Configuration = (USB_CONFIGURATION_DESCRIPTOR*)env->GetByteArrayElements(Conf,JNI_FALSE);
				Status =UsbioPipe->StoreConfigurationDescriptor(Configuration);
				env->ReleaseByteArrayElements(Conf,(signed char*)Configuration,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("StoreConfigurationDescriptor] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_readSync
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count,jint Timeout)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("ReadSync: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("ReadSync: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(7,tprint("[ReadSync\n"));
	
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			TRACE(5,tprint("ReadSync(%02X)\n",UsbioPipe->mDbgEndpointAddress));
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if ((jsize)length <= env->GetArrayLength(bytearr)) {
					TRACE(7,tprint("ReadSync: Length: %u, Timeout: %u\n",length,Timeout));
					jbyte* Buffer = env->GetByteArrayElements(bytearr,JNI_FALSE);
					LeaveCriticalSection(&CritSect);
					Status = UsbioPipe->ReadSync(Buffer,length,Timeout);
					EnterCriticalSection(&CritSect);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(bytearr,Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(7,tprint("ReadSync] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_classOrVendorInRequest
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jbyteArray Request)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("ClassOrVendorInRequest: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("ClassOrVendorInRequest: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (Request == NULL) {
		TRACE(1,tprint("ClassOrVendorInRequest: Request is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[ClassOrVendorInRequest\n"));
	
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (((jsize)length <= env->GetArrayLength(bytearr)) && (sizeof(USBIO_CLASS_OR_VENDOR_REQUEST) <= env->GetArrayLength(Request))) {
					jbyte* Buffer = env->GetByteArrayElements(bytearr,JNI_FALSE);
					USBIO_CLASS_OR_VENDOR_REQUEST* Req = (USBIO_CLASS_OR_VENDOR_REQUEST*)env->GetByteArrayElements(Request,JNI_FALSE);
					Status = UsbioPipe->ClassOrVendorInRequest(Buffer,length,Req);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(Request,(jbyte*)Req,0);
					env->ReleaseByteArrayElements(bytearr,Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("ClassOrVendorInRequest] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_classOrVendorOutRequest
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jbyteArray Request)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("ClassOrVendorOutRequest: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("ClassOrVendorOutRequest: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (Request == NULL) {
		TRACE(1,tprint("ClassOrVendorOutRequest: Request is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[ClassOrVendorOutRequest\n"));

	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (((jsize)length <= env->GetArrayLength(bytearr)) && (sizeof(USBIO_CLASS_OR_VENDOR_REQUEST) <= env->GetArrayLength(Request))) {
					jbyte* Buffer = env->GetByteArrayElements(bytearr,JNI_FALSE);
					USBIO_CLASS_OR_VENDOR_REQUEST* Req = (USBIO_CLASS_OR_VENDOR_REQUEST*)env->GetByteArrayElements(Request,JNI_FALSE);
					Status = UsbioPipe->ClassOrVendorOutRequest(Buffer,length,Req);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(Request,(jbyte*)Req,0);
					env->ReleaseByteArrayElements(bytearr,Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("ClassOrVendorOutRequest] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getConfigurationDescriptor
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jbyte Index)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("GetConfigurationDescriptor: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("GetConfigurationDescriptor: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetConfigurationDescriptor\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (sizeof(USB_CONFIGURATION_DESCRIPTOR) <= env->GetArrayLength(bytearr)) {
					USB_CONFIGURATION_DESCRIPTOR* Buffer = (USB_CONFIGURATION_DESCRIPTOR*)env->GetByteArrayElements(bytearr,JNI_FALSE);
					Status = UsbioPipe->GetConfigurationDescriptor(Buffer,length,Index);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetConfigurationDescriptor] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getDescriptor
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jint Recipient, jbyte DescriptorType, jbyte DescriptorIndex, jshort LanguageId)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("GetDescriptor: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("GetDescriptor: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDescriptor\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (sizeof(USB_CONFIGURATION_DESCRIPTOR) <= env->GetArrayLength(bytearr)) {
					USB_CONFIGURATION_DESCRIPTOR* Buffer = (USB_CONFIGURATION_DESCRIPTOR*)env->GetByteArrayElements(bytearr,JNI_FALSE);
					Status = UsbioPipe->GetDescriptor(Buffer,length,(USBIO_REQUEST_RECIPIENT)Recipient,DescriptorType,DescriptorIndex,LanguageId);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetDescriptor] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_setDescriptor
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jint Recipient, jbyte DescriptorType, jbyte DescriptorIndex, jshort LanguageId)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("SetDescriptor: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("SetDescriptor: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetDescriptor\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (sizeof(USB_CONFIGURATION_DESCRIPTOR) <= env->GetArrayLength(bytearr)) {
					USB_CONFIGURATION_DESCRIPTOR* Buffer = (USB_CONFIGURATION_DESCRIPTOR*)env->GetByteArrayElements(bytearr,JNI_FALSE);
					Status = UsbioPipe->SetDescriptor(Buffer,length,(USBIO_REQUEST_RECIPIENT)Recipient,DescriptorType,DescriptorIndex,LanguageId);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("SetDescriptor] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_writeSync
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count,jint Timeout)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("WriteSync: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("WriteSync: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(8,tprint("[WriteSync\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			TRACE(5,tprint("WriteSync(%02X)\n",UsbioPipe->mDbgEndpointAddress));
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if ((jsize)length <= env->GetArrayLength(bytearr)) {
					TRACE(8,tprint("WriteSync: Length: %u, Timeout: %u\n",length,Timeout));
					jbyte* Buffer = env->GetByteArrayElements(bytearr,JNI_FALSE);
					LeaveCriticalSection(&CritSect);
					Status = UsbioPipe->WriteSync(Buffer,length,Timeout);
					EnterCriticalSection(&CritSect);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(bytearr,Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(8,tprint("WriteSync] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_bind
(JNIEnv *env, jobject obj, jobject Handle, jint DeviceNumber, jbyte EndpointAddress,jint DeviceList,jstring InterfaceGuid)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;
	HRESULT result;

	if (InterfaceGuid == NULL) {
		TRACE(1,tprint("Bind: InterfaceGuid is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[Bind Address:%02x\n",EndpointAddress & 0xff));

	GUID Guid;

	WCHAR* guidWStr = (WCHAR*)env->GetStringChars(InterfaceGuid, 0);
	result = ::CLSIDFromString(guidWStr,&Guid);

	if (result != NOERROR) {
		TRACE(2,tprint("Bind: Error convert String to Guid."));
		// error convert string to guid
		Status = USBIO_ERR_FAILED;
	} else {
		// get Handle
		getObjHandle(env,Handle,&value);
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			#ifdef _DEBUG
				UsbioPipe->mDbgEndpointAddress = EndpointAddress & 0xFF;
			#endif
			TRACE(4,tprint("Bind: EndpointAddress: %u, DeviceNumber: %i\n",EndpointAddress,DeviceNumber));
			Status = UsbioPipe->Bind(DeviceNumber,EndpointAddress&0xFF,(void*)DeviceList,&Guid);
		} else {
			while (usb_instances[globalcounter] != NULL) {
				globalcounter++;
				if (globalcounter == 0) {
					globalcounter++;
				}
			}
			CPipe* UsbioPipe = new CPipe();
			if (UsbioPipe != NULL) {
				#ifdef _DEBUG
					UsbioPipe->mDbgEndpointAddress = EndpointAddress;
				#endif
				TRACE(4,tprint("Bind: EndpointAddress: %u, DeviceNumber: %i\n",EndpointAddress,DeviceNumber));
				Status = UsbioPipe->Bind(DeviceNumber,EndpointAddress,(void*)DeviceList,&Guid);
				
				if (Status == USBIO_ERR_SUCCESS) {
					TRACE(4,tprint("Bind: new CPipe instance globalcounter: %i\n",globalcounter));
					usb_instances[globalcounter] = UsbioPipe;
					if (!setObjHandle(env,&Handle,globalcounter)) {
						Status = USBIO_ERR_FAILED;
						usb_instances.erase(globalcounter);
						delete UsbioPipe;
					}
				} else {
					delete UsbioPipe;
				}
			} else {
				Status = USBIO_ERR_NO_MEMORY;
			}
		}
	}
	
	env->ReleaseStringChars(InterfaceGuid,guidWStr);

	TRACE(4,tprint("Bind] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
} // Java_de_thesycon_usbio_UsbIoPipe_Bind


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_unbind
(JNIEnv *env, jobject obj, jobject Handle)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[Unbind\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			TRACE(5,tprint("Unbind(%02X)\n",UsbioPipe->mDbgEndpointAddress));
			Status = UsbioPipe->Unbind();
		}
	}
	TRACE(4,tprint("Unbind] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_resetPipe
(JNIEnv *env, jobject obj, jobject Handle)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[ResetPipe\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->ResetPipe();
		}
	}
	TRACE(4,tprint("ResetPipe] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_abortPipe
(JNIEnv *env, jobject obj, jobject Handle)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[AbortPipe\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->AbortPipe();
		}
	}
	TRACE(4,tprint("AbortPipe] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_getPipeParameters
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("GetPipeParameters: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetPipeParameters\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(bytearr) == sizeof(USBIO_PIPE_PARAMETERS)) {
				USBIO_PIPE_PARAMETERS* Buffer = (USBIO_PIPE_PARAMETERS*)env->GetByteArrayElements(bytearr,JNI_FALSE);
				Status = UsbioPipe->GetPipeParameters(Buffer);
				env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetPipeParameters] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_setPipeParameters
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("SetPipeParameters: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetPipeParameters\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(bytearr) == sizeof(USBIO_PIPE_PARAMETERS)) {
				USBIO_PIPE_PARAMETERS* Buffer = (USBIO_PIPE_PARAMETERS*)env->GetByteArrayElements(bytearr,JNI_FALSE);
				Status = UsbioPipe->SetPipeParameters(Buffer);
				env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("SetPipeParameters] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getConfiguration
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("GetConfiguration: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetConfiguration\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(bytearr) == 1) {
				UCHAR* Buffer = (UCHAR*)env->GetByteArrayElements(bytearr,JNI_FALSE);
				Status = UsbioPipe->GetConfiguration(*Buffer);
				env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetConfiguration] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getDevicePowerState
(JNIEnv *env, jobject obj, jobject Handle, jintArray DevicePowerState)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (DevicePowerState == NULL) {
		TRACE(1,tprint("GetDevicePowerState: DevicePowerState is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetDevicePowerState\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(DevicePowerState) == 1) {
				USBIO_DEVICE_POWER_STATE* Buffer = (USBIO_DEVICE_POWER_STATE*)env->GetIntArrayElements(DevicePowerState,JNI_FALSE);
				Status = UsbioPipe->GetDevicePowerState(*Buffer);
				env->ReleaseIntArrayElements(DevicePowerState,(jint*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetDevicePowerState] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_setDevicePowerState
(JNIEnv *env, jobject obj, jobject Handle, jint DevicePowerState)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetDevicePowerState\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->SetDevicePowerState((USBIO_DEVICE_POWER_STATE)DevicePowerState);
		}
	}
	TRACE(4,tprint("SetDevicePowerState] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getInterface
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray AlternateSetting, jshort Interface)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (AlternateSetting == NULL) {
		TRACE(1,tprint("GetInterface: AlternateSetting is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetInterface\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(AlternateSetting) == 1) {
				UCHAR* Buffer = (UCHAR*)env->GetByteArrayElements(AlternateSetting,JNI_FALSE);
				Status = UsbioPipe->GetInterface(*Buffer, Interface);
				env->ReleaseByteArrayElements(AlternateSetting,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetInterface] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getStatus
(JNIEnv *env, jobject obj, jobject Handle, jshortArray StatusValue, jint Recipient, jshort index)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (StatusValue == NULL) {
		TRACE(1,tprint("GetStatus: StatusValue is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetStatus\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(StatusValue) == 1) {
				USHORT* Buffer = (USHORT*)env->GetShortArrayElements(StatusValue,JNI_FALSE);
				Status = UsbioPipe->GetStatus(*Buffer, (USBIO_REQUEST_RECIPIENT)Recipient, index);
				env->ReleaseShortArrayElements(StatusValue,(jshort*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetStatus] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_getCurrentFrameNumber
(JNIEnv *env, jobject obj, jobject Handle, jintArray FrameNumber)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (FrameNumber == NULL) {
		TRACE(1,tprint("GetCurrentFrameNumber: FrameNumber is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[GetCurrentFrameNumber\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(FrameNumber) == 1) {
				DWORD* Buffer = (DWORD*)env->GetIntArrayElements(FrameNumber,JNI_FALSE);
				Status = UsbioPipe->GetCurrentFrameNumber(*Buffer);
				env->ReleaseIntArrayElements(FrameNumber,(jint*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("GetCurrentFrameNumber] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_queryPipeStatistics
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jint flags)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("QueryPipeStatistics: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(5,tprint("[QueryPipeStatistics\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(bytearr) == sizeof(USBIO_PIPE_STATISTICS)) {
				USBIO_PIPE_STATISTICS* Buffer = (USBIO_PIPE_STATISTICS*)env->GetByteArrayElements(bytearr,JNI_FALSE);
				Status = UsbioPipe->QueryPipeStatistics(Buffer,flags);
				env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(5,tprint("QueryPipeStatistics] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_resetPipeStatistics
(JNIEnv *env, jobject obj, jobject Handle)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(5,tprint("[ResetPipeStatistics\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->ResetPipeStatistics();
		}
	}
	TRACE(5,tprint("ResetPipeStatistics] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_setupPipeStatistics
(JNIEnv *env, jobject obj, jobject Handle, jint AveragingInterval)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(5,tprint("[SetupPipeStatistics\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->SetupPipeStatistics(AveragingInterval);
		}
	}
	TRACE(5,tprint("SetupPipeStatistics] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_clearFeature
(JNIEnv *env, jobject obj, jobject Handle, jint Recipient, jshort FeatureSelector, jshort Index)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[ClearFeature\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->ClearFeature((USBIO_REQUEST_RECIPIENT)Recipient, FeatureSelector, Index);
		}
	}
	TRACE(4,tprint("ClearFeature] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_setFeature
(JNIEnv *env, jobject obj, jobject Handle, jint Recipient, jshort FeatureSelector, jshort Index)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetFeature\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			Status = UsbioPipe->SetFeature((USBIO_REQUEST_RECIPIENT)Recipient, FeatureSelector, Index);
		}
	}
	TRACE(4,tprint("SetFeature] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIo_setInterface
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("SetInterface: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[SetInterface\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(bytearr) == sizeof(USBIO_INTERFACE_SETTING)) {
				USBIO_INTERFACE_SETTING* Buffer = (USBIO_INTERFACE_SETTING*)env->GetByteArrayElements(bytearr,JNI_FALSE);
				Status = UsbioPipe->SetInterface(Buffer);
				env->ReleaseByteArrayElements(bytearr,(jbyte*)Buffer,0);
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("SetInterface] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_read
(JNIEnv *env, jobject obj, jobject Handle, jobject Buffer)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;
	CUsbIoBufEx* Buf;
	void* Mem;

	if (Buffer == NULL) {
		TRACE(1,tprint("Read: Buffer is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(7,tprint("[Read\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			TRACE(7,tprint("Read(%02X)\n",UsbioPipe->mDbgEndpointAddress));
			jclass cls = env->GetObjectClass(Buffer);
			if (cls != NULL) {
				jfieldID BufferMemID = env->GetFieldID(cls,"BufferMem","[B");
				jfieldID BufferSizeID = env->GetFieldID(cls,"Size","I");
				jfieldID BytesToTransferID = env->GetFieldID(cls,"NumberOfBytesToTransfer","I");
				jfieldID BufferHandleID = env->GetFieldID(cls,"Handle","I");

				jbyteArray bytearr = (jbyteArray)env->GetObjectField(Buffer,BufferMemID);
				jint Size = env->GetIntField(Buffer,BufferSizeID);
				jint BytesToTransfer = env->GetIntField(Buffer,BytesToTransferID);
				
				if (env->GetArrayLength(bytearr) >= Size) {
					if ( UsbioPipe->BufPool.CurrentCount() == 0) {
						UsbioPipe->BufPool.IncreaseBufPoolSize(5);
					}

					Buf = UsbioPipe->BufPool.Get();
					if (Buf == NULL) {
						Status = USBIO_ERR_FAILED;
					} else {
						TRACE(7,tprint("Read BytesToTransfer: %i, Size: %i\n",BytesToTransfer,Size));
						env->SetIntField(Buffer,BufferHandleID,(jint)Buf);

						Mem = (void*)env->GetByteArrayElements(bytearr,JNI_FALSE);
						Buf->setBufMemPointer(Mem);
						Buf->setBufMemSize(Size);
						Buf->NumberOfBytesToTransfer = BytesToTransfer;
						Buf->Context = (DWORD)Buffer;
						UsbioPipe->Read(Buf);
					}
				} else {
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		} else {
			TRACE(2, tprint("Read: UsbioPipe is NULL\n"));
		}
	}
	TRACE(7,tprint("Read] (%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_write
(JNIEnv *env, jobject obj, jobject Handle, jobject Buffer)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;
	CUsbIoBufEx* Buf;
	void* Mem;

	if (Buffer == NULL) {
		TRACE(1,tprint("Write: Buffer is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(8,tprint("[Write\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			TRACE(8,tprint("Write(%02X)\n",UsbioPipe->mDbgEndpointAddress));
			jclass cls = env->GetObjectClass(Buffer);
			if (cls != NULL) {
				jfieldID BufferMemID = env->GetFieldID(cls,"BufferMem","[B");
				jfieldID BufferSizeID = env->GetFieldID(cls,"Size","I");
				jfieldID BytesToTransferID = env->GetFieldID(cls,"NumberOfBytesToTransfer","I");
				jfieldID BufferHandleID = env->GetFieldID(cls,"Handle","I");

				jbyteArray bytearr = (jbyteArray)env->GetObjectField(Buffer,BufferMemID);
				jint Size = env->GetIntField(Buffer,BufferSizeID);
				jint BytesToTransfer = env->GetIntField(Buffer,BytesToTransferID);
				
				if (env->GetArrayLength(bytearr) >= Size) {
					if ( UsbioPipe->BufPool.CurrentCount() == 0) {
						UsbioPipe->BufPool.IncreaseBufPoolSize(5);
					}

					Buf = UsbioPipe->BufPool.Get();
					if (Buf == NULL) {
						Status = USBIO_ERR_FAILED;
					} else {
						TRACE(8,tprint("Write BytesToTransfer: %i, Size: %i\n",BytesToTransfer,Size));
						env->SetIntField(Buffer,BufferHandleID,(jint)Buf);
						
						Mem = (void*)env->GetByteArrayElements(bytearr,JNI_FALSE);
						Buf->setBufMemPointer(Mem);
						Buf->setBufMemSize(Size);
						Buf->NumberOfBytesToTransfer = BytesToTransfer;
						Buf->Context = (DWORD)Buffer;
						UsbioPipe->Write(Buf);
					}
				} else {
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		} else {
			TRACE(2, tprint("Write: UsbioPipe is NULL\n"));
		}
	}
	TRACE(8,tprint("Write] (%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_waitForCompletion
(JNIEnv *env, jobject obj, jobject Handle, jobject Buffer, jint timeout)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;
	CUsbIoBufEx* Buf;
	void* Mem;

	if (Buffer == NULL) {
		TRACE(1,tprint("WaitForCompletion: Buffer is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(9,tprint("[WaitForCompletion\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			TRACE(9,tprint("WaitForCompletion(%02X)\n",UsbioPipe->mDbgEndpointAddress));

			jclass cls = env->GetObjectClass(Buffer);
			if (cls != NULL) {
				jfieldID BufferMemID = env->GetFieldID(cls,"BufferMem","[B");
				jfieldID BufferStatusID = env->GetFieldID(cls,"Status","I");
				jfieldID BytesTransferredID = env->GetFieldID(cls,"BytesTransferred","I");
				jfieldID BufferHandleID = env->GetFieldID(cls,"Handle","I");

				Buf = (CUsbIoBufEx*)env->GetIntField(Buffer,BufferHandleID);
				if (Buf != NULL) {
					LeaveCriticalSection(&CritSect);
					Status = UsbioPipe->WaitForCompletion(Buf,timeout);
					EnterCriticalSection(&CritSect);
					Mem = Buf->getBufMemPointer();
					jbyteArray bytearr = (jbyteArray)env->GetObjectField(Buffer,BufferMemID);

					env->ReleaseByteArrayElements(bytearr,(jbyte*)Mem,0);

					env->SetIntField(Buffer,BytesTransferredID,Buf->BytesTransferred);
					env->SetIntField(Buffer,BufferStatusID,Buf->Status);

					TRACE(9,tprint("WaitForCompletion BytesTransferred: %u, Status: 0x%08X\n",Buf->BytesTransferred,Buf->Status));

					Buf->setBufMemPointer(NULL);
					Buf->setBufMemSize(0);
					UsbioPipe->BufPool.Put(Buf);

				} else {
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		} else {
			TRACE(2, tprint("WaitForCompletion: UsbioPipe is NULL\n"));
		}
	}
	TRACE(9,tprint("WaitForCompletion] (%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}



JNIEXPORT jstring JNICALL Java_de_thesycon_usbio_UsbIo_errorText
(JNIEnv *env, jclass obj, jint ErrorCode)
{
	char buffer[MAX_ERROR_TEXT_SIZE];

	TRACE(4,tprint("[ErrorText\n"));
	// call static ErrorText function
	CPipe::ErrorText(buffer,MAX_ERROR_TEXT_SIZE,ErrorCode);
	
	TRACE(4,tprint("ErrorText]\n"));
	return env->NewStringUTF(buffer);
}

void NotifyCallback(void *context,int function)
{
	JNIEnv *env = NULL;

	TRACE(6,tprint("NotifyCallback\n"));
	jobject obj = (jobject)context;

	vm->AttachCurrentThread((void**)&env,NULL);

	jclass cls = env->GetObjectClass(obj);
	jmethodID methodAdd = env->GetMethodID(cls,"onAdd","()V");
	jmethodID methodRemove = env->GetMethodID(cls,"onRemove","()V");

	switch (function) {
	case NOTIFY_ADD:
		if (methodAdd != NULL) {
			env->CallVoidMethod(obj,methodAdd);
		}
		break;
	case NOTIFY_REMOVE:
		if (methodRemove != NULL) {
			env->CallVoidMethod(obj,methodRemove);
		}
		break;
	default:
		TRACE(0,tprint("NotifyCallback:FATAL: unknown function code %x\n",function));
		break;
	}// switch

	vm->DetachCurrentThread();
} // NotifyCallback


JNIEXPORT jint JNICALL Java_de_thesycon_usbio_PnPNotify_enablePnPNotification
(JNIEnv *env, jobject obj,jstring InterfaceGuid, jobject Interface)
{
  DWORD Status = USBIO_ERR_SUCCESS;
	CThreadPnPNotify *Notify;
	HRESULT result;

	if (InterfaceGuid == NULL) {
		TRACE(1,tprint("EnablePnPNotification: InterfaceGuid is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(6,tprint("[EnablePnPNotification 0x%08X\n",Interface));

	GUID Guid;

	WCHAR* guidWStr = (WCHAR*)env->GetStringChars(InterfaceGuid, 0);
	result = ::CLSIDFromString(guidWStr,&Guid);
	
	if (result != NOERROR) {
		TRACE(2,tprint("EnablePnPNotification: Error convert String to Guid."));
		// error convert string to guid
		Status = USBIO_ERR_INVALID_PARAM;
	} else {
		if (!gGuidList.Lookup(Guid,&Notify)) {
			// create the new class instance of CThreadPnPNotify
			Notify = new CThreadPnPNotify;
			// add the pointer to the guid list
			gGuidList.Add(Guid,Notify);
			env->GetJavaVM(&vm);
			jobject object = env->NewGlobalRef(Interface);
			TRACE(6,tprint("EnablePnPNotification: RegisterCallback\n"));
			// register the callback function
			Notify->RegisterCallback(object,NotifyCallback);
			// give the guid in the created class instance
			Notify->SetGuid(Guid);
			// start thread
			if(!Notify->Start()) {
				env->DeleteGlobalRef(object);
				Status = USBIO_ERR_FAILED;
				gGuidList.Remove(Guid,&Notify);	//lint !e534
			}
		} else {
			Status = USBIO_ERR_FAILED;	
		}
	}

	TRACE(6,tprint("EnablePnPNotification] (0x%08X)\n",Status));

	env->ReleaseStringChars(InterfaceGuid,guidWStr);
	LeaveCriticalSection(&CritSect);

	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_PnPNotify_disablePnPNotification
(JNIEnv *env, jobject obj,jstring InterfaceGuid)
{
  DWORD Status;
	CThreadPnPNotify *Notify;
	HRESULT result;

	if (InterfaceGuid == NULL) {
		TRACE(1,tprint("DisablePnPNotification: InterfaceGuid is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	
	EnterCriticalSection(&CritSect);
	TRACE(6,tprint("[DisablePnPNotification\n"));

	GUID Guid;

	WCHAR* guidWStr = (WCHAR*)env->GetStringChars(InterfaceGuid, 0);
	result = ::CLSIDFromString(guidWStr,&Guid);

	if (result != NOERROR) {
		TRACE(2,tprint("DisablePnPNotification: Error convert String to Guid."));
		// error convert string to guid
		Status = USBIO_ERR_INVALID_PARAM;
	} else {
		// remove guid from the list
		if(gGuidList.Remove(Guid,&Notify)) {
			// stop thread
			Notify->Stop();
			jobject InterfaceObj = (jobject)Notify->GetContext();
			if (InterfaceObj != NULL) {
				env->DeleteGlobalRef(InterfaceObj);
			}
			// destroy class
			delete Notify;
		}
		Status = USBIO_ERR_SUCCESS;
	}

	TRACE(6,tprint("DisablePnPNotification] (0x%08X)\n",Status));

	env->ReleaseStringChars(InterfaceGuid,guidWStr);
	LeaveCriticalSection(&CritSect);

	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_pipeControlTransferIn
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jbyteArray ControlTransfer)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("PipeControlTransferIn: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("PipeControlTransferIn: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (ControlTransfer == NULL) {
		TRACE(1,tprint("PipeControlTransferIn: ControlTransfer is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[PipeControlTransferIn\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (((jsize)length <= env->GetArrayLength(bytearr)) && (sizeof(USBIO_PIPE_CONTROL_TRANSFER) <= env->GetArrayLength(ControlTransfer))) {
					jbyte* Buffer = env->GetByteArrayElements(bytearr,JNI_FALSE);
					USBIO_PIPE_CONTROL_TRANSFER* Req = (USBIO_PIPE_CONTROL_TRANSFER*)env->GetByteArrayElements(ControlTransfer,JNI_FALSE);
					Status = UsbioPipe->PipeControlTransferIn(Buffer,length,Req);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(ControlTransfer,(jbyte*)Req,0);
					env->ReleaseByteArrayElements(bytearr,Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("PipeControlTransferIn] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}

JNIEXPORT jint JNICALL Java_de_thesycon_usbio_UsbIoPipe_pipeControlTransferOut
(JNIEnv *env, jobject obj, jobject Handle, jbyteArray bytearr, jintArray count, jbyteArray ControlTransfer)
{
	DWORD Status = USBIO_ERR_FAILED;
	int value;

	if (bytearr == NULL) {
		TRACE(1,tprint("PipeControlTransferOut: bytearr is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (count == NULL) {
		TRACE(1,tprint("PipeControlTransferOut: count is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}
	if (ControlTransfer == NULL) {
		TRACE(1,tprint("PipeControlTransferOut: ControlTransfer is NULL."));
		return USBIO_ERR_INVALID_PARAM;
	}

	EnterCriticalSection(&CritSect);
	TRACE(4,tprint("[PipeControlTransferOut\n"));
	// get Handle
	if (getObjHandle(env,Handle,&value)) {
		// get pointer to the UsbIoPipe class
		CPipe* UsbioPipe = usb_instances[value];
		if (UsbioPipe != NULL) {
			if (env->GetArrayLength(count) == 1) {
				unsigned long length;
				env->GetIntArrayRegion(count,0,1,(long*)&length);
				if (((jsize)length <= env->GetArrayLength(bytearr)) && (sizeof(USBIO_PIPE_CONTROL_TRANSFER) <= env->GetArrayLength(ControlTransfer))) {
					jbyte* Buffer = env->GetByteArrayElements(bytearr,JNI_FALSE);
					USBIO_PIPE_CONTROL_TRANSFER* Req = (USBIO_PIPE_CONTROL_TRANSFER*)env->GetByteArrayElements(ControlTransfer,JNI_FALSE);
					Status = UsbioPipe->PipeControlTransferOut(Buffer,length,Req);
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					env->ReleaseByteArrayElements(ControlTransfer,(jbyte*)Req,0);
					env->ReleaseByteArrayElements(bytearr,Buffer,0);
				} else {
					length = 0;
					env->SetIntArrayRegion(count,0,1,(long*)&length);
					Status = USBIO_ERR_INVALID_INBUFFER;
				}
			} else {
				Status = USBIO_ERR_INVALID_INBUFFER;
			}
		}
	}
	TRACE(4,tprint("PipeControlTransferOut] (0x%08X)\n",Status));
	LeaveCriticalSection(&CritSect);
	// return status
	return Status;
}

/***************************** EOF **************************************/
