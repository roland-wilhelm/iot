/************************************************************************
 *
 *  Module:       CRegAcc.cpp
 *  Long name:    Registry Access
 *  Description:  covers the access to registry key's
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include "stdafx.h"

CRegAcc::CRegAcc()
{
	mKey = NULL;
}


CRegAcc::~CRegAcc()
{
	CloseKey();
	mKey = NULL;
}



// open a key, create it if Create is true
// return true on success or false if error
bool 
CRegAcc::OpenKey(HKEY Key, LPCTSTR SubKey, bool Create /*= false*/)
{
	LONG res;
	bool ret;

	if (mKey != NULL) {
		CloseKey();
	}
	res =	RegOpenKeyEx(
				Key,								// handle to open key
				SubKey,							// subkey name
				0,									// reserved
				KEY_READ|KEY_WRITE,			// security access mask
				&mKey								// handle to open key
			);
	if (res != ERROR_SUCCESS) {
		// error
		if (Create) {
			// Try to create the key
			res = RegCreateKeyEx(
							Key,                      // handle to open key
							SubKey,                   // subkey name
							0,												// reserved
							NULL,                     // class string
							REG_OPTION_NON_VOLATILE,	// special options
							KEY_READ|KEY_WRITE,           // desired security access
							NULL,											// inheritance
							&mKey,                    // key handle 
							NULL							        // disposition value buffer
						);
			if (res == ERROR_SUCCESS) {
				ret = true;
			} else {
				ret = false;
			}
		} else {
			ret = false;
		}
	} else {
		ret = true;
	}
	return ret;
} // OpenKey



// open a sub key, create it if Create is true
// return true on success or false if error
bool 
CRegAcc::OpenSubKey(LPCTSTR SubKey, bool Create /*= false*/)
{
	LONG res;
	bool ret;

	if (mKey == NULL) {
		return false;
	}
	res =	RegOpenKeyEx(
				mKey,								// handle to open key
				SubKey,							// subkey name
				0,									// reserved
				KEY_READ|KEY_WRITE,			// security access mask
				&mKey								// handle to open key
			);
	if (res != ERROR_SUCCESS) {
		// error
		if (Create) {
			// Try to create the key
			res = RegCreateKeyEx(
							mKey,                      // handle to open key
							SubKey,                   // subkey name
							0,												// reserved
							NULL,                     // class string
							REG_OPTION_NON_VOLATILE,	// special options
							KEY_READ|KEY_WRITE,           // desired security access
							NULL,											// inheritance
							&mKey,                    // key handle 
							NULL							        // disposition value buffer
						);
			if (res == ERROR_SUCCESS) {
				ret = true;
			} else {
				ret = false;
			}
		} else {
			ret = false;
		}
	} else {
		ret = true;
	}
	return ret;
} // OpenSubKey


bool 
CRegAcc::EnumKey(
	DWORD Index, 
	LPTSTR Key, 
	DWORD Size
	)
{	
	long ret;
	ret = RegEnumKey(
							mKey,     // handle to key to query
							Index, // index of subkey to query
							Key, // buffer for subkey name
							Size   // size of subkey name buffer
							);
	if (ret == ERROR_SUCCESS) {
		return true;
	} else {
		return false;
	}
} // EnumKey

bool CRegAcc::DeleteKey(
	LPTSTR SubKey
	)
{
	long ret;
	ret = RegDeleteKey(mKey,SubKey);
	if (ret == ERROR_SUCCESS) {
		return true;
	} else {
		return false;
	}
} // DeleteKey


void 
CRegAcc::CloseKey()
{
	if ( mKey != NULL ) {
		RegCloseKey(mKey); //lint !e534
		mKey = NULL;
	}
} // CloseKey


// reads a DWORD entry from a key
// returns true on success, value returned has been read from registry
// returns false on error, return value is the default value
bool 
CRegAcc::GetDword(LPCTSTR Name, DWORD *Value, DWORD DefaultValue /*= -1*/)
{
	bool ret;
	LONG res;
	DWORD Type;
	DWORD Size;

	if (mKey == NULL) {
		*Value = DefaultValue;
		return false;
	}
	Size = sizeof(DWORD);
	res = RegQueryValueEx(
							mKey,								// handle to key
							Name,								// value name
							NULL,								// reserved
							&Type,							// type buffer
							(LPBYTE)Value,			// data buffer
							&Size								// size of data buffer
						);
	if (res == ERROR_SUCCESS && Type ==  REG_DWORD) {
		ret = true;
	} else {
		*Value = DefaultValue;
		ret = false;
	}
	return ret;
} // GetDword



// set a DWORD value
bool 
CRegAcc::SetDword(LPCTSTR Name, DWORD Value)
{
	bool ret;
	LONG res;

	if (mKey == NULL) {
		return false;
	}
	res = RegSetValueEx(
				mKey,								// handle to key
				Name,								// value name
				0,									// reserved
				REG_DWORD,					// value type
				(LPBYTE)&Value,							// value data
				sizeof(DWORD)       // size of value data
			);
	if (res == ERROR_SUCCESS ) {
		ret = true;
	} else {
		ret = false;
	}
	return ret;
} // SetDword


bool 
CRegAcc::GetString(LPCTSTR Name, LPTSTR Value, DWORD Size, LPCTSTR DefaultValue /*= ""*/)
{
	bool ret;
	LONG res;
	DWORD Type;
	DWORD RetSize = Size;

	if (mKey == NULL) {
		strncpy(Value,DefaultValue,Size);
		Value[Size-1] = '\0';
		return false;
	}
	res = RegQueryValueEx(
							mKey,								// handle to key
							Name,								// value name
							NULL,								// reserved
							&Type,							// type buffer
							(LPBYTE)Value,			// data buffer
							&RetSize						// size of data buffer
						);
	if (res == ERROR_SUCCESS /*&& Type ==  REG_SZ*/) {
		// terminate the string 
		RetSize = min(RetSize,Size-1);
		Value[RetSize] = '\0';
		ret = true;
	} else {
		strncpy(Value,DefaultValue,Size);
		Value[Size-1] = '\0';
		ret = false;
	}
	return ret;
} // GetString

	
bool 
CRegAcc::SetString(LPCTSTR Name, LPCTSTR Value)
{
	bool ret;
	LONG res;

	if (mKey == NULL) {
		return false;
	}

	res = RegSetValueEx(
				mKey,								// handle to key
				Name,								// value name
				0,									// reserved
				REG_SZ,							// value type
				(LPBYTE)Value,							// value data
				strlen(Value)+sizeof(TCHAR)     // size of value data
			);
	if (res == ERROR_SUCCESS ) {
		ret = true;
	} else {
		ret = false;
	}
	return ret;
} // SetString

/*****************************  EOF ******************************/



