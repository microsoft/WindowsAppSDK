
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
#ifndef __microsoft2Eui2Einput2Einterop_h__
#define __microsoft2Eui2Einput2Einterop_h__
#ifndef __microsoft2Eui2Einput2Einterop_p_h__
#define __microsoft2Eui2Einput2Einterop_p_h__


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
#if !defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)
#define MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.Foundation.h"
#include "Microsoft.UI.Input.h"
#include "Windows.Devices.Input.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace Interop {
                    interface IPenDeviceInteropStatics;
                } /* Interop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics ABI::Microsoft::UI::Input::Interop::IPenDeviceInteropStatics

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                class PointerPoint;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                interface IPointerPoint;
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint ABI::Microsoft::UI::Input::IPointerPoint

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Devices {
            namespace Input {
                class PenDevice;
            } /* Input */
        } /* Devices */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CDevices_CInput_CIPenDevice_FWD_DEFINED__
#define ____x_ABI_CWindows_CDevices_CInput_CIPenDevice_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Devices {
            namespace Input {
                interface IPenDevice;
            } /* Input */
        } /* Devices */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CDevices_CInput_CIPenDevice ABI::Windows::Devices::Input::IPenDevice

#endif // ____x_ABI_CWindows_CDevices_CInput_CIPenDevice_FWD_DEFINED__

/*
 *
 * Interface Microsoft.UI.Input.Interop.IPenDeviceInteropStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.Interop.PenDeviceInterop
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_Interop_IPenDeviceInteropStatics[] = L"Microsoft.UI.Input.Interop.IPenDeviceInteropStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Input {
                namespace Interop {
                    MIDL_INTERFACE("c2a59f2a-e077-5d30-a1bd-cf84dd09ee39")
                    IPenDeviceInteropStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE FromPointerPoint(
                            ABI::Microsoft::UI::Input::IPointerPoint* pointerPoint,
                            ABI::Windows::Devices::Input::IPenDevice** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPenDeviceInteropStatics = _uuidof(IPenDeviceInteropStatics);
                } /* Interop */
            } /* Input */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Input.Interop.PenDeviceInterop
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Input.Interop.IPenDeviceInteropStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Input_Interop_PenDeviceInterop_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_Interop_PenDeviceInterop_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_Interop_PenDeviceInterop[] = L"Microsoft.UI.Input.Interop.PenDeviceInterop";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint;

#endif // ____x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CDevices_CInput_CIPenDevice_FWD_DEFINED__
#define ____x_ABI_CWindows_CDevices_CInput_CIPenDevice_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CDevices_CInput_CIPenDevice __x_ABI_CWindows_CDevices_CInput_CIPenDevice;

#endif // ____x_ABI_CWindows_CDevices_CInput_CIPenDevice_FWD_DEFINED__

/*
 *
 * Interface Microsoft.UI.Input.Interop.IPenDeviceInteropStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Input.Interop.PenDeviceInterop
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Input_Interop_IPenDeviceInteropStatics[] = L"Microsoft.UI.Input.Interop.IPenDeviceInteropStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* FromPointerPoint)(__x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics* This,
        __x_ABI_CMicrosoft_CUI_CInput_CIPointerPoint* pointerPoint,
        __x_ABI_CWindows_CDevices_CInput_CIPenDevice** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_FromPointerPoint(This, pointerPoint, result) \
    ((This)->lpVtbl->FromPointerPoint(This, pointerPoint, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CInput_CInterop_CIPenDeviceInteropStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Input.Interop.PenDeviceInterop
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Input.Interop.IPenDeviceInteropStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Input_Interop_PenDeviceInterop_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Input_Interop_PenDeviceInterop_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Input_Interop_PenDeviceInterop[] = L"Microsoft.UI.Input.Interop.PenDeviceInterop";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Einput2Einterop_p_h__

#endif // __microsoft2Eui2Einput2Einterop_h__
