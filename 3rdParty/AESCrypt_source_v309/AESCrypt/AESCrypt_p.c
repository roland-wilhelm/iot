

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "AESCrypt.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _AESCrypt_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } AESCrypt_MIDL_TYPE_FORMAT_STRING;

typedef struct _AESCrypt_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } AESCrypt_MIDL_PROC_FORMAT_STRING;

typedef struct _AESCrypt_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } AESCrypt_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const AESCrypt_MIDL_TYPE_FORMAT_STRING AESCrypt__MIDL_TypeFormatString;
extern const AESCrypt_MIDL_PROC_FORMAT_STRING AESCrypt__MIDL_ProcFormatString;
extern const AESCrypt_MIDL_EXPR_FORMAT_STRING AESCrypt__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAESCryptShellExt_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAESCryptShellExt_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const AESCrypt_MIDL_PROC_FORMAT_STRING AESCrypt__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const AESCrypt_MIDL_TYPE_FORMAT_STRING AESCrypt__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAESCryptShellExt, ver. 0.0,
   GUID={0x3E228AAF,0x683B,0x44AD,{0xA8,0xDA,0x3F,0xC8,0xEF,0x25,0x00,0x8A}} */

#pragma code_seg(".orpc")
static const unsigned short IAESCryptShellExt_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAESCryptShellExt_ProxyInfo =
    {
    &Object_StubDesc,
    AESCrypt__MIDL_ProcFormatString.Format,
    &IAESCryptShellExt_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAESCryptShellExt_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    AESCrypt__MIDL_ProcFormatString.Format,
    &IAESCryptShellExt_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IAESCryptShellExtProxyVtbl = 
{
    0,
    &IID_IAESCryptShellExt,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IAESCryptShellExtStubVtbl =
{
    &IID_IAESCryptShellExt,
    &IAESCryptShellExt_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    AESCrypt__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _AESCrypt_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAESCryptShellExtProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _AESCrypt_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAESCryptShellExtStubVtbl,
    0
};

PCInterfaceName const _AESCrypt_InterfaceNamesList[] = 
{
    "IAESCryptShellExt",
    0
};


#define _AESCrypt_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _AESCrypt, pIID, n)

int __stdcall _AESCrypt_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_AESCrypt_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo AESCrypt_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _AESCrypt_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _AESCrypt_StubVtblList,
    (const PCInterfaceName * ) & _AESCrypt_InterfaceNamesList,
    0, /* no delegation */
    & _AESCrypt_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

