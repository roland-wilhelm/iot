

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Mar 25 08:11:30 2013
 */
/* Compiler settings for AESCrypt.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AESCrypt_h__
#define __AESCrypt_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAESCryptShellExt_FWD_DEFINED__
#define __IAESCryptShellExt_FWD_DEFINED__
typedef interface IAESCryptShellExt IAESCryptShellExt;
#endif 	/* __IAESCryptShellExt_FWD_DEFINED__ */


#ifndef __AESCryptShellExtCom_FWD_DEFINED__
#define __AESCryptShellExtCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class AESCryptShellExtCom AESCryptShellExtCom;
#else
typedef struct AESCryptShellExtCom AESCryptShellExtCom;
#endif /* __cplusplus */

#endif 	/* __AESCryptShellExtCom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAESCryptShellExt_INTERFACE_DEFINED__
#define __IAESCryptShellExt_INTERFACE_DEFINED__

/* interface IAESCryptShellExt */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAESCryptShellExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E228AAF-683B-44AD-A8DA-3FC8EF25008A")
    IAESCryptShellExt : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAESCryptShellExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAESCryptShellExt * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAESCryptShellExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAESCryptShellExt * This);
        
        END_INTERFACE
    } IAESCryptShellExtVtbl;

    interface IAESCryptShellExt
    {
        CONST_VTBL struct IAESCryptShellExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAESCryptShellExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAESCryptShellExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAESCryptShellExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAESCryptShellExt_INTERFACE_DEFINED__ */



#ifndef __AESCryptLib_LIBRARY_DEFINED__
#define __AESCryptLib_LIBRARY_DEFINED__

/* library AESCryptLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AESCryptLib;

EXTERN_C const CLSID CLSID_AESCryptShellExtCom;

#ifdef __cplusplus

class DECLSPEC_UUID("35872D53-3BD4-45FA-8DB5-FFC47D4235E7")
AESCryptShellExtCom;
#endif
#endif /* __AESCryptLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


