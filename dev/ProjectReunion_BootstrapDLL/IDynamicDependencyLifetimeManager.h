

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for IDynamicDependencyLifetimeManager.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
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

#ifndef __IDynamicDependencyLifetimeManager_h__
#define __IDynamicDependencyLifetimeManager_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDynamicDependencyLifetimeManager_FWD_DEFINED__
#define __IDynamicDependencyLifetimeManager_FWD_DEFINED__
typedef interface IDynamicDependencyLifetimeManager IDynamicDependencyLifetimeManager;

#endif 	/* __IDynamicDependencyLifetimeManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDynamicDependencyLifetimeManager_INTERFACE_DEFINED__
#define __IDynamicDependencyLifetimeManager_INTERFACE_DEFINED__

/* interface IDynamicDependencyLifetimeManager */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDynamicDependencyLifetimeManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("06F1BAD0-DD14-11d0-AB8F-0000C0148FDB")
    IDynamicDependencyLifetimeManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPackageFullName( 
            /* [retval][out] */ LPWSTR *packageFullName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDynamicDependencyLifetimeManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDynamicDependencyLifetimeManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDynamicDependencyLifetimeManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDynamicDependencyLifetimeManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IDynamicDependencyLifetimeManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *Shutdown )( 
            IDynamicDependencyLifetimeManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPackageFullName )( 
            IDynamicDependencyLifetimeManager * This,
            /* [retval][out] */ LPWSTR *packageFullName);
        
        END_INTERFACE
    } IDynamicDependencyLifetimeManagerVtbl;

    interface IDynamicDependencyLifetimeManager
    {
        CONST_VTBL struct IDynamicDependencyLifetimeManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDynamicDependencyLifetimeManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDynamicDependencyLifetimeManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDynamicDependencyLifetimeManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDynamicDependencyLifetimeManager_Initialize(This)	\
    ( (This)->lpVtbl -> Initialize(This) ) 

#define IDynamicDependencyLifetimeManager_Shutdown(This)	\
    ( (This)->lpVtbl -> Shutdown(This) ) 

#define IDynamicDependencyLifetimeManager_GetPackageFullName(This,packageFullName)	\
    ( (This)->lpVtbl -> GetPackageFullName(This,packageFullName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDynamicDependencyLifetimeManager_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


