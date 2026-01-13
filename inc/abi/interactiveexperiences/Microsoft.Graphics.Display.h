
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
#ifndef __microsoft2Egraphics2Edisplay_h__
#define __microsoft2Egraphics2Edisplay_h__
#ifndef __microsoft2Egraphics2Edisplay_p_h__
#define __microsoft2Egraphics2Edisplay_p_h__


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
#include "Microsoft.UI.Dispatching.h"
#include "Windows.Storage.Streams.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                interface IDisplayAdvancedColorInfo;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo ABI::Microsoft::Graphics::Display::IDisplayAdvancedColorInfo

#endif // ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                interface IDisplayInformation;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation ABI::Microsoft::Graphics::Display::IDisplayInformation

#endif // ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                interface IDisplayInformationStatics;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics ABI::Microsoft::Graphics::Display::IDisplayInformationStatics

#endif // ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            namespace Streams {
                interface IRandomAccessStream;
            } /* Streams */
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream ABI::Windows::Storage::Streams::IRandomAccessStream

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("430ecece-1418-5d19-81b2-5ddb381603cc"))
IAsyncOperation<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IAsyncOperation_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Windows.Storage.Streams.IRandomAccessStream>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("398c4183-793d-5b00-819b-4aef92485e94"))
IAsyncOperationCompletedHandler<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.Storage.Streams.IRandomAccessStream>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                class DisplayInformation;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

