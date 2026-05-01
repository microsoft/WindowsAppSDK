
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
#ifndef __microsoft2Ewindows2Ewidgets2Enotifications_h__
#define __microsoft2Ewindows2Ewidgets2Enotifications_h__
#ifndef __microsoft2Ewindows2Ewidgets2Enotifications_p_h__
#define __microsoft2Ewindows2Ewidgets2Enotifications_p_h__


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
#if !defined(MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION 0xc0000
#endif // defined(MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION)

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
#include "Microsoft.Windows.Widgets.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    interface IFeedAnnouncement;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncement

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    interface IFeedAnnouncementFactory;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncementFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    interface IFeedAnnouncementInvokedArgs;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncementInvokedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct DateTime DateTime;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct TimeSpan TimeSpan;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            class Uri;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IUriRuntimeClass;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIUriRuntimeClass ABI::Windows::Foundation::IUriRuntimeClass

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    typedef enum AnnouncementActionKind : int AnnouncementActionKind;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    typedef enum AnnouncementTextColor : int AnnouncementTextColor;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    class FeedAnnouncement;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Widgets.Notifications.AnnouncementActionKind
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    enum AnnouncementActionKind : int
                    {
                        AnnouncementActionKind_Shown = 0,
                        AnnouncementActionKind_Engaged = 1,
                    };
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Struct Microsoft.Windows.Widgets.Notifications.AnnouncementTextColor
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    enum AnnouncementTextColor : int
                    {
                        AnnouncementTextColor_Default = 0,
                        AnnouncementTextColor_Dark = 1,
                        AnnouncementTextColor_Light = 2,
                        AnnouncementTextColor_Accent = 3,
                        AnnouncementTextColor_Good = 4,
                        AnnouncementTextColor_Warning = 5,
                        AnnouncementTextColor_Attention = 6,
                    };
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Notifications.IFeedAnnouncement
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Notifications.FeedAnnouncement
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Notifications_IFeedAnnouncement[] = L"Microsoft.Windows.Widgets.Notifications.IFeedAnnouncement";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    MIDL_INTERFACE("b88e8c2c-d251-5344-acc2-8cf9ba07ec15")
                    IFeedAnnouncement : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Id(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Id(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PrimaryText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PrimaryText(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SecondaryText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SecondaryText(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LightModeIconUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LightModeIconUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DarkModeIconUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DarkModeIconUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PrimaryTextColor(
                            ABI::Microsoft::Windows::Widgets::Notifications::AnnouncementTextColor* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PrimaryTextColor(
                            ABI::Microsoft::Windows::Widgets::Notifications::AnnouncementTextColor value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SecondaryTextColor(
                            ABI::Microsoft::Windows::Widgets::Notifications::AnnouncementTextColor* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SecondaryTextColor(
                            ABI::Microsoft::Windows::Widgets::Notifications::AnnouncementTextColor value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CustomAccessibilityText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CustomAccessibilityText(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsSecondaryTextSubtle(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsSecondaryTextSubtle(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ShowBadgeIfUserNotEngaged(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ShowBadgeIfUserNotEngaged(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpirationTime(
                            ABI::Windows::Foundation::DateTime* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExpirationTime(
                            ABI::Windows::Foundation::DateTime value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Duration(
                            ABI::Windows::Foundation::TimeSpan* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Duration(
                            ABI::Windows::Foundation::TimeSpan value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFeedAnnouncement = _uuidof(IFeedAnnouncement);
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Notifications.FeedAnnouncement
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Notifications_IFeedAnnouncementFactory[] = L"Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    MIDL_INTERFACE("22074243-46d8-5af2-8715-1c76d1cb774c")
                    IFeedAnnouncementFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING id,
                            HSTRING primaryText,
                            HSTRING secondaryText,
                            ABI::Windows::Foundation::IUriRuntimeClass* lightModeIcon,
                            ABI::Windows::Foundation::IUriRuntimeClass* darkModeIcon,
                            ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncement** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFeedAnnouncementFactory = _uuidof(IFeedAnnouncementFactory);
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Notifications.FeedAnnouncementInvokedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Notifications_IFeedAnnouncementInvokedArgs[] = L"Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementInvokedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    MIDL_INTERFACE("70a48d98-323d-5f19-a1e1-b63fe36edbf2")
                    IFeedAnnouncementInvokedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AnnouncementId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ActionKind(
                            ABI::Microsoft::Windows::Widgets::Notifications::AnnouncementActionKind* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IFeedAnnouncementInvokedArgs = _uuidof(IFeedAnnouncementInvokedArgs);
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Notifications.FeedAnnouncement
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementFactory interface starting with version 5.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Notifications.IFeedAnnouncement ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncement_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncement_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Notifications_FeedAnnouncement[] = L"Microsoft.Windows.Widgets.Notifications.FeedAnnouncement";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Notifications.FeedAnnouncementInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementInvokedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncementInvokedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncementInvokedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Notifications_FeedAnnouncementInvokedArgs[] = L"Microsoft.Windows.Widgets.Notifications.FeedAnnouncementInvokedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CWindows_CFoundation_CDateTime __x_ABI_CWindows_CFoundation_CDateTime;

typedef struct __x_ABI_CWindows_CFoundation_CTimeSpan __x_ABI_CWindows_CFoundation_CTimeSpan;

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementActionKind __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementActionKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor;

/*
 *
 * Struct Microsoft.Windows.Widgets.Notifications.AnnouncementActionKind
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementActionKind
{
    AnnouncementActionKind_Shown = 0,
    AnnouncementActionKind_Engaged = 1,
};
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Struct Microsoft.Windows.Widgets.Notifications.AnnouncementTextColor
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor
{
    AnnouncementTextColor_Default = 0,
    AnnouncementTextColor_Dark = 1,
    AnnouncementTextColor_Light = 2,
    AnnouncementTextColor_Accent = 3,
    AnnouncementTextColor_Good = 4,
    AnnouncementTextColor_Warning = 5,
    AnnouncementTextColor_Attention = 6,
};
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Notifications.IFeedAnnouncement
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Notifications.FeedAnnouncement
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Notifications_IFeedAnnouncement[] = L"Microsoft.Windows.Widgets.Notifications.IFeedAnnouncement";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Id)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_PrimaryText)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_PrimaryText)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_SecondaryText)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_SecondaryText)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_LightModeIconUri)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_LightModeIconUri)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_DarkModeIconUri)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_DarkModeIconUri)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_PrimaryTextColor)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor* value);
    HRESULT (STDMETHODCALLTYPE* put_PrimaryTextColor)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor value);
    HRESULT (STDMETHODCALLTYPE* get_SecondaryTextColor)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor* value);
    HRESULT (STDMETHODCALLTYPE* put_SecondaryTextColor)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementTextColor value);
    HRESULT (STDMETHODCALLTYPE* get_CustomAccessibilityText)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CustomAccessibilityText)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_IsSecondaryTextSubtle)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsSecondaryTextSubtle)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ShowBadgeIfUserNotEngaged)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ShowBadgeIfUserNotEngaged)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ExpirationTime)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime* value);
    HRESULT (STDMETHODCALLTYPE* put_ExpirationTime)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime value);
    HRESULT (STDMETHODCALLTYPE* get_Duration)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan* value);
    HRESULT (STDMETHODCALLTYPE* put_Duration)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* This,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_Id(This, value) \
    ((This)->lpVtbl->put_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_PrimaryText(This, value) \
    ((This)->lpVtbl->get_PrimaryText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_PrimaryText(This, value) \
    ((This)->lpVtbl->put_PrimaryText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_SecondaryText(This, value) \
    ((This)->lpVtbl->get_SecondaryText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_SecondaryText(This, value) \
    ((This)->lpVtbl->put_SecondaryText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_LightModeIconUri(This, value) \
    ((This)->lpVtbl->get_LightModeIconUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_LightModeIconUri(This, value) \
    ((This)->lpVtbl->put_LightModeIconUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_DarkModeIconUri(This, value) \
    ((This)->lpVtbl->get_DarkModeIconUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_DarkModeIconUri(This, value) \
    ((This)->lpVtbl->put_DarkModeIconUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_PrimaryTextColor(This, value) \
    ((This)->lpVtbl->get_PrimaryTextColor(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_PrimaryTextColor(This, value) \
    ((This)->lpVtbl->put_PrimaryTextColor(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_SecondaryTextColor(This, value) \
    ((This)->lpVtbl->get_SecondaryTextColor(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_SecondaryTextColor(This, value) \
    ((This)->lpVtbl->put_SecondaryTextColor(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_CustomAccessibilityText(This, value) \
    ((This)->lpVtbl->get_CustomAccessibilityText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_CustomAccessibilityText(This, value) \
    ((This)->lpVtbl->put_CustomAccessibilityText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_IsSecondaryTextSubtle(This, value) \
    ((This)->lpVtbl->get_IsSecondaryTextSubtle(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_IsSecondaryTextSubtle(This, value) \
    ((This)->lpVtbl->put_IsSecondaryTextSubtle(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_ShowBadgeIfUserNotEngaged(This, value) \
    ((This)->lpVtbl->get_ShowBadgeIfUserNotEngaged(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_ShowBadgeIfUserNotEngaged(This, value) \
    ((This)->lpVtbl->put_ShowBadgeIfUserNotEngaged(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_ExpirationTime(This, value) \
    ((This)->lpVtbl->get_ExpirationTime(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_ExpirationTime(This, value) \
    ((This)->lpVtbl->put_ExpirationTime(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_get_Duration(This, value) \
    ((This)->lpVtbl->get_Duration(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_put_Duration(This, value) \
    ((This)->lpVtbl->put_Duration(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Notifications.FeedAnnouncement
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Notifications_IFeedAnnouncementFactory[] = L"Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory* This,
        HSTRING id,
        HSTRING primaryText,
        HSTRING secondaryText,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* lightModeIcon,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* darkModeIcon,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_CreateInstance(This, id, primaryText, secondaryText, lightModeIcon, darkModeIcon, value) \
    ((This)->lpVtbl->CreateInstance(This, id, primaryText, secondaryText, lightModeIcon, darkModeIcon, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Notifications.FeedAnnouncementInvokedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Notifications_IFeedAnnouncementInvokedArgs[] = L"Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementInvokedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AnnouncementId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ActionKind)(__x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* This,
        enum __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CAnnouncementActionKind* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_get_AnnouncementId(This, value) \
    ((This)->lpVtbl->get_AnnouncementId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_get_ActionKind(This, value) \
    ((This)->lpVtbl->get_ActionKind(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Notifications.FeedAnnouncement
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementFactory interface starting with version 5.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Notifications.IFeedAnnouncement ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncement_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncement_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Notifications_FeedAnnouncement[] = L"Microsoft.Windows.Widgets.Notifications.FeedAnnouncement";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Notifications.FeedAnnouncementInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Notifications.IFeedAnnouncementInvokedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncementInvokedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Notifications_FeedAnnouncementInvokedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Notifications_FeedAnnouncementInvokedArgs[] = L"Microsoft.Windows.Widgets.Notifications.FeedAnnouncementInvokedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Ewidgets2Enotifications_p_h__

#endif // __microsoft2Ewindows2Ewidgets2Enotifications_h__
