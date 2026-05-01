

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

#ifndef __xamlom2Ewinui_h__
#define __xamlom2Ewinui_h__

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

#ifndef __IVisualTreeServiceCallback3_FWD_DEFINED__
#define __IVisualTreeServiceCallback3_FWD_DEFINED__
typedef interface IVisualTreeServiceCallback3 IVisualTreeServiceCallback3;

#endif 	/* __IVisualTreeServiceCallback3_FWD_DEFINED__ */


#ifndef __IXamlDiagnostics2_FWD_DEFINED__
#define __IXamlDiagnostics2_FWD_DEFINED__
typedef interface IXamlDiagnostics2 IXamlDiagnostics2;

#endif 	/* __IXamlDiagnostics2_FWD_DEFINED__ */


/* header files for imported files */
#include "XamlOM.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_XamlOM2EWinUI_0000_0000 */
/* [local] */ 

#pragma region Application Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#pragma warning(push)
#pragma warning(disable:4668) 
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
// Win32 API definitions
#define E_NOTFOUND HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
#define E_UNKNOWNTYPE MAKE_HRESULT(SEVERITY_ERROR, FACILITY_XAML, 40L)


extern RPC_IF_HANDLE __MIDL_itf_XamlOM2EWinUI_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_XamlOM2EWinUI_0000_0000_v0_0_s_ifspec;

#ifndef __IVisualTreeServiceCallback3_INTERFACE_DEFINED__
#define __IVisualTreeServiceCallback3_INTERFACE_DEFINED__

/* interface IVisualTreeServiceCallback3 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IVisualTreeServiceCallback3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("765DF10A-08C8-46B0-82C9-297CFC4CEAD7")
    IVisualTreeServiceCallback3 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnXamlRootChange( 
            /* [in] */ InstanceHandle root,
            /* [in] */ VisualMutationType mutationType) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVisualTreeServiceCallback3Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __RPC__in IVisualTreeServiceCallback3 * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __RPC__in IVisualTreeServiceCallback3 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __RPC__in IVisualTreeServiceCallback3 * This);
        
        DECLSPEC_XFGVIRT(IVisualTreeServiceCallback3, OnXamlRootChange)
        HRESULT ( STDMETHODCALLTYPE *OnXamlRootChange )( 
            __RPC__in IVisualTreeServiceCallback3 * This,
            /* [in] */ InstanceHandle root,
            /* [in] */ VisualMutationType mutationType);
        
        END_INTERFACE
    } IVisualTreeServiceCallback3Vtbl;

    interface IVisualTreeServiceCallback3
    {
        CONST_VTBL struct IVisualTreeServiceCallback3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisualTreeServiceCallback3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVisualTreeServiceCallback3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVisualTreeServiceCallback3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVisualTreeServiceCallback3_OnXamlRootChange(This,root,mutationType)	\
    ( (This)->lpVtbl -> OnXamlRootChange(This,root,mutationType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVisualTreeServiceCallback3_INTERFACE_DEFINED__ */


#ifndef __IXamlDiagnostics2_INTERFACE_DEFINED__
#define __IXamlDiagnostics2_INTERFACE_DEFINED__

/* interface IXamlDiagnostics2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IXamlDiagnostics2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("523A35EE-EB38-4AE6-A3E1-5B7D0D547BD0")
    IXamlDiagnostics2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetUiLayerForXamlRoot( 
            /* [in] */ InstanceHandle instanceHandle,
            /* [retval][out] */ __RPC__deref_out_opt IInspectable **ppLayer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HitTestForXamlRoot( 
            /* [in] */ InstanceHandle instanceHandle,
            /* [in] */ RECT rect,
            /* [out] */ __RPC__out unsigned int *pCount,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*pCount) InstanceHandle **ppInstanceHandles) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IXamlDiagnostics2Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __RPC__in IXamlDiagnostics2 * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __RPC__in IXamlDiagnostics2 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __RPC__in IXamlDiagnostics2 * This);
        
        DECLSPEC_XFGVIRT(IXamlDiagnostics2, GetUiLayerForXamlRoot)
        HRESULT ( STDMETHODCALLTYPE *GetUiLayerForXamlRoot )( 
            __RPC__in IXamlDiagnostics2 * This,
            /* [in] */ InstanceHandle instanceHandle,
            /* [retval][out] */ __RPC__deref_out_opt IInspectable **ppLayer);
        
        DECLSPEC_XFGVIRT(IXamlDiagnostics2, HitTestForXamlRoot)
        HRESULT ( STDMETHODCALLTYPE *HitTestForXamlRoot )( 
            __RPC__in IXamlDiagnostics2 * This,
            /* [in] */ InstanceHandle instanceHandle,
            /* [in] */ RECT rect,
            /* [out] */ __RPC__out unsigned int *pCount,
            /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*pCount) InstanceHandle **ppInstanceHandles);
        
        END_INTERFACE
    } IXamlDiagnostics2Vtbl;

    interface IXamlDiagnostics2
    {
        CONST_VTBL struct IXamlDiagnostics2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXamlDiagnostics2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IXamlDiagnostics2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IXamlDiagnostics2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IXamlDiagnostics2_GetUiLayerForXamlRoot(This,instanceHandle,ppLayer)	\
    ( (This)->lpVtbl -> GetUiLayerForXamlRoot(This,instanceHandle,ppLayer) ) 

#define IXamlDiagnostics2_HitTestForXamlRoot(This,instanceHandle,rect,pCount,ppInstanceHandles)	\
    ( (This)->lpVtbl -> HitTestForXamlRoot(This,instanceHandle,rect,pCount,ppInstanceHandles) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXamlDiagnostics2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_XamlOM2EWinUI_0000_0002 */
/* [local] */ 

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */ 
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_XamlOM2EWinUI_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_XamlOM2EWinUI_0000_0002_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


