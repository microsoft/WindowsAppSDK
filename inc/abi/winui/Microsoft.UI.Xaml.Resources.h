
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
#ifndef __microsoft2Eui2Examl2Eresources_h__
#define __microsoft2Eui2Examl2Eresources_h__
#ifndef __microsoft2Eui2Examl2Eresources_p_h__
#define __microsoft2Eui2Examl2Eresources_p_h__


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
#if !defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)
#define MICROSOFT_UI_XAML_WINUICONTRACT_VERSION 0xa0000
#endif // defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)

#if !defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)
#define MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION 0xa0000
#endif // defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.UI.Xaml.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    interface ICustomXamlResourceLoader;
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoader

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    interface ICustomXamlResourceLoaderFactory;
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoaderFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    interface ICustomXamlResourceLoaderOverrides;
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoaderOverrides

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    interface ICustomXamlResourceLoaderStatics;
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoaderStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    class CustomXamlResourceLoader;
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoader[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoader";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    MIDL_INTERFACE("2832c2e5-2ace-5993-a173-3c9c3b992b2e")
                    ICustomXamlResourceLoader : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ICustomXamlResourceLoader = _uuidof(ICustomXamlResourceLoader);
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoaderFactory[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    MIDL_INTERFACE("174d49a6-e1e2-5f7b-a618-a8a953d1b5a0")
                    ICustomXamlResourceLoaderFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoader** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICustomXamlResourceLoaderFactory = _uuidof(ICustomXamlResourceLoaderFactory);
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoaderOverrides[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    MIDL_INTERFACE("84bb504c-6730-586a-bd04-9198264b2dc7")
                    ICustomXamlResourceLoaderOverrides : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetResource(
                            HSTRING resourceId,
                            HSTRING objectType,
                            HSTRING propertyName,
                            HSTRING propertyType,
                            IInspectable** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICustomXamlResourceLoaderOverrides = _uuidof(ICustomXamlResourceLoaderOverrides);
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoaderStatics[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Resources {
                    MIDL_INTERFACE("e08a5a92-b1a2-539a-9d4a-7994e4468cd7")
                    ICustomXamlResourceLoaderStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Current(
                            ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoader** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Current(
                            ABI::Microsoft::UI::Xaml::Resources::ICustomXamlResourceLoader* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICustomXamlResourceLoaderStatics = _uuidof(ICustomXamlResourceLoaderStatics);
                } /* Resources */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoader ** Default Interface **
 *    Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Resources_CustomXamlResourceLoader_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Resources_CustomXamlResourceLoader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Resources_CustomXamlResourceLoader[] = L"Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoader[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoader";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoaderFactory[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoaderOverrides[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverridesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetResource)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides* This,
        HSTRING resourceId,
        HSTRING objectType,
        HSTRING propertyName,
        HSTRING propertyType,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverridesVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverridesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_GetResource(This, resourceId, objectType, propertyName, propertyType, result) \
    ((This)->lpVtbl->GetResource(This, resourceId, objectType, propertyName, propertyType, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderOverrides_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Resources_ICustomXamlResourceLoaderStatics[] = L"Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader** value);
    HRESULT (STDMETHODCALLTYPE* put_Current)(__x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoader* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_get_Current(This, value) \
    ((This)->lpVtbl->get_Current(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_put_Current(This, value) \
    ((This)->lpVtbl->put_Current(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CResources_CICustomXamlResourceLoaderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoader ** Default Interface **
 *    Microsoft.UI.Xaml.Resources.ICustomXamlResourceLoaderOverrides
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Resources_CustomXamlResourceLoader_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Resources_CustomXamlResourceLoader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Resources_CustomXamlResourceLoader[] = L"Microsoft.UI.Xaml.Resources.CustomXamlResourceLoader";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Eresources_p_h__

#endif // __microsoft2Eui2Examl2Eresources_h__
