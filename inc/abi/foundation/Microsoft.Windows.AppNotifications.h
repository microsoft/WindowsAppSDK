
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
#ifndef __microsoft2Ewindows2Eappnotifications_h__
#define __microsoft2Ewindows2Eappnotifications_h__
#ifndef __microsoft2Ewindows2Eappnotifications_p_h__
#define __microsoft2Ewindows2Eappnotifications_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION 0x40000
#endif // defined(MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION)

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
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotification;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification ABI::Microsoft::Windows::AppNotifications::IAppNotification

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationActivatedEventArgs;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs ABI::Microsoft::Windows::AppNotifications::IAppNotificationActivatedEventArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationActivatedEventArgs2;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2 ABI::Microsoft::Windows::AppNotifications::IAppNotificationActivatedEventArgs2

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationFactory;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory ABI::Microsoft::Windows::AppNotifications::IAppNotificationFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationManager;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager ABI::Microsoft::Windows::AppNotifications::IAppNotificationManager

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationManager2;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2 ABI::Microsoft::Windows::AppNotifications::IAppNotificationManager2

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationManagerStatics;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics ABI::Microsoft::Windows::AppNotifications::IAppNotificationManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationManagerStatics2;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2 ABI::Microsoft::Windows::AppNotifications::IAppNotificationManagerStatics2

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationProgressData;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressData

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                interface IAppNotificationProgressDataFactory;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressDataFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                typedef enum AppNotificationProgressResult : int AppNotificationProgressResult;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("aa739d3f-d458-5d30-b292-de6d52979eb4"))
IAsyncOperation<enum ABI::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> : IAsyncOperation_impl<enum ABI::Microsoft::Windows::AppNotifications::AppNotificationProgressResult>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.AppNotifications.AppNotificationProgressResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<enum ABI::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("566f5620-c1d5-526f-a898-ba7d0da3a56d"))
IAsyncOperationCompletedHandler<enum ABI::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> : IAsyncOperationCompletedHandler_impl<enum ABI::Microsoft::Windows::AppNotifications::AppNotificationProgressResult>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.AppNotifications.AppNotificationProgressResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<enum ABI::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                class AppNotification;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("450e1195-001f-58ff-a652-aabd9bcda5c0"))
IIterator<ABI::Microsoft::Windows::AppNotifications::AppNotification*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppNotifications::AppNotification*, ABI::Microsoft::Windows::AppNotifications::IAppNotification*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.AppNotifications.AppNotification>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::AppNotifications::AppNotification*> __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t;
#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b6fdba11-96fd-5160-b282-52a393823d51"))
IIterable<ABI::Microsoft::Windows::AppNotifications::AppNotification*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppNotifications::AppNotification*, ABI::Microsoft::Windows::AppNotifications::IAppNotification*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.AppNotifications.AppNotification>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::AppNotifications::AppNotification*> __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t;
#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e645c6bd-e8e3-5b12-8b95-963bac29f974"))
IVectorView<ABI::Microsoft::Windows::AppNotifications::AppNotification*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppNotifications::AppNotification*, ABI::Microsoft::Windows::AppNotifications::IAppNotification*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.AppNotifications.AppNotification>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::AppNotifications::AppNotification*> __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t;
#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#define DEF___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("de618ddb-bebc-5c93-91fe-ebd890df7cb7"))
IVector<ABI::Microsoft::Windows::AppNotifications::AppNotification*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppNotifications::AppNotification*, ABI::Microsoft::Windows::AppNotifications::IAppNotification*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.Windows.AppNotifications.AppNotification>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::Windows::AppNotifications::AppNotification*> __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t;
#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#define DEF___FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("704700c2-f4a1-5edd-871a-d0ba8b9b4c59"))
IAsyncOperation<__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification*> : IAsyncOperation_impl<__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Windows.Foundation.Collections.IVector`1<Microsoft.Windows.AppNotifications.AppNotification>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification*> __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t;
#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification ABI::Windows::Foundation::__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#define DEF___FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("fc00bf73-ae70-537b-a702-a85a20bbd714"))
IAsyncOperationCompletedHandler<__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification*> : IAsyncOperationCompletedHandler_impl<__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Windows.Foundation.Collections.IVector`1<Microsoft.Windows.AppNotifications.AppNotification>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification*> __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t;
#define __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("60310303-49c5-52e6-abc6-a9b36eccc716"))
IKeyValuePair<HSTRING, HSTRING> : IKeyValuePair_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, HSTRING> __FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("05eb86f1-7140-5517-b88d-cbaebe57e6b1"))
IIterator<__FIKeyValuePair_2_HSTRING_HSTRING*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING_HSTRING*> __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e9bdaaf0-cbf6-5c72-be90-29cbf3a1319b"))
IIterable<__FIKeyValuePair_2_HSTRING_HSTRING*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING_HSTRING*> __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIMapView_2_HSTRING_HSTRING_USE
#define DEF___FIMapView_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ac7f26f2-feb7-5b2a-8ac4-345bc62caede"))
IMapView<HSTRING, HSTRING> : IMapView_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, HSTRING> __FIMapView_2_HSTRING_HSTRING_t;
#define __FIMapView_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIMap_2_HSTRING_HSTRING_USE
#define DEF___FIMap_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f6d1f700-49c2-52ae-8154-826f9908773c"))
IMap<HSTRING, HSTRING> : IMap_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMap`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMap<HSTRING, HSTRING> __FIMap_2_HSTRING_HSTRING_t;
#define __FIMap_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIMap_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMap_2_HSTRING_HSTRING_USE */


namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                class AppNotificationManager;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                class AppNotificationActivatedEventArgs;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("9909b0b0-ef99-5bce-97c8-78190d411b61"))
ITypedEventHandler<ABI::Microsoft::Windows::AppNotifications::AppNotificationManager*, ABI::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppNotifications::AppNotificationManager*, ABI::Microsoft::Windows::AppNotifications::IAppNotificationManager*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs*, ABI::Microsoft::Windows::AppNotifications::IAppNotificationActivatedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.AppNotifications.AppNotificationManager, Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::AppNotifications::AppNotificationManager*, ABI::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs*> __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_USE */

#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct DateTime DateTime;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IAsyncAction;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIAsyncAction ABI::Windows::Foundation::IAsyncAction

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

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
            namespace AppNotifications {
                typedef enum AppNotificationPriority : int AppNotificationPriority;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                typedef enum AppNotificationSetting : int AppNotificationSetting;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                class AppNotificationProgressData;
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AppNotifications.AppNotificationPriority
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                enum AppNotificationPriority : int
                {
                    AppNotificationPriority_Default = 0,
                    AppNotificationPriority_High = 1,
                };
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.AppNotificationProgressResult
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                enum AppNotificationProgressResult : int
                {
                    AppNotificationProgressResult_Succeeded = 0,
                    AppNotificationProgressResult_AppNotificationNotFound = 1,
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
                    AppNotificationProgressResult_Unsupported = 2,
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
                };
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.AppNotificationSetting
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                enum AppNotificationSetting : int
                {
                    AppNotificationSetting_Enabled = 0,
                    AppNotificationSetting_DisabledForApplication = 1,
                    AppNotificationSetting_DisabledForUser = 2,
                    AppNotificationSetting_DisabledByGroupPolicy = 3,
                    AppNotificationSetting_DisabledByManifest = 4,
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
                    AppNotificationSetting_Unsupported = 5,
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
                };
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotification
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotification
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotification[] = L"Microsoft.Windows.AppNotifications.IAppNotification";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("373a6917-4116-5657-936a-15f99afdd667")
                IAppNotification : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Tag(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Tag(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Group(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Group(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Id(
                        UINT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Payload(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Progress(
                        ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressData** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Progress(
                        ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressData* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Expiration(
                        ABI::Windows::Foundation::DateTime* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Expiration(
                        ABI::Windows::Foundation::DateTime value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExpiresOnReboot(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ExpiresOnReboot(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Priority(
                        ABI::Microsoft::Windows::AppNotifications::AppNotificationPriority* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Priority(
                        ABI::Microsoft::Windows::AppNotifications::AppNotificationPriority value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SuppressDisplay(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_SuppressDisplay(
                        boolean value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotification = _uuidof(IAppNotification);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationActivatedEventArgs[] = L"Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("7a8afaf9-31cb-51d5-82be-db6bd5878b77")
                IAppNotificationActivatedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Argument(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_UserInput(
                        __FIMap_2_HSTRING_HSTRING** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationActivatedEventArgs = _uuidof(IAppNotificationActivatedEventArgs);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs2
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 3.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x30000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationActivatedEventArgs2[] = L"Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("52c06b9b-2c50-5037-9416-a3be47b9d5bd")
                IAppNotificationActivatedEventArgs2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Arguments(
                        __FIMap_2_HSTRING_HSTRING** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationActivatedEventArgs2 = _uuidof(IAppNotificationActivatedEventArgs2);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x30000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotification
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationFactory[] = L"Microsoft.Windows.AppNotifications.IAppNotificationFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("9ffee485-184a-5c65-87a9-c1d94469dbe7")
                IAppNotificationFactory : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                        HSTRING payload,
                        ABI::Microsoft::Windows::AppNotifications::IAppNotification** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationFactory = _uuidof(IAppNotificationFactory);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManager
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManager[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("55129688-b4bd-550b-ae6b-c24061954d91")
                IAppNotificationManager : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Register(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Unregister(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UnregisterAll(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_NotificationInvoked(
                        __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_NotificationInvoked(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Show(
                        ABI::Microsoft::Windows::AppNotifications::IAppNotification* notification
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UpdateAsync(
                        ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressData* data,
                        HSTRING tag,
                        HSTRING group,
                        __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UpdateAsync2(
                        ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressData* data,
                        HSTRING tag,
                        __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Setting(
                        ABI::Microsoft::Windows::AppNotifications::AppNotificationSetting* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveByIdAsync(
                        UINT32 notificationId,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveByTagAsync(
                        HSTRING tag,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveByTagAndGroupAsync(
                        HSTRING tag,
                        HSTRING group,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveByGroupAsync(
                        HSTRING group,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveAllAsync(
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetAllAsync(
                        __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification** operation
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationManager = _uuidof(IAppNotificationManager);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManager2
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManager2[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManager2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("38ba268d-e0c7-522e-a79d-8a29dcdd7135")
                IAppNotificationManager2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Register(
                        HSTRING displayName,
                        ABI::Windows::Foundation::IUriRuntimeClass* iconUri
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationManager2 = _uuidof(IAppNotificationManager2);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManagerStatics[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("6cfc0d8d-84a3-5592-b4c6-e3e7e7c680e4")
                IAppNotificationManagerStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Default(
                        ABI::Microsoft::Windows::AppNotifications::IAppNotificationManager** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationManagerStatics = _uuidof(IAppNotificationManagerStatics);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics2
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManagerStatics2[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("6eb42a35-e82f-5732-98f1-129705602f2e")
                IAppNotificationManagerStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE IsSupported(
                        boolean* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationManagerStatics2 = _uuidof(IAppNotificationManagerStatics2);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationProgressData
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationProgressData
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationProgressData[] = L"Microsoft.Windows.AppNotifications.IAppNotificationProgressData";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("4debfac0-809d-55cb-b879-924821876b97")
                IAppNotificationProgressData : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_SequenceNumber(
                        UINT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_SequenceNumber(
                        UINT32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Title(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Title(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Value(
                        DOUBLE* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Value(
                        DOUBLE value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ValueStringOverride(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ValueStringOverride(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Status(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Status(
                        HSTRING value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationProgressData = _uuidof(IAppNotificationProgressData);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationProgressDataFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationProgressData
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationProgressDataFactory[] = L"Microsoft.Windows.AppNotifications.IAppNotificationProgressDataFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppNotifications {
                MIDL_INTERFACE("c08e4a0f-3a75-55d6-8c3e-14f03ae46046")
                IAppNotificationProgressDataFactory : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                        UINT32 sequenceNumber,
                        ABI::Microsoft::Windows::AppNotifications::IAppNotificationProgressData** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppNotificationProgressDataFactory = _uuidof(IAppNotificationProgressDataFactory);
            } /* AppNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotification
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AppNotifications.IAppNotificationFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotification ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotification_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotification_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotification[] = L"Microsoft.Windows.AppNotifications.AppNotification";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs ** Default Interface **
 *    Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationActivatedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationActivatedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotificationActivatedEventArgs[] = L"Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotificationManager ** Default Interface **
 *    Microsoft.Windows.AppNotifications.IAppNotificationManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotificationManager[] = L"Microsoft.Windows.AppNotifications.AppNotificationManager";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotificationProgressData
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AppNotifications.IAppNotificationProgressDataFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotificationProgressData ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationProgressData_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationProgressData_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotificationProgressData[] = L"Microsoft.Windows.AppNotifications.AppNotificationProgressData";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2 __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2 __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2 __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationProgressResult __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationProgressResult;

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult;

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationProgressResult* result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResultVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResultVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

typedef struct __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl;

interface __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

typedef struct __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __FIIterator_1_Microsoft__CWindows__CAppNotifications__CAppNotification** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl;

interface __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

typedef struct __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

typedef struct __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __FIVectorView_1_Microsoft__CWindows__CAppNotifications__CAppNotification** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl;

interface __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification
{
    CONST_VTBL struct __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

typedef interface __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

typedef struct __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification** result);

    END_INTERFACE
} __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl;

interface __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification
{
    CONST_VTBL struct __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification;

typedef struct __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* This,
        __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl;

interface __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if !defined(____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_HSTRING __FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_HSTRING_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_HSTRING_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        __FIKeyValuePair_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING_HSTRING** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_HSTRING __FIMapView_2_HSTRING_HSTRING;

#if !defined(____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_HSTRING __FIMapView_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING_HSTRING;

typedef struct __FIMapView_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING_HSTRING* This,
        __FIMapView_2_HSTRING_HSTRING** first,
        __FIMapView_2_HSTRING_HSTRING** second);

    END_INTERFACE
} __FIMapView_2_HSTRING_HSTRINGVtbl;

interface __FIMapView_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIMapView_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING_HSTRING_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMap_2_HSTRING_HSTRING __FIMap_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMap_2_HSTRING_HSTRING;

typedef struct __FIMap_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMap_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMap_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMap_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMap_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMap_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMap_2_HSTRING_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIMap_2_HSTRING_HSTRING* This,
        __FIMapView_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* Insert)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Remove)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIMap_2_HSTRING_HSTRING* This);

    END_INTERFACE
} __FIMap_2_HSTRING_HSTRINGVtbl;

interface __FIMap_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIMap_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMap_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMap_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMap_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMap_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMap_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMap_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMap_2_HSTRING_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMap_2_HSTRING_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMap_2_HSTRING_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMap_2_HSTRING_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIMap_2_HSTRING_HSTRING_Insert(This, key, value, result) \
    ((This)->lpVtbl->Insert(This, key, value, result))

#define __FIMap_2_HSTRING_HSTRING_Remove(This, key) \
    ((This)->lpVtbl->Remove(This, key))

#define __FIMap_2_HSTRING_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#endif /* COBJMACROS */

#endif // ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* sender,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

typedef struct __x_ABI_CWindows_CFoundation_CDateTime __x_ABI_CWindows_CFoundation_CDateTime;

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIAsyncAction __x_ABI_CWindows_CFoundation_CIAsyncAction;

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationPriority __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationPriority;

typedef enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationSetting __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationSetting;

/*
 *
 * Struct Microsoft.Windows.AppNotifications.AppNotificationPriority
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationPriority
{
    AppNotificationPriority_Default = 0,
    AppNotificationPriority_High = 1,
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.AppNotificationProgressResult
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationProgressResult
{
    AppNotificationProgressResult_Succeeded = 0,
    AppNotificationProgressResult_AppNotificationNotFound = 1,
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
    AppNotificationProgressResult_Unsupported = 2,
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AppNotifications.AppNotificationSetting
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationSetting
{
    AppNotificationSetting_Enabled = 0,
    AppNotificationSetting_DisabledForApplication = 1,
    AppNotificationSetting_DisabledForUser = 2,
    AppNotificationSetting_DisabledByGroupPolicy = 3,
    AppNotificationSetting_DisabledByManifest = 4,
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
    AppNotificationSetting_Unsupported = 5,
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
};
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotification
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotification
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotification[] = L"Microsoft.Windows.AppNotifications.IAppNotification";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Tag)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Tag)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Group)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Group)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* get_Payload)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData** value);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* value);
    HRESULT (STDMETHODCALLTYPE* get_Expiration)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime* value);
    HRESULT (STDMETHODCALLTYPE* put_Expiration)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime value);
    HRESULT (STDMETHODCALLTYPE* get_ExpiresOnReboot)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ExpiresOnReboot)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_Priority)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationPriority* value);
    HRESULT (STDMETHODCALLTYPE* put_Priority)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationPriority value);
    HRESULT (STDMETHODCALLTYPE* get_SuppressDisplay)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_SuppressDisplay)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Tag(This, value) \
    ((This)->lpVtbl->get_Tag(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_Tag(This, value) \
    ((This)->lpVtbl->put_Tag(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Group(This, value) \
    ((This)->lpVtbl->get_Group(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_Group(This, value) \
    ((This)->lpVtbl->put_Group(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Payload(This, value) \
    ((This)->lpVtbl->get_Payload(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Progress(This, value) \
    ((This)->lpVtbl->get_Progress(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_Progress(This, value) \
    ((This)->lpVtbl->put_Progress(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Expiration(This, value) \
    ((This)->lpVtbl->get_Expiration(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_Expiration(This, value) \
    ((This)->lpVtbl->put_Expiration(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_ExpiresOnReboot(This, value) \
    ((This)->lpVtbl->get_ExpiresOnReboot(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_ExpiresOnReboot(This, value) \
    ((This)->lpVtbl->put_ExpiresOnReboot(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_Priority(This, value) \
    ((This)->lpVtbl->get_Priority(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_Priority(This, value) \
    ((This)->lpVtbl->put_Priority(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_get_SuppressDisplay(This, value) \
    ((This)->lpVtbl->get_SuppressDisplay(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_put_SuppressDisplay(This, value) \
    ((This)->lpVtbl->put_SuppressDisplay(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationActivatedEventArgs[] = L"Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Argument)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_UserInput)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_get_Argument(This, value) \
    ((This)->lpVtbl->get_Argument(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_get_UserInput(This, value) \
    ((This)->lpVtbl->get_UserInput(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs2
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 3.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x30000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationActivatedEventArgs2[] = L"Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Arguments)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_get_Arguments(This, value) \
    ((This)->lpVtbl->get_Arguments(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationActivatedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x30000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotification
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationFactory[] = L"Microsoft.Windows.AppNotifications.IAppNotificationFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory* This,
        HSTRING payload,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_CreateInstance(This, payload, value) \
    ((This)->lpVtbl->CreateInstance(This, payload, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManager
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManager[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Register)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* Unregister)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* UnregisterAll)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* add_NotificationInvoked)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CAppNotifications__CAppNotificationManager_Microsoft__CWindows__CAppNotifications__CAppNotificationActivatedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_NotificationInvoked)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* Show)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotification* notification);
    HRESULT (STDMETHODCALLTYPE* UpdateAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* data,
        HSTRING tag,
        HSTRING group,
        __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult** operation);
    HRESULT (STDMETHODCALLTYPE* UpdateAsync2)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* data,
        HSTRING tag,
        __FIAsyncOperation_1_Microsoft__CWindows__CAppNotifications__CAppNotificationProgressResult** operation);
    HRESULT (STDMETHODCALLTYPE* get_Setting)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppNotifications_CAppNotificationSetting* value);
    HRESULT (STDMETHODCALLTYPE* RemoveByIdAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        UINT32 notificationId,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* RemoveByTagAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        HSTRING tag,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* RemoveByTagAndGroupAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        HSTRING tag,
        HSTRING group,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* RemoveByGroupAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        HSTRING group,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* RemoveAllAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* GetAllAsync)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager* This,
        __FIAsyncOperation_1___FIVector_1_Microsoft__CWindows__CAppNotifications__CAppNotification** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_Register(This) \
    ((This)->lpVtbl->Register(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_Unregister(This) \
    ((This)->lpVtbl->Unregister(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_UnregisterAll(This) \
    ((This)->lpVtbl->UnregisterAll(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_add_NotificationInvoked(This, handler, token) \
    ((This)->lpVtbl->add_NotificationInvoked(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_remove_NotificationInvoked(This, token) \
    ((This)->lpVtbl->remove_NotificationInvoked(This, token))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_Show(This, notification) \
    ((This)->lpVtbl->Show(This, notification))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_UpdateAsync(This, data, tag, group, operation) \
    ((This)->lpVtbl->UpdateAsync(This, data, tag, group, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_UpdateAsync2(This, data, tag, operation) \
    ((This)->lpVtbl->UpdateAsync2(This, data, tag, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_get_Setting(This, value) \
    ((This)->lpVtbl->get_Setting(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_RemoveByIdAsync(This, notificationId, operation) \
    ((This)->lpVtbl->RemoveByIdAsync(This, notificationId, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_RemoveByTagAsync(This, tag, operation) \
    ((This)->lpVtbl->RemoveByTagAsync(This, tag, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_RemoveByTagAndGroupAsync(This, tag, group, operation) \
    ((This)->lpVtbl->RemoveByTagAndGroupAsync(This, tag, group, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_RemoveByGroupAsync(This, group, operation) \
    ((This)->lpVtbl->RemoveByGroupAsync(This, group, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_RemoveAllAsync(This, operation) \
    ((This)->lpVtbl->RemoveAllAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_GetAllAsync(This, operation) \
    ((This)->lpVtbl->GetAllAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManager2
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManager2[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManager2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Register)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2* This,
        HSTRING displayName,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* iconUri);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_Register(This, displayName, iconUri) \
    ((This)->lpVtbl->Register(This, displayName, iconUri))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManagerStatics[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Default)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManager** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_get_Default(This, value) \
    ((This)->lpVtbl->get_Default(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics2
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationManagerStatics2[] = L"Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsSupported)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_IsSupported(This, result) \
    ((This)->lpVtbl->IsSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationProgressData
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationProgressData
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationProgressData[] = L"Microsoft.Windows.AppNotifications.IAppNotificationProgressData";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SequenceNumber)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* put_SequenceNumber)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        UINT32 value);
    HRESULT (STDMETHODCALLTYPE* get_Title)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Title)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* put_Value)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* get_ValueStringOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_ValueStringOverride)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Status)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_get_SequenceNumber(This, value) \
    ((This)->lpVtbl->get_SequenceNumber(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_put_SequenceNumber(This, value) \
    ((This)->lpVtbl->put_SequenceNumber(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_get_Title(This, value) \
    ((This)->lpVtbl->get_Title(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_put_Title(This, value) \
    ((This)->lpVtbl->put_Title(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_get_Value(This, value) \
    ((This)->lpVtbl->get_Value(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_put_Value(This, value) \
    ((This)->lpVtbl->put_Value(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_get_ValueStringOverride(This, value) \
    ((This)->lpVtbl->get_ValueStringOverride(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_put_ValueStringOverride(This, value) \
    ((This)->lpVtbl->put_ValueStringOverride(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_put_Status(This, value) \
    ((This)->lpVtbl->put_Status(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppNotifications.IAppNotificationProgressDataFactory
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppNotifications.AppNotificationProgressData
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppNotifications_IAppNotificationProgressDataFactory[] = L"Microsoft.Windows.AppNotifications.IAppNotificationProgressDataFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory* This,
        UINT32 sequenceNumber,
        __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressData** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_CreateInstance(This, sequenceNumber, value) \
    ((This)->lpVtbl->CreateInstance(This, sequenceNumber, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppNotifications_CIAppNotificationProgressDataFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotification
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AppNotifications.IAppNotificationFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotification ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotification_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotification_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotification[] = L"Microsoft.Windows.AppNotifications.AppNotification";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs ** Default Interface **
 *    Microsoft.Windows.AppNotifications.IAppNotificationActivatedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationActivatedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationActivatedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotificationActivatedEventArgs[] = L"Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotificationManager
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *   Static Methods exist on the Microsoft.Windows.AppNotifications.IAppNotificationManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotificationManager ** Default Interface **
 *    Microsoft.Windows.AppNotifications.IAppNotificationManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotificationManager[] = L"Microsoft.Windows.AppNotifications.AppNotificationManager";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppNotifications.AppNotificationProgressData
 *
 * Introduced to Microsoft.Windows.AppNotifications.AppNotificationsContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AppNotifications.IAppNotificationProgressDataFactory interface starting with version 1.0 of the Microsoft.Windows.AppNotifications.AppNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppNotifications.IAppNotificationProgressData ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationProgressData_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppNotifications_AppNotificationProgressData_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppNotifications_AppNotificationProgressData[] = L"Microsoft.Windows.AppNotifications.AppNotificationProgressData";
#endif
#endif // MICROSOFT_WINDOWS_APPNOTIFICATIONS_APPNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eappnotifications_p_h__

#endif // __microsoft2Ewindows2Eappnotifications_h__
