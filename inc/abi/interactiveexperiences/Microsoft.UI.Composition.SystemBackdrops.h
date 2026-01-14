// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.


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
#ifndef __microsoft2Eui2Ecomposition2Esystembackdrops_h__
#define __microsoft2Eui2Ecomposition2Esystembackdrops_h__
#ifndef __microsoft2Eui2Ecomposition2Esystembackdrops_p_h__
#define __microsoft2Eui2Ecomposition2Esystembackdrops_p_h__


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
#define MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION 0x10008
#endif // defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)
#define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
#endif // defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)
#define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
#endif // defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.Foundation.h"
#include "Microsoft.UI.h"
#include "Microsoft.UI.Composition.h"
#include "Windows.UI.h"
#include "Windows.UI.Composition.h"
#include "Windows.UI.Core.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IDesktopAcrylicController;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController ABI::Microsoft::UI::Composition::SystemBackdrops::IDesktopAcrylicController

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IDesktopAcrylicController2;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2 ABI::Microsoft::UI::Composition::SystemBackdrops::IDesktopAcrylicController2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IDesktopAcrylicController3;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3 ABI::Microsoft::UI::Composition::SystemBackdrops::IDesktopAcrylicController3

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IDesktopAcrylicControllerStatics;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics ABI::Microsoft::UI::Composition::SystemBackdrops::IDesktopAcrylicControllerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IMicaController;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController ABI::Microsoft::UI::Composition::SystemBackdrops::IMicaController

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IMicaController2;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2 ABI::Microsoft::UI::Composition::SystemBackdrops::IMicaController2

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface IMicaControllerStatics;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics ABI::Microsoft::UI::Composition::SystemBackdrops::IMicaControllerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface ISystemBackdropConfiguration;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropConfiguration

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface ISystemBackdropController;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropController

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    interface ISystemBackdropControllerWithTargets;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropControllerWithTargets

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Windows {
        namespace UI {
            typedef struct Color Color;
        } /* UI */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIReference_1_Windows__CUI__CColor_USE
#define DEF___FIReference_1_Windows__CUI__CColor_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ab8e5d11-b0c1-5a21-95ae-f16bf3a37624"))
IReference<struct ABI::Windows::UI::Color> : IReference_impl<struct ABI::Windows::UI::Color>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Windows.UI.Color>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<struct ABI::Windows::UI::Color> __FIReference_1_Windows__CUI__CColor_t;
#define __FIReference_1_Windows__CUI__CColor ABI::Windows::Foundation::__FIReference_1_Windows__CUI__CColor_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_Windows__CUI__CColor_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("4c245142-08e6-5719-bacb-a2d2f18947c6"))
ITypedEventHandler<ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropControllerWithTargets*, IInspectable*> : ITypedEventHandler_impl<ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropControllerWithTargets*, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropControllerWithTargets*, IInspectable*> __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositionSupportsSystemBackdrop;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop ABI::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IClosableNotifier;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier ABI::Microsoft::UI::IClosableNotifier

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IClosable;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIClosable ABI::Windows::Foundation::IClosable

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IPropertyValue;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIPropertyValue ABI::Windows::Foundation::IPropertyValue

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                class CompositionTarget;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                interface ICompositionTarget;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CUI_CComposition_CICompositionTarget ABI::Windows::UI::Composition::ICompositionTarget

#endif // ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Core {
                class CoreWindow;
            } /* Core */
        } /* UI */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindow_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CCore_CICoreWindow_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Core {
                interface ICoreWindow;
            } /* Core */
        } /* UI */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CUI_CCore_CICoreWindow ABI::Windows::UI::Core::ICoreWindow

