
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
#ifndef __microsoft2Eui_h__
#define __microsoft2Eui_h__
#ifndef __microsoft2Eui_p_h__
#define __microsoft2Eui_p_h__


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

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Microsoft.Foundation.h"
#include "Windows.UI.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IClosableNotifierHandler;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler ABI::Microsoft::UI::IClosableNotifierHandler

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_FWD_DEFINED__

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

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorHelper_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IColorHelper;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIColorHelper ABI::Microsoft::UI::IColorHelper

#endif // ____x_ABI_CMicrosoft_CUI_CIColorHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IColorHelperStatics;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics ABI::Microsoft::UI::IColorHelperStatics

#endif // ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IColorHelperStatics2;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2 ABI::Microsoft::UI::IColorHelperStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColors_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColors_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IColors;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIColors ABI::Microsoft::UI::IColors

#endif // ____x_ABI_CMicrosoft_CUI_CIColors_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IColorsStatics;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIColorsStatics ABI::Microsoft::UI::IColorsStatics

#endif // ____x_ABI_CMicrosoft_CUI_CIColorsStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Windows {
        namespace UI {
            typedef struct Color Color;
        } /* UI */
    } /* Windows */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.DisplayId
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            struct DisplayId
            {
                UINT64 Value;
            };
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.IconId
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            struct IconId
            {
                UINT64 Value;
            };
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.WindowId
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            struct WindowId
            {
                UINT64 Value;
            };
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.ClosableNotifierHandler
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("478cec68-ea8e-52fc-87e2-c819de000f92")
            IClosableNotifierHandler : public IUnknown
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE Invoke(void) = 0;
            };

            MIDL_CONST_ID IID& IID_IClosableNotifierHandler = _uuidof(IClosableNotifierHandler);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.IClosableNotifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifier_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IClosableNotifier[] = L"Microsoft.UI.IClosableNotifier";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("2989e93b-ed0f-5e79-90f2-eac592fc6e6a")
            IClosableNotifier : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE get_IsClosed(
                    boolean* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE add_Closed(
                    ABI::Microsoft::UI::IClosableNotifierHandler* handler,
                    EventRegistrationToken* token
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE remove_Closed(
                    EventRegistrationToken token
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE add_FrameworkClosed(
                    ABI::Microsoft::UI::IClosableNotifierHandler* handler,
                    EventRegistrationToken* token
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE remove_FrameworkClosed(
                    EventRegistrationToken token
                    ) = 0;
            };

            MIDL_CONST_ID IID& IID_IClosableNotifier = _uuidof(IClosableNotifier);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIClosableNotifier;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifier_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.IColorHelper
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.ColorHelper
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorHelper[] = L"Microsoft.UI.IColorHelper";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("3adddccd-3949-585b-a566-ccb8350dd221")
            IColorHelper : public IInspectable
            {
            public:
            };

            MIDL_CONST_ID IID& IID_IColorHelper = _uuidof(IColorHelper);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.IColorHelperStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.ColorHelper
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorHelperStatics[] = L"Microsoft.UI.IColorHelperStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("1d1d85a1-eb63-538a-84f0-019210bc406b")
            IColorHelperStatics : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE FromArgb(
                    BYTE a,
                    BYTE r,
                    BYTE g,
                    BYTE b,
                    ABI::Windows::UI::Color* result
                    ) = 0;
            };

            MIDL_CONST_ID IID& IID_IColorHelperStatics = _uuidof(IColorHelperStatics);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.IColorHelperStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.6
 *
 * Interface is a part of the implementation of type Microsoft.UI.ColorHelper
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10006
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorHelperStatics2[] = L"Microsoft.UI.IColorHelperStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("982a2d93-0ec4-56b7-9c20-0b5c77949066")
            IColorHelperStatics2 : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE ToDisplayName(
                    ABI::Windows::UI::Color color,
                    HSTRING* result
                    ) = 0;
            };

            MIDL_CONST_ID IID& IID_IColorHelperStatics2 = _uuidof(IColorHelperStatics2);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorHelperStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10006

/*
 *
 * Interface Microsoft.UI.IColors
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Colors
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColors_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColors_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColors[] = L"Microsoft.UI.IColors";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("8cf15863-8411-5afd-946c-328e04da2f2f")
            IColors : public IInspectable
            {
            public:
            };

            MIDL_CONST_ID IID& IID_IColors = _uuidof(IColors);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColors;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColors_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.IColorsStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Colors
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorsStatics[] = L"Microsoft.UI.IColorsStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            MIDL_INTERFACE("8620a5b0-015a-57ac-a3f3-895d0b1269ae")
            IColorsStatics : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE get_AliceBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_AntiqueWhite(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Aqua(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Aquamarine(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Azure(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Beige(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Bisque(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Black(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_BlanchedAlmond(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Blue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_BlueViolet(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Brown(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_BurlyWood(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_CadetBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Chartreuse(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Chocolate(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Coral(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_CornflowerBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Cornsilk(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Crimson(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Cyan(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkCyan(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkGoldenrod(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkGray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkKhaki(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkMagenta(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkOliveGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkOrange(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkOrchid(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkRed(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkSalmon(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkSeaGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkSlateBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkSlateGray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkTurquoise(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DarkViolet(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DeepPink(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DeepSkyBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DimGray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_DodgerBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Firebrick(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_FloralWhite(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_ForestGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Fuchsia(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Gainsboro(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_GhostWhite(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Gold(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Goldenrod(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Gray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Green(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_GreenYellow(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Honeydew(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_HotPink(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_IndianRed(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Indigo(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Ivory(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Khaki(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Lavender(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LavenderBlush(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LawnGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LemonChiffon(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightCoral(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightCyan(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightGoldenrodYellow(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightGray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightPink(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightSalmon(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightSeaGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightSkyBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightSlateGray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightSteelBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LightYellow(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Lime(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_LimeGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Linen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Magenta(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Maroon(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumAquamarine(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumOrchid(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumPurple(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumSeaGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumSlateBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumSpringGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumTurquoise(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MediumVioletRed(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MidnightBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MintCream(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_MistyRose(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Moccasin(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_NavajoWhite(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Navy(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_OldLace(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Olive(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_OliveDrab(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Orange(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_OrangeRed(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Orchid(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PaleGoldenrod(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PaleGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PaleTurquoise(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PaleVioletRed(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PapayaWhip(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PeachPuff(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Peru(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Pink(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Plum(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_PowderBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Purple(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Red(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_RosyBrown(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_RoyalBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SaddleBrown(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Salmon(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SandyBrown(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SeaGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SeaShell(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Sienna(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Silver(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SkyBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SlateBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SlateGray(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Snow(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SpringGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_SteelBlue(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Tan(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Teal(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Thistle(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Tomato(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Transparent(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Turquoise(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Violet(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Wheat(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_White(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_WhiteSmoke(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_Yellow(
                    ABI::Windows::UI::Color* value
                    ) = 0;
                virtual HRESULT STDMETHODCALLTYPE get_YellowGreen(
                    ABI::Windows::UI::Color* value
                    ) = 0;
            };

            MIDL_CONST_ID IID& IID_IColorsStatics = _uuidof(IColorsStatics);
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.ColorHelper
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.IColorHelperStatics2 interface starting with version 1.6 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.IColorHelperStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.IColorHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_ColorHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_ColorHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_ColorHelper[] = L"Microsoft.UI.ColorHelper";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Colors
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.IColorsStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.IColors ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Colors_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Colors_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Colors[] = L"Microsoft.UI.Colors";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIClosableNotifier __x_ABI_CMicrosoft_CUI_CIClosableNotifier;

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorHelper_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIColorHelper __x_ABI_CMicrosoft_CUI_CIColorHelper;

#endif // ____x_ABI_CMicrosoft_CUI_CIColorHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIColorHelperStatics __x_ABI_CMicrosoft_CUI_CIColorHelperStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2 __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColors_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColors_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIColors __x_ABI_CMicrosoft_CUI_CIColors;

#endif // ____x_ABI_CMicrosoft_CUI_CIColors_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CIColorsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIColorsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIColorsStatics __x_ABI_CMicrosoft_CUI_CIColorsStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CIColorsStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CWindows_CUI_CColor __x_ABI_CWindows_CUI_CColor;

/*
 *
 * Struct Microsoft.UI.DisplayId
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CDisplayId
{
    UINT64 Value;
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.IconId
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CIconId
{
    UINT64 Value;
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.WindowId
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CWindowId
{
    UINT64 Value;
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Delegate Microsoft.UI.ClosableNotifierHandler
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_Invoke(This) \
    ((This)->lpVtbl->Invoke(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.IClosableNotifier
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifier_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IClosableNotifier[] = L"Microsoft.UI.IClosableNotifier";
typedef struct __x_ABI_CMicrosoft_CUI_CIClosableNotifierVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsClosed)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* add_Closed)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Closed)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_FrameworkClosed)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        __x_ABI_CMicrosoft_CUI_CIClosableNotifierHandler* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_FrameworkClosed)(__x_ABI_CMicrosoft_CUI_CIClosableNotifier* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIClosableNotifierVtbl;

interface __x_ABI_CMicrosoft_CUI_CIClosableNotifier
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIClosableNotifierVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_get_IsClosed(This, value) \
    ((This)->lpVtbl->get_IsClosed(This, value))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_add_Closed(This, handler, token) \
    ((This)->lpVtbl->add_Closed(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_remove_Closed(This, token) \
    ((This)->lpVtbl->remove_Closed(This, token))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_add_FrameworkClosed(This, handler, token) \
    ((This)->lpVtbl->add_FrameworkClosed(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier_remove_FrameworkClosed(This, token) \
    ((This)->lpVtbl->remove_FrameworkClosed(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIClosableNotifier;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIClosableNotifier_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.IColorHelper
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.ColorHelper
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorHelper[] = L"Microsoft.UI.IColorHelper";
typedef struct __x_ABI_CMicrosoft_CUI_CIColorHelperVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIColorHelper* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIColorHelper* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIColorHelper* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CIColorHelper* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CIColorHelper* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CIColorHelper* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIColorHelperVtbl;

interface __x_ABI_CMicrosoft_CUI_CIColorHelper
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIColorHelperVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIColorHelper_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIColorHelper_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIColorHelper_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIColorHelper_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CIColorHelper_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CIColorHelper_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.IColorHelperStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.ColorHelper
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorHelperStatics[] = L"Microsoft.UI.IColorHelperStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CIColorHelperStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* FromArgb)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics* This,
        BYTE a,
        BYTE r,
        BYTE g,
        BYTE b,
        struct __x_ABI_CWindows_CUI_CColor* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIColorHelperStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CIColorHelperStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIColorHelperStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics_FromArgb(This, a, r, g, b, result) \
    ((This)->lpVtbl->FromArgb(This, a, r, g, b, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.IColorHelperStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.6
 *
 * Interface is a part of the implementation of type Microsoft.UI.ColorHelper
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10006
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorHelperStatics2[] = L"Microsoft.UI.IColorHelperStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ToDisplayName)(__x_ABI_CMicrosoft_CUI_CIColorHelperStatics2* This,
        struct __x_ABI_CWindows_CUI_CColor color,
        HSTRING* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_ToDisplayName(This, color, result) \
    ((This)->lpVtbl->ToDisplayName(This, color, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorHelperStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorHelperStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10006

/*
 *
 * Interface Microsoft.UI.IColors
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Colors
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColors_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColors_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColors[] = L"Microsoft.UI.IColors";
typedef struct __x_ABI_CMicrosoft_CUI_CIColorsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIColors* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIColors* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIColors* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CIColors* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CIColors* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CIColors* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIColorsVtbl;

interface __x_ABI_CMicrosoft_CUI_CIColors
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIColorsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIColors_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIColors_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIColors_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIColors_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CIColors_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CIColors_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColors;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColors_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.IColorsStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Colors
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CIColorsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CIColorsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_IColorsStatics[] = L"Microsoft.UI.IColorsStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CIColorsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AliceBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_AntiqueWhite)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Aqua)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Aquamarine)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Azure)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Beige)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Bisque)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Black)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_BlanchedAlmond)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Blue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_BlueViolet)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Brown)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_BurlyWood)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_CadetBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Chartreuse)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Chocolate)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Coral)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_CornflowerBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Cornsilk)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Crimson)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Cyan)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkCyan)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkGoldenrod)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkGray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkKhaki)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkMagenta)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkOliveGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkOrange)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkOrchid)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkRed)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkSalmon)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkSeaGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkSlateBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkSlateGray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkTurquoise)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkViolet)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DeepPink)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DeepSkyBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DimGray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_DodgerBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Firebrick)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_FloralWhite)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ForestGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Fuchsia)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Gainsboro)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_GhostWhite)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Gold)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Goldenrod)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Gray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Green)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_GreenYellow)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Honeydew)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_HotPink)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_IndianRed)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Indigo)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Ivory)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Khaki)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Lavender)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LavenderBlush)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LawnGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LemonChiffon)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightCoral)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightCyan)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightGoldenrodYellow)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightGray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightPink)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightSalmon)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightSeaGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightSkyBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightSlateGray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightSteelBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LightYellow)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Lime)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LimeGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Linen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Magenta)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Maroon)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumAquamarine)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumOrchid)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumPurple)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumSeaGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumSlateBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumSpringGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumTurquoise)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MediumVioletRed)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MidnightBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MintCream)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_MistyRose)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Moccasin)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_NavajoWhite)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Navy)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_OldLace)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Olive)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_OliveDrab)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Orange)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_OrangeRed)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Orchid)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PaleGoldenrod)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PaleGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PaleTurquoise)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PaleVioletRed)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PapayaWhip)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PeachPuff)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Peru)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Pink)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Plum)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_PowderBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Purple)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Red)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_RosyBrown)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_RoyalBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SaddleBrown)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Salmon)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SandyBrown)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SeaGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SeaShell)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Sienna)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Silver)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SkyBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SlateBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SlateGray)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Snow)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SpringGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_SteelBlue)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Tan)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Teal)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Thistle)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Tomato)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Transparent)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Turquoise)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Violet)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Wheat)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_White)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_WhiteSmoke)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Yellow)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_YellowGreen)(__x_ABI_CMicrosoft_CUI_CIColorsStatics* This,
        struct __x_ABI_CWindows_CUI_CColor* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CIColorsStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CIColorsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CIColorsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_AliceBlue(This, value) \
    ((This)->lpVtbl->get_AliceBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_AntiqueWhite(This, value) \
    ((This)->lpVtbl->get_AntiqueWhite(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Aqua(This, value) \
    ((This)->lpVtbl->get_Aqua(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Aquamarine(This, value) \
    ((This)->lpVtbl->get_Aquamarine(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Azure(This, value) \
    ((This)->lpVtbl->get_Azure(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Beige(This, value) \
    ((This)->lpVtbl->get_Beige(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Bisque(This, value) \
    ((This)->lpVtbl->get_Bisque(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Black(This, value) \
    ((This)->lpVtbl->get_Black(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_BlanchedAlmond(This, value) \
    ((This)->lpVtbl->get_BlanchedAlmond(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Blue(This, value) \
    ((This)->lpVtbl->get_Blue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_BlueViolet(This, value) \
    ((This)->lpVtbl->get_BlueViolet(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Brown(This, value) \
    ((This)->lpVtbl->get_Brown(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_BurlyWood(This, value) \
    ((This)->lpVtbl->get_BurlyWood(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_CadetBlue(This, value) \
    ((This)->lpVtbl->get_CadetBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Chartreuse(This, value) \
    ((This)->lpVtbl->get_Chartreuse(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Chocolate(This, value) \
    ((This)->lpVtbl->get_Chocolate(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Coral(This, value) \
    ((This)->lpVtbl->get_Coral(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_CornflowerBlue(This, value) \
    ((This)->lpVtbl->get_CornflowerBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Cornsilk(This, value) \
    ((This)->lpVtbl->get_Cornsilk(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Crimson(This, value) \
    ((This)->lpVtbl->get_Crimson(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Cyan(This, value) \
    ((This)->lpVtbl->get_Cyan(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkBlue(This, value) \
    ((This)->lpVtbl->get_DarkBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkCyan(This, value) \
    ((This)->lpVtbl->get_DarkCyan(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkGoldenrod(This, value) \
    ((This)->lpVtbl->get_DarkGoldenrod(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkGray(This, value) \
    ((This)->lpVtbl->get_DarkGray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkGreen(This, value) \
    ((This)->lpVtbl->get_DarkGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkKhaki(This, value) \
    ((This)->lpVtbl->get_DarkKhaki(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkMagenta(This, value) \
    ((This)->lpVtbl->get_DarkMagenta(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkOliveGreen(This, value) \
    ((This)->lpVtbl->get_DarkOliveGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkOrange(This, value) \
    ((This)->lpVtbl->get_DarkOrange(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkOrchid(This, value) \
    ((This)->lpVtbl->get_DarkOrchid(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkRed(This, value) \
    ((This)->lpVtbl->get_DarkRed(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkSalmon(This, value) \
    ((This)->lpVtbl->get_DarkSalmon(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkSeaGreen(This, value) \
    ((This)->lpVtbl->get_DarkSeaGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkSlateBlue(This, value) \
    ((This)->lpVtbl->get_DarkSlateBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkSlateGray(This, value) \
    ((This)->lpVtbl->get_DarkSlateGray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkTurquoise(This, value) \
    ((This)->lpVtbl->get_DarkTurquoise(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DarkViolet(This, value) \
    ((This)->lpVtbl->get_DarkViolet(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DeepPink(This, value) \
    ((This)->lpVtbl->get_DeepPink(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DeepSkyBlue(This, value) \
    ((This)->lpVtbl->get_DeepSkyBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DimGray(This, value) \
    ((This)->lpVtbl->get_DimGray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_DodgerBlue(This, value) \
    ((This)->lpVtbl->get_DodgerBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Firebrick(This, value) \
    ((This)->lpVtbl->get_Firebrick(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_FloralWhite(This, value) \
    ((This)->lpVtbl->get_FloralWhite(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_ForestGreen(This, value) \
    ((This)->lpVtbl->get_ForestGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Fuchsia(This, value) \
    ((This)->lpVtbl->get_Fuchsia(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Gainsboro(This, value) \
    ((This)->lpVtbl->get_Gainsboro(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_GhostWhite(This, value) \
    ((This)->lpVtbl->get_GhostWhite(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Gold(This, value) \
    ((This)->lpVtbl->get_Gold(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Goldenrod(This, value) \
    ((This)->lpVtbl->get_Goldenrod(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Gray(This, value) \
    ((This)->lpVtbl->get_Gray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Green(This, value) \
    ((This)->lpVtbl->get_Green(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_GreenYellow(This, value) \
    ((This)->lpVtbl->get_GreenYellow(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Honeydew(This, value) \
    ((This)->lpVtbl->get_Honeydew(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_HotPink(This, value) \
    ((This)->lpVtbl->get_HotPink(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_IndianRed(This, value) \
    ((This)->lpVtbl->get_IndianRed(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Indigo(This, value) \
    ((This)->lpVtbl->get_Indigo(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Ivory(This, value) \
    ((This)->lpVtbl->get_Ivory(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Khaki(This, value) \
    ((This)->lpVtbl->get_Khaki(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Lavender(This, value) \
    ((This)->lpVtbl->get_Lavender(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LavenderBlush(This, value) \
    ((This)->lpVtbl->get_LavenderBlush(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LawnGreen(This, value) \
    ((This)->lpVtbl->get_LawnGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LemonChiffon(This, value) \
    ((This)->lpVtbl->get_LemonChiffon(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightBlue(This, value) \
    ((This)->lpVtbl->get_LightBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightCoral(This, value) \
    ((This)->lpVtbl->get_LightCoral(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightCyan(This, value) \
    ((This)->lpVtbl->get_LightCyan(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightGoldenrodYellow(This, value) \
    ((This)->lpVtbl->get_LightGoldenrodYellow(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightGreen(This, value) \
    ((This)->lpVtbl->get_LightGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightGray(This, value) \
    ((This)->lpVtbl->get_LightGray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightPink(This, value) \
    ((This)->lpVtbl->get_LightPink(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightSalmon(This, value) \
    ((This)->lpVtbl->get_LightSalmon(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightSeaGreen(This, value) \
    ((This)->lpVtbl->get_LightSeaGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightSkyBlue(This, value) \
    ((This)->lpVtbl->get_LightSkyBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightSlateGray(This, value) \
    ((This)->lpVtbl->get_LightSlateGray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightSteelBlue(This, value) \
    ((This)->lpVtbl->get_LightSteelBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LightYellow(This, value) \
    ((This)->lpVtbl->get_LightYellow(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Lime(This, value) \
    ((This)->lpVtbl->get_Lime(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_LimeGreen(This, value) \
    ((This)->lpVtbl->get_LimeGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Linen(This, value) \
    ((This)->lpVtbl->get_Linen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Magenta(This, value) \
    ((This)->lpVtbl->get_Magenta(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Maroon(This, value) \
    ((This)->lpVtbl->get_Maroon(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumAquamarine(This, value) \
    ((This)->lpVtbl->get_MediumAquamarine(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumBlue(This, value) \
    ((This)->lpVtbl->get_MediumBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumOrchid(This, value) \
    ((This)->lpVtbl->get_MediumOrchid(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumPurple(This, value) \
    ((This)->lpVtbl->get_MediumPurple(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumSeaGreen(This, value) \
    ((This)->lpVtbl->get_MediumSeaGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumSlateBlue(This, value) \
    ((This)->lpVtbl->get_MediumSlateBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumSpringGreen(This, value) \
    ((This)->lpVtbl->get_MediumSpringGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumTurquoise(This, value) \
    ((This)->lpVtbl->get_MediumTurquoise(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MediumVioletRed(This, value) \
    ((This)->lpVtbl->get_MediumVioletRed(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MidnightBlue(This, value) \
    ((This)->lpVtbl->get_MidnightBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MintCream(This, value) \
    ((This)->lpVtbl->get_MintCream(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_MistyRose(This, value) \
    ((This)->lpVtbl->get_MistyRose(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Moccasin(This, value) \
    ((This)->lpVtbl->get_Moccasin(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_NavajoWhite(This, value) \
    ((This)->lpVtbl->get_NavajoWhite(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Navy(This, value) \
    ((This)->lpVtbl->get_Navy(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_OldLace(This, value) \
    ((This)->lpVtbl->get_OldLace(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Olive(This, value) \
    ((This)->lpVtbl->get_Olive(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_OliveDrab(This, value) \
    ((This)->lpVtbl->get_OliveDrab(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Orange(This, value) \
    ((This)->lpVtbl->get_Orange(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_OrangeRed(This, value) \
    ((This)->lpVtbl->get_OrangeRed(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Orchid(This, value) \
    ((This)->lpVtbl->get_Orchid(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PaleGoldenrod(This, value) \
    ((This)->lpVtbl->get_PaleGoldenrod(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PaleGreen(This, value) \
    ((This)->lpVtbl->get_PaleGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PaleTurquoise(This, value) \
    ((This)->lpVtbl->get_PaleTurquoise(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PaleVioletRed(This, value) \
    ((This)->lpVtbl->get_PaleVioletRed(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PapayaWhip(This, value) \
    ((This)->lpVtbl->get_PapayaWhip(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PeachPuff(This, value) \
    ((This)->lpVtbl->get_PeachPuff(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Peru(This, value) \
    ((This)->lpVtbl->get_Peru(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Pink(This, value) \
    ((This)->lpVtbl->get_Pink(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Plum(This, value) \
    ((This)->lpVtbl->get_Plum(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_PowderBlue(This, value) \
    ((This)->lpVtbl->get_PowderBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Purple(This, value) \
    ((This)->lpVtbl->get_Purple(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Red(This, value) \
    ((This)->lpVtbl->get_Red(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_RosyBrown(This, value) \
    ((This)->lpVtbl->get_RosyBrown(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_RoyalBlue(This, value) \
    ((This)->lpVtbl->get_RoyalBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SaddleBrown(This, value) \
    ((This)->lpVtbl->get_SaddleBrown(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Salmon(This, value) \
    ((This)->lpVtbl->get_Salmon(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SandyBrown(This, value) \
    ((This)->lpVtbl->get_SandyBrown(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SeaGreen(This, value) \
    ((This)->lpVtbl->get_SeaGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SeaShell(This, value) \
    ((This)->lpVtbl->get_SeaShell(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Sienna(This, value) \
    ((This)->lpVtbl->get_Sienna(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Silver(This, value) \
    ((This)->lpVtbl->get_Silver(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SkyBlue(This, value) \
    ((This)->lpVtbl->get_SkyBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SlateBlue(This, value) \
    ((This)->lpVtbl->get_SlateBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SlateGray(This, value) \
    ((This)->lpVtbl->get_SlateGray(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Snow(This, value) \
    ((This)->lpVtbl->get_Snow(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SpringGreen(This, value) \
    ((This)->lpVtbl->get_SpringGreen(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_SteelBlue(This, value) \
    ((This)->lpVtbl->get_SteelBlue(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Tan(This, value) \
    ((This)->lpVtbl->get_Tan(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Teal(This, value) \
    ((This)->lpVtbl->get_Teal(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Thistle(This, value) \
    ((This)->lpVtbl->get_Thistle(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Tomato(This, value) \
    ((This)->lpVtbl->get_Tomato(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Transparent(This, value) \
    ((This)->lpVtbl->get_Transparent(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Turquoise(This, value) \
    ((This)->lpVtbl->get_Turquoise(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Violet(This, value) \
    ((This)->lpVtbl->get_Violet(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Wheat(This, value) \
    ((This)->lpVtbl->get_Wheat(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_White(This, value) \
    ((This)->lpVtbl->get_White(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_WhiteSmoke(This, value) \
    ((This)->lpVtbl->get_WhiteSmoke(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_Yellow(This, value) \
    ((This)->lpVtbl->get_Yellow(This, value))

#define __x_ABI_CMicrosoft_CUI_CIColorsStatics_get_YellowGreen(This, value) \
    ((This)->lpVtbl->get_YellowGreen(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CIColorsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CIColorsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.ColorHelper
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.IColorHelperStatics2 interface starting with version 1.6 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.IColorHelperStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.IColorHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_ColorHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_ColorHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_ColorHelper[] = L"Microsoft.UI.ColorHelper";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Colors
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.IColorsStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.IColors ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Colors_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Colors_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Colors[] = L"Microsoft.UI.Colors";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui_p_h__

#endif // __microsoft2Eui_h__
