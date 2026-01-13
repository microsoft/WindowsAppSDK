
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
#ifndef __microsoft2Ewindows2Epushnotifications_h__
#define __microsoft2Ewindows2Epushnotifications_h__
#ifndef __microsoft2Ewindows2Epushnotifications_p_h__
#define __microsoft2Ewindows2Epushnotifications_p_h__


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
#if !defined(MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION)

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
#include "Windows.ApplicationModel.Background.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                interface IPushNotificationChannel;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel ABI::Microsoft::Windows::PushNotifications::IPushNotificationChannel

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                interface IPushNotificationCreateChannelResult;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult ABI::Microsoft::Windows::PushNotifications::IPushNotificationCreateChannelResult

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                interface IPushNotificationManager;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager ABI::Microsoft::Windows::PushNotifications::IPushNotificationManager

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                interface IPushNotificationManagerStatics;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics ABI::Microsoft::Windows::PushNotifications::IPushNotificationManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                interface IPushNotificationReceivedEventArgs;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs ABI::Microsoft::Windows::PushNotifications::IPushNotificationReceivedEventArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                class PushNotificationCreateChannelResult;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                typedef struct PushNotificationCreateChannelStatus PushNotificationCreateChannelStatus;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("7d14c00d-233f-5126-83b7-e84a5c3d9cce"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, ABI::Microsoft::Windows::PushNotifications::IPushNotificationCreateChannelResult*>, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult, Microsoft.Windows.PushNotifications.PushNotificationCreateChannelStatus>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE */

#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("f9b84a9d-7d59-5445-9cf1-33a6c4518241"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, ABI::Microsoft::Windows::PushNotifications::IPushNotificationCreateChannelResult*>, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult, Microsoft.Windows.PushNotifications.PushNotificationCreateChannelStatus>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE */

#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("5a89cffd-b4d1-5dc0-add8-7af59fa52b49"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, ABI::Microsoft::Windows::PushNotifications::IPushNotificationCreateChannelResult*>, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult, Microsoft.Windows.PushNotifications.PushNotificationCreateChannelStatus>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult*, struct ABI::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_USE */

#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                class PushNotificationManager;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                class PushNotificationReceivedEventArgs;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("64f9e503-18cf-56bf-b85a-97fb8261e2d2"))
ITypedEventHandler<ABI::Microsoft::Windows::PushNotifications::PushNotificationManager*, ABI::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::PushNotifications::PushNotificationManager*, ABI::Microsoft::Windows::PushNotifications::IPushNotificationManager*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs*, ABI::Microsoft::Windows::PushNotifications::IPushNotificationReceivedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.PushNotifications.PushNotificationManager, Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::PushNotifications::PushNotificationManager*, ABI::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs*> __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_USE */

#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundTaskCanceledEventHandler;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler ABI::Windows::ApplicationModel::Background::IBackgroundTaskCanceledEventHandler

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                class BackgroundTaskDeferral;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundTaskDeferral;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral ABI::Windows::ApplicationModel::Background::IBackgroundTaskDeferral

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_FWD_DEFINED__

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
            namespace PushNotifications {
                typedef enum PushNotificationChannelStatus : int PushNotificationChannelStatus;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                class PushNotificationChannel;
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.PushNotifications.PushNotificationChannelStatus
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                enum PushNotificationChannelStatus : int
                {
                    PushNotificationChannelStatus_InProgress = 0,
                    PushNotificationChannelStatus_InProgressRetry = 1,
                    PushNotificationChannelStatus_CompletedSuccess = 2,
                    PushNotificationChannelStatus_CompletedFailure = 3,
                };
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.PushNotifications.PushNotificationCreateChannelStatus
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                struct PushNotificationCreateChannelStatus
                {
                    ABI::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus status;
                    HRESULT extendedError;
                    UINT32 retryCount;
                };
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationChannel
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationChannel
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationChannel[] = L"Microsoft.Windows.PushNotifications.IPushNotificationChannel";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                MIDL_INTERFACE("da28bbcb-7695-5d38-af82-f30b72fef1f6")
                IPushNotificationChannel : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Uri(
                        ABI::Windows::Foundation::IUriRuntimeClass** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExpirationTime(
                        ABI::Windows::Foundation::DateTime* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Close(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IPushNotificationChannel = _uuidof(IPushNotificationChannel);
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationCreateChannelResult
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationCreateChannelResult[] = L"Microsoft.Windows.PushNotifications.IPushNotificationCreateChannelResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                MIDL_INTERFACE("4df3717f-5d33-56e9-b381-1b350c95722e")
                IPushNotificationCreateChannelResult : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Channel(
                        ABI::Microsoft::Windows::PushNotifications::IPushNotificationChannel** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                        HRESULT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Status(
                        ABI::Microsoft::Windows::PushNotifications::PushNotificationChannelStatus* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IPushNotificationCreateChannelResult = _uuidof(IPushNotificationCreateChannelResult);
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationManager
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationManager[] = L"Microsoft.Windows.PushNotifications.IPushNotificationManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                MIDL_INTERFACE("902f4aba-ff63-5dfe-a88f-15cc6bed55ff")
                IPushNotificationManager : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Register(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Unregister(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UnregisterAll(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateChannelAsync(
                        GUID remoteId,
                        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_PushReceived(
                        __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_PushReceived(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IPushNotificationManager = _uuidof(IPushNotificationManager);
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationManagerStatics
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationManagerStatics[] = L"Microsoft.Windows.PushNotifications.IPushNotificationManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                MIDL_INTERFACE("71329470-1b55-58dc-a00c-68c26f2d8bd9")
                IPushNotificationManagerStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE IsSupported(
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Default(
                        ABI::Microsoft::Windows::PushNotifications::IPushNotificationManager** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IPushNotificationManagerStatics = _uuidof(IPushNotificationManagerStatics);
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationReceivedEventArgs
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationReceivedEventArgs[] = L"Microsoft.Windows.PushNotifications.IPushNotificationReceivedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace PushNotifications {
                MIDL_INTERFACE("fbd4ec53-bb83-5495-8777-d3cf13e4299c")
                IPushNotificationReceivedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Payload(
                        UINT32* valueLength,
                        BYTE** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetDeferral(
                        ABI::Windows::ApplicationModel::Background::IBackgroundTaskDeferral** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Canceled(
                        ABI::Windows::ApplicationModel::Background::IBackgroundTaskCanceledEventHandler* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Canceled(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IPushNotificationReceivedEventArgs = _uuidof(IPushNotificationReceivedEventArgs);
            } /* PushNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationChannel
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationChannel ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationChannel_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationChannel_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationChannel[] = L"Microsoft.Windows.PushNotifications.PushNotificationChannel";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationCreateChannelResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationCreateChannelResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationCreateChannelResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationCreateChannelResult[] = L"Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationManager
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.PushNotifications.IPushNotificationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.PushNotifications.PushNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationManager[] = L"Microsoft.Windows.PushNotifications.PushNotificationManager";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationReceivedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationReceivedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationReceivedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationReceivedEventArgs[] = L"Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel;

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationCreateChannelStatus __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationCreateChannelStatus;

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus* asyncInfo,
        struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationCreateChannelStatus progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatusVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs* This,
        __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* sender,
        __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CDateTime __x_ABI_CWindows_CFoundation_CDateTime;

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationChannelStatus __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationChannelStatus;

/*
 *
 * Struct Microsoft.Windows.PushNotifications.PushNotificationChannelStatus
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationChannelStatus
{
    PushNotificationChannelStatus_InProgress = 0,
    PushNotificationChannelStatus_InProgressRetry = 1,
    PushNotificationChannelStatus_CompletedSuccess = 2,
    PushNotificationChannelStatus_CompletedFailure = 3,
};
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.PushNotifications.PushNotificationCreateChannelStatus
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationCreateChannelStatus
{
    enum __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationChannelStatus status;
    HRESULT extendedError;
    UINT32 retryCount;
};
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationChannel
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationChannel
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationChannel[] = L"Microsoft.Windows.PushNotifications.IPushNotificationChannel";
typedef struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannelVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Uri)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* get_ExpirationTime)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime* value);
    HRESULT (STDMETHODCALLTYPE* Close)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannelVtbl;

interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannelVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_get_Uri(This, value) \
    ((This)->lpVtbl->get_Uri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_get_ExpirationTime(This, value) \
    ((This)->lpVtbl->get_ExpirationTime(This, value))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_Close(This) \
    ((This)->lpVtbl->Close(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationCreateChannelResult
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationCreateChannelResult[] = L"Microsoft.Windows.PushNotifications.IPushNotificationCreateChannelResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Channel)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationChannel** value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CPushNotifications_CPushNotificationChannelStatus* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_get_Channel(This, value) \
    ((This)->lpVtbl->get_Channel(This, value))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationCreateChannelResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationManager
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationManager[] = L"Microsoft.Windows.PushNotifications.IPushNotificationManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Register)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* Unregister)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* UnregisterAll)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* CreateChannelAsync)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        GUID remoteId,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelResult_Microsoft__CWindows__CPushNotifications__CPushNotificationCreateChannelStatus** operation);
    HRESULT (STDMETHODCALLTYPE* add_PushReceived)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CPushNotifications__CPushNotificationManager_Microsoft__CWindows__CPushNotifications__CPushNotificationReceivedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_PushReceived)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_Register(This) \
    ((This)->lpVtbl->Register(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_Unregister(This) \
    ((This)->lpVtbl->Unregister(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_UnregisterAll(This) \
    ((This)->lpVtbl->UnregisterAll(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_CreateChannelAsync(This, remoteId, operation) \
    ((This)->lpVtbl->CreateChannelAsync(This, remoteId, operation))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_add_PushReceived(This, handler, token) \
    ((This)->lpVtbl->add_PushReceived(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_remove_PushReceived(This, token) \
    ((This)->lpVtbl->remove_PushReceived(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationManagerStatics
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationManagerStatics[] = L"Microsoft.Windows.PushNotifications.IPushNotificationManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsSupported)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* get_Default)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManager** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_IsSupported(This, result) \
    ((This)->lpVtbl->IsSupported(This, result))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_get_Default(This, value) \
    ((This)->lpVtbl->get_Default(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.PushNotifications.IPushNotificationReceivedEventArgs
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_PushNotifications_IPushNotificationReceivedEventArgs[] = L"Microsoft.Windows.PushNotifications.IPushNotificationReceivedEventArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Payload)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        UINT32* valueLength,
        BYTE** value);
    HRESULT (STDMETHODCALLTYPE* GetDeferral)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskDeferral** result);
    HRESULT (STDMETHODCALLTYPE* add_Canceled)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskCanceledEventHandler* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Canceled)(__x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_get_Payload(This, valueLength, value) \
    ((This)->lpVtbl->get_Payload(This, valueLength, value))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_GetDeferral(This, result) \
    ((This)->lpVtbl->GetDeferral(This, result))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_add_Canceled(This, handler, token) \
    ((This)->lpVtbl->add_Canceled(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_remove_Canceled(This, token) \
    ((This)->lpVtbl->remove_Canceled(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CPushNotifications_CIPushNotificationReceivedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationChannel
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationChannel ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationChannel_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationChannel_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationChannel[] = L"Microsoft.Windows.PushNotifications.PushNotificationChannel";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationCreateChannelResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationCreateChannelResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationCreateChannelResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationCreateChannelResult[] = L"Microsoft.Windows.PushNotifications.PushNotificationCreateChannelResult";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationManager
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.PushNotifications.IPushNotificationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.PushNotifications.PushNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationManager[] = L"Microsoft.Windows.PushNotifications.PushNotificationManager";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs
 *
 * Introduced to Microsoft.Windows.PushNotifications.PushNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.PushNotifications.IPushNotificationReceivedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationReceivedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_PushNotifications_PushNotificationReceivedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_PushNotifications_PushNotificationReceivedEventArgs[] = L"Microsoft.Windows.PushNotifications.PushNotificationReceivedEventArgs";
#endif
#endif // MICROSOFT_WINDOWS_PUSHNOTIFICATIONS_PUSHNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Epushnotifications_p_h__

#endif // __microsoft2Ewindows2Epushnotifications_h__
