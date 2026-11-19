

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __microsoft2Eui2Examl2Ewindow_h__
#define __microsoft2Eui2Examl2Ewindow_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IWindowNative_FWD_DEFINED__
#define __IWindowNative_FWD_DEFINED__
typedef interface IWindowNative IWindowNative;

#endif 	/* __IWindowNative_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_microsoft2Eui2Examl2Ewindow_0000_0000 */
/* [local] */ 

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)


extern RPC_IF_HANDLE __MIDL_itf_microsoft2Eui2Examl2Ewindow_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_microsoft2Eui2Examl2Ewindow_0000_0000_v0_0_s_ifspec;

#ifndef __IWindowNative_INTERFACE_DEFINED__
#define __IWindowNative_INTERFACE_DEFINED__

/* interface IWindowNative */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IWindowNative;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EECDBF0E-BAE9-4CB6-A68E-9598E1CB57BB")
    IWindowNative : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WindowHandle( 
            /* [retval][out] */ HWND *hWnd) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWindowNativeVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWindowNative * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWindowNative * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWindowNative * This);
        
        DECLSPEC_XFGVIRT(IWindowNative, get_WindowHandle)
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WindowHandle )( 
            IWindowNative * This,
            /* [retval][out] */ HWND *hWnd);
        
        END_INTERFACE
    } IWindowNativeVtbl;

    interface IWindowNative
    {
        CONST_VTBL struct IWindowNativeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWindowNative_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWindowNative_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWindowNative_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWindowNative_get_WindowHandle(This,hWnd)	\
    ( (This)->lpVtbl -> get_WindowHandle(This,hWnd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWindowNative_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_microsoft2Eui2Examl2Ewindow_0000_0001 */
/* [local] */ 

#endif // NTDDI_VERSION >= NTDDI_WIN10_RS4


extern RPC_IF_HANDLE __MIDL_itf_microsoft2Eui2Examl2Ewindow_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_microsoft2Eui2Examl2Ewindow_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


