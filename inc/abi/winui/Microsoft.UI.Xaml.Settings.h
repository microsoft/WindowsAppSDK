
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
#ifndef __microsoft2Eui2Examl2Esettings_h__
#define __microsoft2Eui2Examl2Esettings_h__
#ifndef __microsoft2Eui2Examl2Esettings_p_h__
#define __microsoft2Eui2Examl2Esettings_p_h__


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
#define MICROSOFT_UI_XAML_WINUICONTRACT_VERSION 0xb0000
#endif // defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)

#if !defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)
#define MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION 0xb0000
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
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Settings {
                    interface IXamlOptionalChanges;
                } /* Settings */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges ABI::Microsoft::UI::Xaml::Settings::IXamlOptionalChanges

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Settings {
                    interface IXamlOptionalChangesStatics;
                } /* Settings */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics ABI::Microsoft::UI::Xaml::Settings::IXamlOptionalChangesStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Settings {
                    typedef enum XamlChangeId : int XamlChangeId;
                } /* Settings */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Settings.XamlChangeId
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Settings {
                    enum XamlChangeId : int
                    {
                        XamlChangeId__Reserved = 0,
                        XamlChangeId_IconNoGridOptimization = 61276805,
                        XamlChangeId_OptimizeApplyStyles = 61697456,
                        XamlChangeId_DefaultStyleOptimizations = 60995620,
                        XamlChangeId_DeferContextFlyoutInit = 61098986,
                    };
                } /* Settings */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.UI.Xaml.Settings.IXamlOptionalChanges
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Settings.XamlOptionalChanges
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Settings_IXamlOptionalChanges[] = L"Microsoft.UI.Xaml.Settings.IXamlOptionalChanges";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Settings {
                    MIDL_INTERFACE("387572ae-ac51-5cb0-8317-2d6e118bea6a")
                    IXamlOptionalChanges : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IXamlOptionalChanges = _uuidof(IXamlOptionalChanges);
                } /* Settings */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.UI.Xaml.Settings.IXamlOptionalChangesStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Settings.XamlOptionalChanges
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Settings_IXamlOptionalChangesStatics[] = L"Microsoft.UI.Xaml.Settings.IXamlOptionalChangesStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Settings {
                    MIDL_INTERFACE("edb65323-1884-51c9-8b79-719554de4dd9")
                    IXamlOptionalChangesStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE EnableChange(
                            ABI::Microsoft::UI::Xaml::Settings::XamlChangeId changeId,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DisableChange(
                            ABI::Microsoft::UI::Xaml::Settings::XamlChangeId changeId,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsChangeEnabled(
                            ABI::Microsoft::UI::Xaml::Settings::XamlChangeId changeId,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Lock(
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsLocked(
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlOptionalChangesStatics = _uuidof(IXamlOptionalChangesStatics);
                } /* Settings */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

/*
 *
 * Class Microsoft.UI.Xaml.Settings.XamlOptionalChanges
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Settings.IXamlOptionalChangesStatics interface starting with version 11.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Settings.IXamlOptionalChanges ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Settings_XamlOptionalChanges_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Settings_XamlOptionalChanges_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Settings_XamlOptionalChanges[] = L"Microsoft.UI.Xaml.Settings.XamlOptionalChanges";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CXamlChangeId __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CXamlChangeId;

/*
 *
 * Struct Microsoft.UI.Xaml.Settings.XamlChangeId
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
enum __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CXamlChangeId
{
    XamlChangeId__Reserved = 0,
    XamlChangeId_IconNoGridOptimization = 61276805,
    XamlChangeId_OptimizeApplyStyles = 61697456,
    XamlChangeId_DefaultStyleOptimizations = 60995620,
    XamlChangeId_DeferContextFlyoutInit = 61098986,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.UI.Xaml.Settings.IXamlOptionalChanges
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Settings.XamlOptionalChanges
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Settings_IXamlOptionalChanges[] = L"Microsoft.UI.Xaml.Settings.IXamlOptionalChanges";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChanges_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.UI.Xaml.Settings.IXamlOptionalChangesStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Settings.XamlOptionalChanges
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Settings_IXamlOptionalChangesStatics[] = L"Microsoft.UI.Xaml.Settings.IXamlOptionalChangesStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* EnableChange)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CXamlChangeId changeId,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* DisableChange)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CXamlChangeId changeId,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsChangeEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CXamlChangeId changeId,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Lock)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsLocked)(__x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_EnableChange(This, changeId, result) \
    ((This)->lpVtbl->EnableChange(This, changeId, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_DisableChange(This, changeId, result) \
    ((This)->lpVtbl->DisableChange(This, changeId, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_IsChangeEnabled(This, changeId, result) \
    ((This)->lpVtbl->IsChangeEnabled(This, changeId, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_Lock(This, result) \
    ((This)->lpVtbl->Lock(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_IsLocked(This, result) \
    ((This)->lpVtbl->IsLocked(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CSettings_CIXamlOptionalChangesStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

/*
 *
 * Class Microsoft.UI.Xaml.Settings.XamlOptionalChanges
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 11.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Settings.IXamlOptionalChangesStatics interface starting with version 11.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Settings.IXamlOptionalChanges ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Settings_XamlOptionalChanges_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Settings_XamlOptionalChanges_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Settings_XamlOptionalChanges[] = L"Microsoft.UI.Xaml.Settings.XamlOptionalChanges";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xb0000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Esettings_p_h__

#endif // __microsoft2Eui2Examl2Esettings_h__
