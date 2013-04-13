/************************************************************************
 *
 *  Module:       CRegAcc.h
 *  Long name:    Registry Access
 *  Description:  covers the access to registry key's
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/


class CRegAcc
{
public:
	CRegAcc();
	~CRegAcc();

	// open a key, create it if Create is true
	// return true on success or false if error
	bool OpenKey(HKEY Key, LPCTSTR SubKey, bool Create = false);
	// the class must be opened befor
	bool OpenSubKey(LPCTSTR SubKey, bool Create = false);

	void CloseKey();

	bool EnumKey(DWORD Index, LPTSTR Value, DWORD Size);
	bool DeleteKey(LPTSTR SubKey);

	// reads a DWORD entry from a key
	// returns true on success, value returned has been read from registry
	// returns false on error, return value is the default value
	bool GetDword(LPCTSTR Name, DWORD *Value, DWORD DefaultValue = (DWORD)-1);

	// set a DWORD value
	bool SetDword(LPCTSTR Name, DWORD Value);

	// get or set a string in registry 
	bool GetString(LPCTSTR Name, LPTSTR Value, DWORD Size, LPCTSTR DefaultValue = "");
	bool SetString(LPCTSTR Name, LPCTSTR Value);

	// return the key
	HKEY GetKey() { return mKey;};
	
private:
	HKEY mKey;
};
