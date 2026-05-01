
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include <rpc.h>
#include <rpcndr.h>

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif /*COM_NO_WINDOWS_H*/
#ifndef __microsoft2Eui2Examl2Examltypeinfo_h__
#define __microsoft2Eui2Examl2Examltypeinfo_h__
#ifndef __microsoft2Eui2Examl2Examltypeinfo_p_h__
#define __microsoft2Eui2Examl2Examltypeinfo_p_h__


#pragma once

// Ensure that the setting of the /ns_prefix command line switch is consistent for all headers.
// If you get an error from the compiler indicating "warning C4005: 'CHECK_NS_PREFIX_STATE': macro redefinition", this
// indicates that you have included two different headers with different settings for the /ns_prefix MIDL command line switch
#if !defined(DISABLE_NS_PREFIX_CHECKS)
#define CHECK_NS_PREFIX_STATE "always"
#endif // !defined(DISABLE_NS_PREFIX_CHECKS)


#pragma push_macro("MIDL_CONST_ID")
#undef MIDL_CONST_ID
#define MIDL_CONST_ID const __declspec(selectany)


//  API Contract Inclusion Definitions
#if !defined(SPECIFIC_API_CONTRACT_DEFINITIONS)
#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.UI.Xaml.Markup.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace XamlTypeInfo {
                    interface IXamlControlsXamlMetaDataProvider;
                } /* XamlTypeInfo */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider ABI::Microsoft::UI::Xaml::XamlTypeInfo::IXamlControlsXamlMetaDataProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace XamlTypeInfo {
                    interface IXamlControlsXamlMetaDataProviderStatics;
                } /* XamlTypeInfo */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics ABI::Microsoft::UI::Xaml::XamlTypeInfo::IXamlControlsXamlMetaDataProviderStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlMetadataProvider;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider ABI::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__

/*
 *
 * Interface Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProvider
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider
 *
 */
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_XamlTypeInfo_IXamlControlsXamlMetaDataProvider[] = L"Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace XamlTypeInfo {
                    MIDL_INTERFACE("17fa3f58-3472-5aa2-a0f8-1ab8a519573d")
                    IXamlControlsXamlMetaDataProvider : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IXamlControlsXamlMetaDataProvider = _uuidof(IXamlControlsXamlMetaDataProvider);
                } /* XamlTypeInfo */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProviderStatics
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider
 *
 */
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_XamlTypeInfo_IXamlControlsXamlMetaDataProviderStatics[] = L"Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProviderStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace XamlTypeInfo {
                    MIDL_INTERFACE("2d7eb3fd-ecdb-5084-b7e0-12f9598381ef")
                    IXamlControlsXamlMetaDataProviderStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Initialize(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlControlsXamlMetaDataProviderStatics = _uuidof(IXamlControlsXamlMetaDataProviderStatics);
                } /* XamlTypeInfo */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_INTERFACE_DEFINED__) */

/*
 *
 * Class Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider
 *
 * RuntimeClass can be activated.
 *
 * RuntimeClass contains static methods.
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProvider
 *    Microsoft.UI.Xaml.Markup.IXamlMetadataProvider ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_XamlTypeInfo_XamlControlsXamlMetaDataProvider_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_XamlTypeInfo_XamlControlsXamlMetaDataProvider_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_XamlTypeInfo_XamlControlsXamlMetaDataProvider[] = L"Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider";
#endif

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__

/*
 *
 * Interface Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProvider
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider
 *
 */
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_XamlTypeInfo_IXamlControlsXamlMetaDataProvider[] = L"Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProvider_INTERFACE_DEFINED__) */

/*
 *
 * Interface Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProviderStatics
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider
 *
 */
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_XamlTypeInfo_IXamlControlsXamlMetaDataProviderStatics[] = L"Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProviderStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Initialize)(__x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_Initialize(This) \
    ((This)->lpVtbl->Initialize(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CXamlTypeInfo_CIXamlControlsXamlMetaDataProviderStatics_INTERFACE_DEFINED__) */

/*
 *
 * Class Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider
 *
 * RuntimeClass can be activated.
 *
 * RuntimeClass contains static methods.
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.XamlTypeInfo.IXamlControlsXamlMetaDataProvider
 *    Microsoft.UI.Xaml.Markup.IXamlMetadataProvider ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_XamlTypeInfo_XamlControlsXamlMetaDataProvider_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_XamlTypeInfo_XamlControlsXamlMetaDataProvider_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_XamlTypeInfo_XamlControlsXamlMetaDataProvider[] = L"Microsoft.UI.Xaml.XamlTypeInfo.XamlControlsXamlMetaDataProvider";
#endif

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Examltypeinfo_p_h__

#endif // __microsoft2Eui2Examl2Examltypeinfo_h__