#ifndef DEF___FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a8d63481-b7e5-551a-a5ea-8632c543dcc9"))
ITypedEventHandler<ABI::Microsoft::Graphics::Display::DisplayInformation*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Graphics::Display::DisplayInformation*, ABI::Microsoft::Graphics::Display::IDisplayInformation*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Graphics.Display.DisplayInformation, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Graphics::Display::DisplayInformation*, IInspectable*> __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherQueue;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueue;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue ABI::Microsoft::UI::Dispatching::IDispatcherQueue

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct DisplayId DisplayId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

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

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Point Point;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                typedef enum DisplayAdvancedColorKind : int DisplayAdvancedColorKind;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                typedef enum DisplayHdrMetadataFormat : int DisplayHdrMetadataFormat;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                class DisplayAdvancedColorInfo;
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Graphics.Display.DisplayAdvancedColorKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                enum DisplayAdvancedColorKind : int
                {
                    DisplayAdvancedColorKind_StandardDynamicRange = 0,
                    DisplayAdvancedColorKind_WideColorGamut = 1,
                    DisplayAdvancedColorKind_HighDynamicRange = 2,
                };
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Struct Microsoft.Graphics.Display.DisplayHdrMetadataFormat
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                enum DisplayHdrMetadataFormat : int
                {
                    DisplayHdrMetadataFormat_Hdr10 = 0,
                    DisplayHdrMetadataFormat_Hdr10Plus = 1,
                };
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.Graphics.Display.IDisplayAdvancedColorInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Display.DisplayAdvancedColorInfo
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Display_IDisplayAdvancedColorInfo[] = L"Microsoft.Graphics.Display.IDisplayAdvancedColorInfo";
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                MIDL_INTERFACE("b44f0f47-7065-5175-ba3e-714489c85a3e")
                IDisplayAdvancedColorInfo : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_CurrentAdvancedColorKind(
                        ABI::Microsoft::Graphics::Display::DisplayAdvancedColorKind* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RedPrimary(
                        ABI::Windows::Foundation::Point* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_GreenPrimary(
                        ABI::Windows::Foundation::Point* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_BluePrimary(
                        ABI::Windows::Foundation::Point* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_WhitePoint(
                        ABI::Windows::Foundation::Point* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MaxLuminanceInNits(
                        DOUBLE* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MinLuminanceInNits(
                        DOUBLE* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MaxAverageFullFrameLuminanceInNits(
                        DOUBLE* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SdrWhiteLevelInNits(
                        DOUBLE* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsHdrMetadataFormatCurrentlySupported(
                        ABI::Microsoft::Graphics::Display::DisplayHdrMetadataFormat format,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE IsAdvancedColorKindAvailable(
                        ABI::Microsoft::Graphics::Display::DisplayAdvancedColorKind kind,
                        boolean* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayAdvancedColorInfo = _uuidof(IDisplayAdvancedColorInfo);
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.Graphics.Display.IDisplayInformation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Display.DisplayInformation
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Display_IDisplayInformation[] = L"Microsoft.Graphics.Display.IDisplayInformation";
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                MIDL_INTERFACE("f0d58d4f-84ce-5b27-b222-4f8f7dc0aaeb")
                IDisplayInformation : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsStereoEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_IsStereoEnabledChanged(
                        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_IsStereoEnabledChanged(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetColorProfileAsync(
                        __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetColorProfile(
                        ABI::Windows::Storage::Streams::IRandomAccessStream** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_ColorProfileChanged(
                        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_ColorProfileChanged(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetAdvancedColorInfo(
                        ABI::Microsoft::Graphics::Display::IDisplayAdvancedColorInfo** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_AdvancedColorInfoChanged(
                        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_AdvancedColorInfoChanged(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Destroyed(
                        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Destroyed(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayInformation = _uuidof(IDisplayInformation);
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.Graphics.Display.IDisplayInformationStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Display.DisplayInformation
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Display_IDisplayInformationStatics[] = L"Microsoft.Graphics.Display.IDisplayInformationStatics";
namespace ABI {
    namespace Microsoft {
        namespace Graphics {
            namespace Display {
                MIDL_INTERFACE("2de85048-37fa-56c0-ac30-47e2044d7ea8")
                IDisplayInformationStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateForWindowId(
                        ABI::Microsoft::UI::WindowId windowId,
                        ABI::Microsoft::Graphics::Display::IDisplayInformation** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateForDisplayId(
                        ABI::Microsoft::UI::DisplayId displayId,
                        ABI::Microsoft::Graphics::Display::IDisplayInformation** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayInformationStatics = _uuidof(IDisplayInformationStatics);
            } /* Display */
        } /* Graphics */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Class Microsoft.Graphics.Display.DisplayAdvancedColorInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Class implements the following interfaces:
 *    Microsoft.Graphics.Display.IDisplayAdvancedColorInfo ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#ifndef RUNTIMECLASS_Microsoft_Graphics_Display_DisplayAdvancedColorInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Graphics_Display_DisplayAdvancedColorInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Graphics_Display_DisplayAdvancedColorInfo[] = L"Microsoft.Graphics.Display.DisplayAdvancedColorInfo";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Class Microsoft.Graphics.Display.DisplayInformation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Graphics.Display.IDisplayInformationStatics interface starting with version 1.2 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Graphics.Display.IDisplayInformation ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#ifndef RUNTIMECLASS_Microsoft_Graphics_Display_DisplayInformation_DEFINED
#define RUNTIMECLASS_Microsoft_Graphics_Display_DisplayInformation_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Graphics_Display_DisplayInformation[] = L"Microsoft.Graphics.Display.DisplayInformation";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo;

#endif // ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation;

#endif // ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics;

#endif // ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream;

typedef struct __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** result);

    END_INTERFACE
} __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl;

interface __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream
{
    CONST_VTBL struct __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream;

typedef struct __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl;

interface __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* This,
        __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CDisplayId __x_ABI_CMicrosoft_CUI_CDisplayId;

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

typedef enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayAdvancedColorKind __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayAdvancedColorKind;

typedef enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayHdrMetadataFormat __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayHdrMetadataFormat;

/*
 *
 * Struct Microsoft.Graphics.Display.DisplayAdvancedColorKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayAdvancedColorKind
{
    DisplayAdvancedColorKind_StandardDynamicRange = 0,
    DisplayAdvancedColorKind_WideColorGamut = 1,
    DisplayAdvancedColorKind_HighDynamicRange = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Struct Microsoft.Graphics.Display.DisplayHdrMetadataFormat
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayHdrMetadataFormat
{
    DisplayHdrMetadataFormat_Hdr10 = 0,
    DisplayHdrMetadataFormat_Hdr10Plus = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.Graphics.Display.IDisplayAdvancedColorInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Display.DisplayAdvancedColorInfo
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Display_IDisplayAdvancedColorInfo[] = L"Microsoft.Graphics.Display.IDisplayAdvancedColorInfo";
typedef struct __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfoVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CurrentAdvancedColorKind)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayAdvancedColorKind* value);
    HRESULT (STDMETHODCALLTYPE* get_RedPrimary)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_GreenPrimary)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_BluePrimary)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_WhitePoint)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        struct __x_ABI_CWindows_CFoundation_CPoint* value);
    HRESULT (STDMETHODCALLTYPE* get_MaxLuminanceInNits)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_MinLuminanceInNits)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_MaxAverageFullFrameLuminanceInNits)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_SdrWhiteLevelInNits)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* IsHdrMetadataFormatCurrentlySupported)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayHdrMetadataFormat format,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsAdvancedColorKindAvailable)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo* This,
        enum __x_ABI_CMicrosoft_CGraphics_CDisplay_CDisplayAdvancedColorKind kind,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfoVtbl;

interface __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfoVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_CurrentAdvancedColorKind(This, value) \
    ((This)->lpVtbl->get_CurrentAdvancedColorKind(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_RedPrimary(This, value) \
    ((This)->lpVtbl->get_RedPrimary(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_GreenPrimary(This, value) \
    ((This)->lpVtbl->get_GreenPrimary(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_BluePrimary(This, value) \
    ((This)->lpVtbl->get_BluePrimary(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_WhitePoint(This, value) \
    ((This)->lpVtbl->get_WhitePoint(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_MaxLuminanceInNits(This, value) \
    ((This)->lpVtbl->get_MaxLuminanceInNits(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_MinLuminanceInNits(This, value) \
    ((This)->lpVtbl->get_MinLuminanceInNits(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_MaxAverageFullFrameLuminanceInNits(This, value) \
    ((This)->lpVtbl->get_MaxAverageFullFrameLuminanceInNits(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_get_SdrWhiteLevelInNits(This, value) \
    ((This)->lpVtbl->get_SdrWhiteLevelInNits(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_IsHdrMetadataFormatCurrentlySupported(This, format, result) \
    ((This)->lpVtbl->IsHdrMetadataFormatCurrentlySupported(This, format, result))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_IsAdvancedColorKindAvailable(This, kind, result) \
    ((This)->lpVtbl->IsAdvancedColorKindAvailable(This, kind, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.Graphics.Display.IDisplayInformation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Display.DisplayInformation
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Display_IDisplayInformation[] = L"Microsoft.Graphics.Display.IDisplayInformation";
typedef struct __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* get_IsStereoEnabled)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* add_IsStereoEnabledChanged)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_IsStereoEnabledChanged)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* GetColorProfileAsync)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream** operation);
    HRESULT (STDMETHODCALLTYPE* GetColorProfile)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** result);
    HRESULT (STDMETHODCALLTYPE* add_ColorProfileChanged)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ColorProfileChanged)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* GetAdvancedColorInfo)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayAdvancedColorInfo** result);
    HRESULT (STDMETHODCALLTYPE* add_AdvancedColorInfoChanged)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_AdvancedColorInfoChanged)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_Destroyed)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        __FITypedEventHandler_2_Microsoft__CGraphics__CDisplay__CDisplayInformation_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Destroyed)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationVtbl;

interface __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_get_IsStereoEnabled(This, value) \
    ((This)->lpVtbl->get_IsStereoEnabled(This, value))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_add_IsStereoEnabledChanged(This, handler, token) \
    ((This)->lpVtbl->add_IsStereoEnabledChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_remove_IsStereoEnabledChanged(This, token) \
    ((This)->lpVtbl->remove_IsStereoEnabledChanged(This, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_GetColorProfileAsync(This, operation) \
    ((This)->lpVtbl->GetColorProfileAsync(This, operation))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_GetColorProfile(This, result) \
    ((This)->lpVtbl->GetColorProfile(This, result))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_add_ColorProfileChanged(This, handler, token) \
    ((This)->lpVtbl->add_ColorProfileChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_remove_ColorProfileChanged(This, token) \
    ((This)->lpVtbl->remove_ColorProfileChanged(This, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_GetAdvancedColorInfo(This, result) \
    ((This)->lpVtbl->GetAdvancedColorInfo(This, result))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_add_AdvancedColorInfoChanged(This, handler, token) \
    ((This)->lpVtbl->add_AdvancedColorInfoChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_remove_AdvancedColorInfoChanged(This, token) \
    ((This)->lpVtbl->remove_AdvancedColorInfoChanged(This, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_add_Destroyed(This, handler, token) \
    ((This)->lpVtbl->add_Destroyed(This, handler, token))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_remove_Destroyed(This, token) \
    ((This)->lpVtbl->remove_Destroyed(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.Graphics.Display.IDisplayInformationStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.Graphics.Display.DisplayInformation
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Graphics_Display_IDisplayInformationStatics[] = L"Microsoft.Graphics.Display.IDisplayInformationStatics";
typedef struct __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForWindowId)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation** result);
    HRESULT (STDMETHODCALLTYPE* CreateForDisplayId)(__x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId displayId,
        __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformation** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStaticsVtbl;

interface __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_CreateForWindowId(This, windowId, result) \
    ((This)->lpVtbl->CreateForWindowId(This, windowId, result))

#define __x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_CreateForDisplayId(This, displayId, result) \
    ((This)->lpVtbl->CreateForDisplayId(This, displayId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Class Microsoft.Graphics.Display.DisplayAdvancedColorInfo
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Class implements the following interfaces:
 *    Microsoft.Graphics.Display.IDisplayAdvancedColorInfo ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#ifndef RUNTIMECLASS_Microsoft_Graphics_Display_DisplayAdvancedColorInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Graphics_Display_DisplayAdvancedColorInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Graphics_Display_DisplayAdvancedColorInfo[] = L"Microsoft.Graphics.Display.DisplayAdvancedColorInfo";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Class Microsoft.Graphics.Display.DisplayInformation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Graphics.Display.IDisplayInformationStatics interface starting with version 1.2 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Graphics.Display.IDisplayInformation ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#ifndef RUNTIMECLASS_Microsoft_Graphics_Display_DisplayInformation_DEFINED
#define RUNTIMECLASS_Microsoft_Graphics_Display_DisplayInformation_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Graphics_Display_DisplayInformation[] = L"Microsoft.Graphics.Display.DisplayInformation";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Egraphics2Edisplay_p_h__

#endif // __microsoft2Egraphics2Edisplay_h__