#endif // ____x_ABI_CWindows_CUI_CCore_CICoreWindow_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    typedef enum DesktopAcrylicKind : int DesktopAcrylicKind;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    typedef enum MicaKind : int MicaKind;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    typedef enum SystemBackdropState : int SystemBackdropState;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    typedef enum SystemBackdropTheme : int SystemBackdropTheme;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    class SystemBackdropConfiguration;
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    enum DesktopAcrylicKind : int
                    {
                        DesktopAcrylicKind_Default = 0,
                        DesktopAcrylicKind_Base = 1,
                        DesktopAcrylicKind_Thin = 2,
                    };
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.MicaKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    enum MicaKind : int
                    {
                        MicaKind_Base = 0,
                        MicaKind_BaseAlt = 1,
                    };
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.SystemBackdropState
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    enum SystemBackdropState : int
                    {
                        SystemBackdropState_Active = 0,
                        SystemBackdropState_Fallback = 1,
                        SystemBackdropState_HighContrast = 2,
                    };
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.SystemBackdropTheme
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    enum SystemBackdropTheme : int
                    {
                        SystemBackdropTheme_Default = 0,
                        SystemBackdropTheme_Light = 1,
                        SystemBackdropTheme_Dark = 2,
                    };
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicController[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("7c20a6af-8eb3-5f08-bdfc-6d35e35dfe45")
                    IDesktopAcrylicController : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_FallbackColor(
                            ABI::Windows::UI::Color* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FallbackColor(
                            ABI::Windows::UI::Color value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LuminosityOpacity(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LuminosityOpacity(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TintColor(
                            ABI::Windows::UI::Color* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TintColor(
                            ABI::Windows::UI::Color value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TintOpacity(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TintOpacity(
                            FLOAT value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopAcrylicController = _uuidof(IDesktopAcrylicController);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicController2[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("88e0a368-dfc7-5971-a50b-40df5aa5f5c2")
                    IDesktopAcrylicController2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE ResetProperties(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopAcrylicController2 = _uuidof(IDesktopAcrylicController2);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicController3[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("30d917e6-02d3-59ca-b440-bf9d2e7cc140")
                    IDesktopAcrylicController3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Kind(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Kind(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopAcrylicController3 = _uuidof(IDesktopAcrylicController3);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicControllerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicControllerStatics[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicControllerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("a9e8f790-79ef-5416-9b67-6bcfe867c8b7")
                    IDesktopAcrylicControllerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsSupported(
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopAcrylicControllerStatics = _uuidof(IDesktopAcrylicControllerStatics);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IMicaController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IMicaController[] = L"Microsoft.UI.Composition.SystemBackdrops.IMicaController";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("2de996a9-0a2a-5889-a89c-1f84060a8cab")
                    IMicaController : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_FallbackColor(
                            ABI::Windows::UI::Color* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FallbackColor(
                            ABI::Windows::UI::Color value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LuminosityOpacity(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LuminosityOpacity(
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TintColor(
                            ABI::Windows::UI::Color* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TintColor(
                            ABI::Windows::UI::Color value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TintOpacity(
                            FLOAT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TintOpacity(
                            FLOAT value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IMicaController = _uuidof(IMicaController);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IMicaController2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IMicaController2[] = L"Microsoft.UI.Composition.SystemBackdrops.IMicaController2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("f1ed4a52-d9ca-506e-9586-caaefd3aa971")
                    IMicaController2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Kind(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::MicaKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Kind(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::MicaKind value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ResetProperties(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IMicaController2 = _uuidof(IMicaController2);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IMicaControllerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IMicaControllerStatics[] = L"Microsoft.UI.Composition.SystemBackdrops.IMicaControllerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("7d85d834-d514-5250-b7c4-0b7850d1efdc")
                    IMicaControllerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsSupported(
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IMicaControllerStatics = _uuidof(IMicaControllerStatics);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_ISystemBackdropConfiguration[] = L"Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropConfiguration";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("ebcce1b9-0e0c-5431-ab0e-00f3f0669962")
                    ISystemBackdropConfiguration : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_HighContrastBackgroundColor(
                            __FIReference_1_Windows__CUI__CColor** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_HighContrastBackgroundColor(
                            __FIReference_1_Windows__CUI__CColor* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsHighContrast(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsHighContrast(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsInputActive(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsInputActive(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Theme(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Theme(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ISystemBackdropConfiguration = _uuidof(ISystemBackdropConfiguration);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Windows.Foundation.IClosable
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_ISystemBackdropController[] = L"Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("5632d76c-0b74-5b52-aa33-80262068aeb2")
                    ISystemBackdropController : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SetTargetWithWindowId(
                            ABI::Microsoft::UI::WindowId windowId,
                            ABI::Windows::UI::Composition::ICompositionTarget* desktopWindowTarget,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetTargetWithCoreWindow(
                            ABI::Windows::UI::Core::ICoreWindow* coreWindow,
                            ABI::Windows::UI::Composition::ICompositionTarget* compositionTarget,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ISystemBackdropController = _uuidof(ISystemBackdropController);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *     Windows.Foundation.IClosable
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_ISystemBackdropControllerWithTargets[] = L"Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace SystemBackdrops {
                    MIDL_INTERFACE("9c56fe7c-98eb-5f89-ad97-dad57fc30c8c")
                    ISystemBackdropControllerWithTargets : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_State(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropState* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddSystemBackdropTarget(
                            ABI::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop* systemBackdropTarget,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveAllSystemBackdropTargets(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveSystemBackdropTarget(
                            ABI::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop* systemBackdropTarget,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetSystemBackdropConfiguration(
                            ABI::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropConfiguration* configuration
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_StateChanged(
                            __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_StateChanged(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ISystemBackdropControllerWithTargets = _uuidof(ISystemBackdropControllerWithTargets);
                } /* SystemBackdrops */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Class Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicControllerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController ** Default Interface **
 *    Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController2
 *    Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController3
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets
 *    Microsoft.UI.IClosableNotifier
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_DesktopAcrylicController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_DesktopAcrylicController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_SystemBackdrops_DesktopAcrylicController[] = L"Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.SystemBackdrops.IMicaControllerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.SystemBackdrops.IMicaController ** Default Interface **
 *    Microsoft.UI.Composition.SystemBackdrops.IMicaController2
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets
 *    Microsoft.UI.IClosableNotifier
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_MicaController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_MicaController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_SystemBackdrops_MicaController[] = L"Microsoft.UI.Composition.SystemBackdrops.MicaController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.1 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropConfiguration ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_SystemBackdropConfiguration_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_SystemBackdropConfiguration_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_SystemBackdrops_SystemBackdropConfiguration[] = L"Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2 __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3 __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2 __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CWindows_CUI_CColor __x_ABI_CWindows_CUI_CColor;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__)
#define ____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__

typedef interface __FIReference_1_Windows__CUI__CColor __FIReference_1_Windows__CUI__CColor;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_Windows__CUI__CColor;

typedef struct __FIReference_1_Windows__CUI__CColorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_Windows__CUI__CColor* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_Windows__CUI__CColor* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_Windows__CUI__CColor* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_Windows__CUI__CColor* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_Windows__CUI__CColor* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_Windows__CUI__CColor* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_Windows__CUI__CColor* This,
        struct __x_ABI_CWindows_CUI_CColor* result);

    END_INTERFACE
} __FIReference_1_Windows__CUI__CColorVtbl;

interface __FIReference_1_Windows__CUI__CColor
{
    CONST_VTBL struct __FIReference_1_Windows__CUI__CColorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_Windows__CUI__CColor_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_Windows__CUI__CColor_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_Windows__CUI__CColor_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_Windows__CUI__CColor_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_Windows__CUI__CColor_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_Windows__CUI__CColor_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_Windows__CUI__CColor_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIClosableNotifier __x_ABI_CMicrosoft_CUI_CIClosableNotifier;

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIPropertyValue __x_ABI_CWindows_CFoundation_CIPropertyValue;

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CUI_CComposition_CICompositionTarget __x_ABI_CWindows_CUI_CComposition_CICompositionTarget;

#endif // ____x_ABI_CWindows_CUI_CComposition_CICompositionTarget_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindow_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CCore_CICoreWindow_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CUI_CCore_CICoreWindow __x_ABI_CWindows_CUI_CCore_CICoreWindow;

#endif // ____x_ABI_CWindows_CUI_CCore_CICoreWindow_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CDesktopAcrylicKind __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CDesktopAcrylicKind;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CMicaKind __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CMicaKind;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropState __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropState;

typedef enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropTheme __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropTheme;

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CDesktopAcrylicKind
{
    DesktopAcrylicKind_Default = 0,
    DesktopAcrylicKind_Base = 1,
    DesktopAcrylicKind_Thin = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.MicaKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CMicaKind
{
    MicaKind_Base = 0,
    MicaKind_BaseAlt = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.SystemBackdropState
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropState
{
    SystemBackdropState_Active = 0,
    SystemBackdropState_Fallback = 1,
    SystemBackdropState_HighContrast = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Struct Microsoft.UI.Composition.SystemBackdrops.SystemBackdropTheme
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropTheme
{
    SystemBackdropTheme_Default = 0,
    SystemBackdropTheme_Light = 1,
    SystemBackdropTheme_Dark = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicController[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FallbackColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* put_FallbackColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        struct __x_ABI_CWindows_CUI_CColor value);
    HRESULT (STDMETHODCALLTYPE* get_LuminosityOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_LuminosityOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_TintColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* put_TintColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        struct __x_ABI_CWindows_CUI_CColor value);
    HRESULT (STDMETHODCALLTYPE* get_TintOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_TintOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController* This,
        FLOAT value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_get_FallbackColor(This, value) \
    ((This)->lpVtbl->get_FallbackColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_put_FallbackColor(This, value) \
    ((This)->lpVtbl->put_FallbackColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_get_LuminosityOpacity(This, value) \
    ((This)->lpVtbl->get_LuminosityOpacity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_put_LuminosityOpacity(This, value) \
    ((This)->lpVtbl->put_LuminosityOpacity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_get_TintColor(This, value) \
    ((This)->lpVtbl->get_TintColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_put_TintColor(This, value) \
    ((This)->lpVtbl->put_TintColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_get_TintOpacity(This, value) \
    ((This)->lpVtbl->get_TintOpacity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_put_TintOpacity(This, value) \
    ((This)->lpVtbl->put_TintOpacity(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicController2[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ResetProperties)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_ResetProperties(This) \
    ((This)->lpVtbl->ResetProperties(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicController3[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController3";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CDesktopAcrylicKind* value);
    HRESULT (STDMETHODCALLTYPE* put_Kind)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CDesktopAcrylicKind value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_put_Kind(This, value) \
    ((This)->lpVtbl->put_Kind(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicController3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicControllerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IDesktopAcrylicControllerStatics[] = L"Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicControllerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsSupported)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_IsSupported(This, result) \
    ((This)->lpVtbl->IsSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIDesktopAcrylicControllerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IMicaController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IMicaController[] = L"Microsoft.UI.Composition.SystemBackdrops.IMicaController";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FallbackColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* put_FallbackColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        struct __x_ABI_CWindows_CUI_CColor value);
    HRESULT (STDMETHODCALLTYPE* get_LuminosityOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_LuminosityOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_TintColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* put_TintColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        struct __x_ABI_CWindows_CUI_CColor value);
    HRESULT (STDMETHODCALLTYPE* get_TintOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_TintOpacity)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController* This,
        FLOAT value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_get_FallbackColor(This, value) \
    ((This)->lpVtbl->get_FallbackColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_put_FallbackColor(This, value) \
    ((This)->lpVtbl->put_FallbackColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_get_LuminosityOpacity(This, value) \
    ((This)->lpVtbl->get_LuminosityOpacity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_put_LuminosityOpacity(This, value) \
    ((This)->lpVtbl->put_LuminosityOpacity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_get_TintColor(This, value) \
    ((This)->lpVtbl->get_TintColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_put_TintColor(This, value) \
    ((This)->lpVtbl->put_TintColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_get_TintOpacity(This, value) \
    ((This)->lpVtbl->get_TintOpacity(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_put_TintOpacity(This, value) \
    ((This)->lpVtbl->put_TintOpacity(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IMicaController2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IMicaController2[] = L"Microsoft.UI.Composition.SystemBackdrops.IMicaController2";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CMicaKind* value);
    HRESULT (STDMETHODCALLTYPE* put_Kind)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CMicaKind value);
    HRESULT (STDMETHODCALLTYPE* ResetProperties)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_put_Kind(This, value) \
    ((This)->lpVtbl->put_Kind(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_ResetProperties(This) \
    ((This)->lpVtbl->ResetProperties(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaController2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.IMicaControllerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_IMicaControllerStatics[] = L"Microsoft.UI.Composition.SystemBackdrops.IMicaControllerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsSupported)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_IsSupported(This, result) \
    ((This)->lpVtbl->IsSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CIMicaControllerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_ISystemBackdropConfiguration[] = L"Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropConfiguration";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfigurationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_HighContrastBackgroundColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_HighContrastBackgroundColor)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_IsHighContrast)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsHighContrast)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsInputActive)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsInputActive)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_Theme)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropTheme* value);
    HRESULT (STDMETHODCALLTYPE* put_Theme)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropTheme value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfigurationVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfigurationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_get_HighContrastBackgroundColor(This, value) \
    ((This)->lpVtbl->get_HighContrastBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_put_HighContrastBackgroundColor(This, value) \
    ((This)->lpVtbl->put_HighContrastBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_get_IsHighContrast(This, value) \
    ((This)->lpVtbl->get_IsHighContrast(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_put_IsHighContrast(This, value) \
    ((This)->lpVtbl->put_IsHighContrast(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_get_IsInputActive(This, value) \
    ((This)->lpVtbl->get_IsInputActive(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_put_IsInputActive(This, value) \
    ((This)->lpVtbl->put_IsInputActive(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_get_Theme(This, value) \
    ((This)->lpVtbl->get_Theme(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_put_Theme(This, value) \
    ((This)->lpVtbl->put_Theme(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Windows.Foundation.IClosable
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_ISystemBackdropController[] = L"Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SetTargetWithWindowId)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CWindows_CUI_CComposition_CICompositionTarget* desktopWindowTarget,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetTargetWithCoreWindow)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController* This,
        __x_ABI_CWindows_CUI_CCore_CICoreWindow* coreWindow,
        __x_ABI_CWindows_CUI_CComposition_CICompositionTarget* compositionTarget,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_SetTargetWithWindowId(This, windowId, desktopWindowTarget, result) \
    ((This)->lpVtbl->SetTargetWithWindowId(This, windowId, desktopWindowTarget, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_SetTargetWithCoreWindow(This, coreWindow, compositionTarget, result) \
    ((This)->lpVtbl->SetTargetWithCoreWindow(This, coreWindow, compositionTarget, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *     Windows.Foundation.IClosable
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_SystemBackdrops_ISystemBackdropControllerWithTargets[] = L"Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargetsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_State)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        enum __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CSystemBackdropState* value);
    HRESULT (STDMETHODCALLTYPE* AddSystemBackdropTarget)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop* systemBackdropTarget,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* RemoveAllSystemBackdropTargets)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This);
    HRESULT (STDMETHODCALLTYPE* RemoveSystemBackdropTarget)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop* systemBackdropTarget,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetSystemBackdropConfiguration)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropConfiguration* configuration);
    HRESULT (STDMETHODCALLTYPE* add_StateChanged)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        __FITypedEventHandler_2_Microsoft__CUI__CComposition__CSystemBackdrops__CISystemBackdropControllerWithTargets_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_StateChanged)(__x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargetsVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargetsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_get_State(This, value) \
    ((This)->lpVtbl->get_State(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_AddSystemBackdropTarget(This, systemBackdropTarget, result) \
    ((This)->lpVtbl->AddSystemBackdropTarget(This, systemBackdropTarget, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_RemoveAllSystemBackdropTargets(This) \
    ((This)->lpVtbl->RemoveAllSystemBackdropTargets(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_RemoveSystemBackdropTarget(This, systemBackdropTarget, result) \
    ((This)->lpVtbl->RemoveSystemBackdropTarget(This, systemBackdropTarget, result))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_SetSystemBackdropConfiguration(This, configuration) \
    ((This)->lpVtbl->SetSystemBackdropConfiguration(This, configuration))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_add_StateChanged(This, handler, token) \
    ((This)->lpVtbl->add_StateChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_remove_StateChanged(This, token) \
    ((This)->lpVtbl->remove_StateChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CSystemBackdrops_CISystemBackdropControllerWithTargets_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Class Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicControllerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController ** Default Interface **
 *    Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController2
 *    Microsoft.UI.Composition.SystemBackdrops.IDesktopAcrylicController3
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets
 *    Microsoft.UI.IClosableNotifier
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_DesktopAcrylicController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_DesktopAcrylicController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_SystemBackdrops_DesktopAcrylicController[] = L"Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.SystemBackdrops.MicaController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Composition.SystemBackdrops.IMicaControllerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.SystemBackdrops.IMicaController ** Default Interface **
 *    Microsoft.UI.Composition.SystemBackdrops.IMicaController2
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropController
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropControllerWithTargets
 *    Microsoft.UI.IClosableNotifier
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_MicaController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_MicaController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_SystemBackdrops_MicaController[] = L"Microsoft.UI.Composition.SystemBackdrops.MicaController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.1 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.SystemBackdrops.ISystemBackdropConfiguration ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_SystemBackdropConfiguration_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_SystemBackdrops_SystemBackdropConfiguration_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_SystemBackdrops_SystemBackdropConfiguration[] = L"Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Ecomposition2Esystembackdrops_p_h__

#endif // __microsoft2Eui2Ecomposition2Esystembackdrops_h__
