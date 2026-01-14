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
#ifndef __microsoft2Eui2Edispatching_h__
#define __microsoft2Eui2Edispatching_h__
#ifndef __microsoft2Eui2Edispatching_p_h__
#define __microsoft2Eui2Edispatching_p_h__


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

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueHandler;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler ABI::Microsoft::UI::Dispatching::IDispatcherQueueHandler

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherExitDeferral;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral ABI::Microsoft::UI::Dispatching::IDispatcherExitDeferral

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_FWD_DEFINED__

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

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueue2;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2 ABI::Microsoft::UI::Dispatching::IDispatcherQueue2

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueue3;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3 ABI::Microsoft::UI::Dispatching::IDispatcherQueue3

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueController;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController ABI::Microsoft::UI::Dispatching::IDispatcherQueueController

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueController2;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2 ABI::Microsoft::UI::Dispatching::IDispatcherQueueController2

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueControllerStatics;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics ABI::Microsoft::UI::Dispatching::IDispatcherQueueControllerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueShutdownStartingEventArgs;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs ABI::Microsoft::UI::Dispatching::IDispatcherQueueShutdownStartingEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueStatics;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics ABI::Microsoft::UI::Dispatching::IDispatcherQueueStatics

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueueTimer;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer ABI::Microsoft::UI::Dispatching::IDispatcherQueueTimer

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherQueue;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherQueueShutdownStartingEventArgs;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ecd63a61-4dbf-57bc-880c-a255dfe352c3"))
ITypedEventHandler<ABI::Microsoft::UI::Dispatching::DispatcherQueue*, ABI::Microsoft::UI::Dispatching::DispatcherQueueShutdownStartingEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Dispatching::DispatcherQueue*, ABI::Microsoft::UI::Dispatching::IDispatcherQueue*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Dispatching::DispatcherQueueShutdownStartingEventArgs*, ABI::Microsoft::UI::Dispatching::IDispatcherQueueShutdownStartingEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Dispatching.DispatcherQueue, Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Dispatching::DispatcherQueue*, ABI::Microsoft::UI::Dispatching::DispatcherQueueShutdownStartingEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("3bdaf5dd-3da4-5b44-adb3-6990540afac6"))
ITypedEventHandler<ABI::Microsoft::UI::Dispatching::DispatcherQueue*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Dispatching::DispatcherQueue*, ABI::Microsoft::UI::Dispatching::IDispatcherQueue*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Dispatching.DispatcherQueue, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Dispatching::DispatcherQueue*, IInspectable*> __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherQueueTimer;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("2182a2ac-7545-566a-984f-b10f07bab089"))
ITypedEventHandler<ABI::Microsoft::UI::Dispatching::DispatcherQueueTimer*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Dispatching::DispatcherQueueTimer*, ABI::Microsoft::UI::Dispatching::IDispatcherQueueTimer*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Dispatching.DispatcherQueueTimer, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Dispatching::DispatcherQueueTimer*, IInspectable*> __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Windows {
        namespace Foundation {
            class Deferral;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IDeferral;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIDeferral ABI::Windows::Foundation::IDeferral

#endif // ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__

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
            typedef struct TimeSpan TimeSpan;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                typedef enum DispatcherQueuePriority : int DispatcherQueuePriority;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                typedef enum DispatcherRunOptions : unsigned int DispatcherRunOptions;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherExitDeferral;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherQueueController;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Dispatching.DispatcherQueuePriority
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                enum DispatcherQueuePriority : int
                {
                    DispatcherQueuePriority_Low = -10,
                    DispatcherQueuePriority_Normal = 0,
                    DispatcherQueuePriority_High = 10,
                };
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Dispatching.DispatcherRunOptions
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                enum DispatcherRunOptions : unsigned int
                {
                    DispatcherRunOptions_None = 0,
                    DispatcherRunOptions_ContinueOnQuit = 0x1,
                    DispatcherRunOptions_QuitOnlyLocalLoop = 0x2,
                };

                DEFINE_ENUM_FLAG_OPERATORS(DispatcherRunOptions)
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Delegate Microsoft.UI.Dispatching.DispatcherQueueHandler
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_INTERFACE_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("2e0872a9-4e29-5f14-b688-fb96d5f9d5f8")
                IDispatcherQueueHandler : public IUnknown
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Invoke(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueHandler = _uuidof(IDispatcherQueueHandler);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherExitDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherExitDeferral
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherExitDeferral[] = L"Microsoft.UI.Dispatching.IDispatcherExitDeferral";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("910b5aac-3310-563e-8418-f3005579729e")
                IDispatcherExitDeferral : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Complete(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherExitDeferral = _uuidof(IDispatcherExitDeferral);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueue[] = L"Microsoft.UI.Dispatching.IDispatcherQueue";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("f6ebf8fa-be1c-5bf6-a467-73da28738ae8")
                IDispatcherQueue : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateTimer(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueueTimer** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE TryEnqueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueueHandler* callback,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE TryEnqueueWithPriority(
                        ABI::Microsoft::UI::Dispatching::DispatcherQueuePriority priority,
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueueHandler* callback,
                        boolean* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_ShutdownStarting(
                        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_ShutdownStarting(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_ShutdownCompleted(
                        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_ShutdownCompleted(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueue = _uuidof(IDispatcherQueue);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueue2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueue2[] = L"Microsoft.UI.Dispatching.IDispatcherQueue2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("0cf48751-f1ac-59b8-ba52-6ce7a1444d6f")
                IDispatcherQueue2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_HasThreadAccess(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueue2 = _uuidof(IDispatcherQueue2);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueue3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueue3[] = L"Microsoft.UI.Dispatching.IDispatcherQueue3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("14a7a175-5c27-5a35-b079-21960cf764a8")
                IDispatcherQueue3 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE EnqueueEventLoopExit(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE EnsureSystemDispatcherQueue(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RunEventLoop(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RunEventLoopWithOptions(
                        ABI::Microsoft::UI::Dispatching::DispatcherRunOptions options,
                        ABI::Microsoft::UI::Dispatching::IDispatcherExitDeferral* deferral
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_FrameworkShutdownStarting(
                        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_FrameworkShutdownStarting(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_FrameworkShutdownCompleted(
                        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_FrameworkShutdownCompleted(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueue3 = _uuidof(IDispatcherQueue3);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueController[] = L"Microsoft.UI.Dispatching.IDispatcherQueueController";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("bce8178d-2183-584c-9e5b-f9366f6ae484")
                IDispatcherQueueController : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ShutdownQueueAsync(
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueController = _uuidof(IDispatcherQueueController);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueController2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueController2[] = L"Microsoft.UI.Dispatching.IDispatcherQueueController2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("4c68ee2a-1cb1-5591-a3a2-9b590b8f8b9a")
                IDispatcherQueueController2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE ShutdownQueue(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueController2 = _uuidof(IDispatcherQueueController2);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueControllerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueControllerStatics[] = L"Microsoft.UI.Dispatching.IDispatcherQueueControllerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("f18d6145-722b-593d-bcf2-a61e713f0037")
                IDispatcherQueueControllerStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateOnDedicatedThread(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueueController** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateOnCurrentThread(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueueController** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueControllerStatics = _uuidof(IDispatcherQueueControllerStatics);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueShutdownStartingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueShutdownStartingEventArgs[] = L"Microsoft.UI.Dispatching.IDispatcherQueueShutdownStartingEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("32519be5-072b-5660-a70e-8835c9b8157d")
                IDispatcherQueueShutdownStartingEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetDeferral(
                        ABI::Windows::Foundation::IDeferral** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueShutdownStartingEventArgs = _uuidof(IDispatcherQueueShutdownStartingEventArgs);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueStatics[] = L"Microsoft.UI.Dispatching.IDispatcherQueueStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("cd3382ea-a455-5124-b63a-ca40d34ca23c")
                IDispatcherQueueStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetForCurrentThread(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueStatics = _uuidof(IDispatcherQueueStatics);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueTimer
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueTimer
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueTimer[] = L"Microsoft.UI.Dispatching.IDispatcherQueueTimer";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                MIDL_INTERFACE("ad4d63fd-88fe-541f-ac11-bf2dc1ed2ce5")
                IDispatcherQueueTimer : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Interval(
                        ABI::Windows::Foundation::TimeSpan* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Interval(
                        ABI::Windows::Foundation::TimeSpan value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsRunning(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsRepeating(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsRepeating(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Start(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Stop(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Tick(
                        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Tick(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDispatcherQueueTimer = _uuidof(IDispatcherQueueTimer);
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherExitDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherExitDeferral ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherExitDeferral_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherExitDeferral_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherExitDeferral[] = L"Microsoft.UI.Dispatching.DispatcherExitDeferral";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Dispatching.IDispatcherQueueStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueue ** Default Interface **
 *    Microsoft.UI.Dispatching.IDispatcherQueue2
 *    Microsoft.UI.Dispatching.IDispatcherQueue3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueue_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueue_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueue[] = L"Microsoft.UI.Dispatching.DispatcherQueue";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueueController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Dispatching.IDispatcherQueueControllerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueueController ** Default Interface **
 *    Microsoft.UI.Dispatching.IDispatcherQueueController2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueueController[] = L"Microsoft.UI.Dispatching.DispatcherQueueController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueueShutdownStartingEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueShutdownStartingEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueShutdownStartingEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueueShutdownStartingEventArgs[] = L"Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueueTimer
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueueTimer ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueTimer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueTimer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueueTimer[] = L"Microsoft.UI.Dispatching.DispatcherQueueTimer";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2 __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3 __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2 __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* sender,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIDeferral __x_ABI_CWindows_CFoundation_CIDeferral;

#endif // ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIAsyncAction __x_ABI_CWindows_CFoundation_CIAsyncAction;

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CTimeSpan __x_ABI_CWindows_CFoundation_CTimeSpan;

typedef enum __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherQueuePriority __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherQueuePriority;

typedef enum __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherRunOptions __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherRunOptions;

/*
 *
 * Struct Microsoft.UI.Dispatching.DispatcherQueuePriority
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherQueuePriority
{
    DispatcherQueuePriority_Low = -10,
    DispatcherQueuePriority_Normal = 0,
    DispatcherQueuePriority_High = 10,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Dispatching.DispatcherRunOptions
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherRunOptions
{
    DispatcherRunOptions_None = 0,
    DispatcherRunOptions_ContinueOnQuit = 0x1,
    DispatcherRunOptions_QuitOnlyLocalLoop = 0x2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Delegate Microsoft.UI.Dispatching.DispatcherQueueHandler
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_INTERFACE_DEFINED__
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandlerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandlerVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_Invoke(This) \
    ((This)->lpVtbl->Invoke(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherExitDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherExitDeferral
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherExitDeferral[] = L"Microsoft.UI.Dispatching.IDispatcherExitDeferral";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferralVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Complete)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferralVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferralVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_Complete(This) \
    ((This)->lpVtbl->Complete(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueue[] = L"Microsoft.UI.Dispatching.IDispatcherQueue";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateTimer)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer** result);
    HRESULT (STDMETHODCALLTYPE* TryEnqueue)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler* callback,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* TryEnqueueWithPriority)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        enum __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherQueuePriority priority,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueHandler* callback,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* add_ShutdownStarting)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ShutdownStarting)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_ShutdownCompleted)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ShutdownCompleted)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_CreateTimer(This, result) \
    ((This)->lpVtbl->CreateTimer(This, result))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_TryEnqueue(This, callback, result) \
    ((This)->lpVtbl->TryEnqueue(This, callback, result))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_TryEnqueueWithPriority(This, priority, callback, result) \
    ((This)->lpVtbl->TryEnqueueWithPriority(This, priority, callback, result))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_add_ShutdownStarting(This, handler, token) \
    ((This)->lpVtbl->add_ShutdownStarting(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_remove_ShutdownStarting(This, token) \
    ((This)->lpVtbl->remove_ShutdownStarting(This, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_add_ShutdownCompleted(This, handler, token) \
    ((This)->lpVtbl->add_ShutdownCompleted(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_remove_ShutdownCompleted(This, token) \
    ((This)->lpVtbl->remove_ShutdownCompleted(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueue2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueue2[] = L"Microsoft.UI.Dispatching.IDispatcherQueue2";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_HasThreadAccess)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_get_HasThreadAccess(This, value) \
    ((This)->lpVtbl->get_HasThreadAccess(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueue3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueue3[] = L"Microsoft.UI.Dispatching.IDispatcherQueue3";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* EnqueueEventLoopExit)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This);
    HRESULT (STDMETHODCALLTYPE* EnsureSystemDispatcherQueue)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This);
    HRESULT (STDMETHODCALLTYPE* RunEventLoop)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This);
    HRESULT (STDMETHODCALLTYPE* RunEventLoopWithOptions)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        enum __x_ABI_CMicrosoft_CUI_CDispatching_CDispatcherRunOptions options,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherExitDeferral* deferral);
    HRESULT (STDMETHODCALLTYPE* add_FrameworkShutdownStarting)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_Microsoft__CUI__CDispatching__CDispatcherQueueShutdownStartingEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_FrameworkShutdownStarting)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_FrameworkShutdownCompleted)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueue_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_FrameworkShutdownCompleted)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_EnqueueEventLoopExit(This) \
    ((This)->lpVtbl->EnqueueEventLoopExit(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_EnsureSystemDispatcherQueue(This) \
    ((This)->lpVtbl->EnsureSystemDispatcherQueue(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_RunEventLoop(This) \
    ((This)->lpVtbl->RunEventLoop(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_RunEventLoopWithOptions(This, options, deferral) \
    ((This)->lpVtbl->RunEventLoopWithOptions(This, options, deferral))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_add_FrameworkShutdownStarting(This, handler, token) \
    ((This)->lpVtbl->add_FrameworkShutdownStarting(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_remove_FrameworkShutdownStarting(This, token) \
    ((This)->lpVtbl->remove_FrameworkShutdownStarting(This, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_add_FrameworkShutdownCompleted(This, handler, token) \
    ((This)->lpVtbl->add_FrameworkShutdownCompleted(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_remove_FrameworkShutdownCompleted(This, token) \
    ((This)->lpVtbl->remove_FrameworkShutdownCompleted(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueController[] = L"Microsoft.UI.Dispatching.IDispatcherQueueController";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* ShutdownQueueAsync)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController* This,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_ShutdownQueueAsync(This, operation) \
    ((This)->lpVtbl->ShutdownQueueAsync(This, operation))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueController2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueController2[] = L"Microsoft.UI.Dispatching.IDispatcherQueueController2";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ShutdownQueue)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_ShutdownQueue(This) \
    ((This)->lpVtbl->ShutdownQueue(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueControllerStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueControllerStatics[] = L"Microsoft.UI.Dispatching.IDispatcherQueueControllerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateOnDedicatedThread)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController** result);
    HRESULT (STDMETHODCALLTYPE* CreateOnCurrentThread)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueController** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_CreateOnDedicatedThread(This, result) \
    ((This)->lpVtbl->CreateOnDedicatedThread(This, result))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_CreateOnCurrentThread(This, result) \
    ((This)->lpVtbl->CreateOnCurrentThread(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueControllerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueShutdownStartingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueShutdownStartingEventArgs[] = L"Microsoft.UI.Dispatching.IDispatcherQueueShutdownStartingEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDeferral)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs* This,
        __x_ABI_CWindows_CFoundation_CIDeferral** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_GetDeferral(This, result) \
    ((This)->lpVtbl->GetDeferral(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueShutdownStartingEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueue
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueStatics[] = L"Microsoft.UI.Dispatching.IDispatcherQueueStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetForCurrentThread)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_GetForCurrentThread(This, result) \
    ((This)->lpVtbl->GetForCurrentThread(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Dispatching.IDispatcherQueueTimer
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Dispatching.DispatcherQueueTimer
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Dispatching_IDispatcherQueueTimer[] = L"Microsoft.UI.Dispatching.IDispatcherQueueTimer";
typedef struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Interval)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan* value);
    HRESULT (STDMETHODCALLTYPE* put_Interval)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan value);
    HRESULT (STDMETHODCALLTYPE* get_IsRunning)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsRepeating)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsRepeating)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* Start)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This);
    HRESULT (STDMETHODCALLTYPE* Stop)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This);
    HRESULT (STDMETHODCALLTYPE* add_Tick)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        __FITypedEventHandler_2_Microsoft__CUI__CDispatching__CDispatcherQueueTimer_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Tick)(__x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimerVtbl;

interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_get_Interval(This, value) \
    ((This)->lpVtbl->get_Interval(This, value))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_put_Interval(This, value) \
    ((This)->lpVtbl->put_Interval(This, value))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_get_IsRunning(This, value) \
    ((This)->lpVtbl->get_IsRunning(This, value))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_get_IsRepeating(This, value) \
    ((This)->lpVtbl->get_IsRepeating(This, value))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_put_IsRepeating(This, value) \
    ((This)->lpVtbl->put_IsRepeating(This, value))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_Start(This) \
    ((This)->lpVtbl->Start(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_Stop(This) \
    ((This)->lpVtbl->Stop(This))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_add_Tick(This, handler, token) \
    ((This)->lpVtbl->add_Tick(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_remove_Tick(This, token) \
    ((This)->lpVtbl->remove_Tick(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueueTimer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherExitDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherExitDeferral ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherExitDeferral_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherExitDeferral_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherExitDeferral[] = L"Microsoft.UI.Dispatching.DispatcherExitDeferral";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueue
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Dispatching.IDispatcherQueueStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueue ** Default Interface **
 *    Microsoft.UI.Dispatching.IDispatcherQueue2
 *    Microsoft.UI.Dispatching.IDispatcherQueue3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueue_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueue_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueue[] = L"Microsoft.UI.Dispatching.DispatcherQueue";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueueController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Dispatching.IDispatcherQueueControllerStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueueController ** Default Interface **
 *    Microsoft.UI.Dispatching.IDispatcherQueueController2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueueController[] = L"Microsoft.UI.Dispatching.DispatcherQueueController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueueShutdownStartingEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueShutdownStartingEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueShutdownStartingEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueueShutdownStartingEventArgs[] = L"Microsoft.UI.Dispatching.DispatcherQueueShutdownStartingEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Dispatching.DispatcherQueueTimer
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Dispatching.IDispatcherQueueTimer ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueTimer_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Dispatching_DispatcherQueueTimer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Dispatching_DispatcherQueueTimer[] = L"Microsoft.UI.Dispatching.DispatcherQueueTimer";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Edispatching_p_h__

#endif // __microsoft2Eui2Edispatching_h__
