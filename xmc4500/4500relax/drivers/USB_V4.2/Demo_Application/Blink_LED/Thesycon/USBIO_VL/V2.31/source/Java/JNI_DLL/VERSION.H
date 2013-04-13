/************************************************************************
 *
 *  Module:       VERSION.H
 *  Long name:    version information
 *  Description:  
 *
 *  Runtime Env.: 
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __VERSION_H__
#define __VERSION_H__

#include "usbiover.h"


#define PRODUCT_VERSION_MJ		USBIO_VERSION_MJ
#define PRODUCT_VERSION_MN		USBIO_VERSION_MN

#define MODULE_VERSION_MJ     USBIO_VERSION_MJ
#define MODULE_VERSION_MN     USBIO_VERSION_MN

// version string, e.g. "2.0"
#define VERSION_STR	\
    _TO_STRING_(MODULE_VERSION_MJ)     \
    "."                                \
    _TO_STRING_(MODULE_VERSION_MN)     \


// filename
#define VER_INTERNALNAME_STR        "USBIOJAVA"
#define VER_ORIGINALFILENAME_STR    "USBIOJAVA"

// description
#define VER_FILEDESCRIPTION_STR     "USBIOJAVA JNI DLL"


#define VER_PRODUCTNAME_STR         USBIO_PRODUCTNAME_STR

#define VER_COMPANYNAME_STR         USBIO_COMPANYNAME_STR
#define VER_LEGALCOPYRIGHT_STR      USBIO_COPYRIGHT_STR


#if DBG || defined(_DEBUG)
#define MODULE_VERSION_STRING   VERSION_STR " (debug)"
#define VER_BUILDTYPE_STRING		"debug"
#else
#define MODULE_VERSION_STRING   VERSION_STR
#define VER_BUILDTYPE_STRING		"release"
#endif

#define PRODUCT_VERSION_STRING	VERSION_STR


// support macro, converts symbolic name to string
// quite tricky
#define _TO_STRING_(x)     __TO_STRING__(x)
#define __TO_STRING__(x)   #x



#endif  // __VERSION_H__

/*************************** EOF **************************************/
