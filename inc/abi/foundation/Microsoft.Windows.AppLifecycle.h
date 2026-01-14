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
#ifndef __microsoft2Ewindows2Eapplifecycle_h__
#define __microsoft2Ewindows2Eapplifecycle_h__
#ifndef __microsoft2Ewindows2Eapplifecycle_p_h__
#define __microsoft2Ewindows2Eapplifecycle_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION)

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
#include "Windows.ApplicationModel.Core.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                interface IActivationRegistrationManagerStatics;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics ABI::Microsoft::Windows::AppLifecycle::IActivationRegistrationManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                interface IAppActivationArguments;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments ABI::Microsoft::Windows::AppLifecycle::IAppActivationArguments

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                interface IAppInstance;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance ABI::Microsoft::Windows::AppLifecycle::IAppInstance

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                interface IAppInstanceStatics;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics ABI::Microsoft::Windows::AppLifecycle::IAppInstanceStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                interface IAppInstanceStatics2;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2 ABI::Microsoft::Windows::AppLifecycle::IAppInstanceStatics2

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                class AppInstance;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("58c4b850-cfd3-54c7-9568-cf76a017afae"))
IIterator<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppLifecycle::AppInstance*, ABI::Microsoft::Windows::AppLifecycle::IAppInstance*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.AppLifecycle.AppInstance>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t;
#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE */

#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("46dd4ef2-c3a5-5a9f-b72d-8f0836be424a"))
IIterable<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppLifecycle::AppInstance*, ABI::Microsoft::Windows::AppLifecycle::IAppInstance*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.AppLifecycle.AppInstance>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t;
#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE */

#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("1520072b-d6f2-5a95-988d-e6c4a6eb66a4"))
IVectorView<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppLifecycle::AppInstance*, ABI::Microsoft::Windows::AppLifecycle::IAppInstance*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.AppLifecycle.AppInstance>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t;
#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE */

#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#define DEF___FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f37e92bb-b953-5d1e-ae0b-15e49c194c98"))
IVector<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppLifecycle::AppInstance*, ABI::Microsoft::Windows::AppLifecycle::IAppInstance*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.Windows.AppLifecycle.AppInstance>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::Windows::AppLifecycle::AppInstance*> __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t;
#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_USE */

#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                class AppActivationArguments;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_USE
#define DEF___FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("37d74b33-9510-5748-b33d-4676ee2b48a7"))
IEventHandler<ABI::Microsoft::Windows::AppLifecycle::AppActivationArguments*> : IEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::AppLifecycle::AppActivationArguments*, ABI::Microsoft::Windows::AppLifecycle::IAppActivationArguments*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Microsoft.Windows.AppLifecycle.AppActivationArguments>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<ABI::Microsoft::Windows::AppLifecycle::AppActivationArguments*> __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_t;
#define __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments ABI::Windows::Foundation::__FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_USE */

#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Core {
                typedef enum AppRestartFailureReason : int AppRestartFailureReason;
            } /* Core */
        } /* ApplicationModel */
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
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                typedef enum ExtendedActivationKind : int ExtendedActivationKind;
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AppLifecycle.ExtendedActivationKind
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                enum ExtendedActivationKind : int
                {
                    ExtendedActivationKind_Launch = 0,
                    ExtendedActivationKind_Search = 1,
                    ExtendedActivationKind_ShareTarget = 2,
                    ExtendedActivationKind_File = 3,
                    ExtendedActivationKind_Protocol = 4,
                    ExtendedActivationKind_FileOpenPicker = 5,
                    ExtendedActivationKind_FileSavePicker = 6,
                    ExtendedActivationKind_CachedFileUpdater = 7,
                    ExtendedActivationKind_ContactPicker = 8,
                    ExtendedActivationKind_Device = 9,
                    ExtendedActivationKind_PrintTaskSettings = 10,
                    ExtendedActivationKind_CameraSettings = 11,
                    ExtendedActivationKind_RestrictedLaunch = 12,
                    ExtendedActivationKind_AppointmentsProvider = 13,
                    ExtendedActivationKind_Contact = 14,
                    ExtendedActivationKind_LockScreenCall = 15,
                    ExtendedActivationKind_VoiceCommand = 16,
                    ExtendedActivationKind_LockScreen = 17,
                    ExtendedActivationKind_PickerReturned = 1000,
                    ExtendedActivationKind_WalletAction = 1001,
                    ExtendedActivationKind_PickFileContinuation = 1002,
                    ExtendedActivationKind_PickSaveFileContinuation = 1003,
                    ExtendedActivationKind_PickFolderContinuation = 1004,
                    ExtendedActivationKind_WebAuthenticationBrokerContinuation = 1005,
                    ExtendedActivationKind_WebAccountProvider = 1006,
                    ExtendedActivationKind_ComponentUI = 1007,
                    ExtendedActivationKind_ProtocolForResults = 1009,
                    ExtendedActivationKind_ToastNotification = 1010,
                    ExtendedActivationKind_Print3DWorkflow = 1011,
                    ExtendedActivationKind_DialReceiver = 1012,
                    ExtendedActivationKind_DevicePairing = 1013,
                    ExtendedActivationKind_UserDataAccountsProvider = 1014,
                    ExtendedActivationKind_FilePickerExperience = 1015,
                    ExtendedActivationKind_LockScreenComponent = 1016,
                    ExtendedActivationKind_ContactPanel = 1017,
                    ExtendedActivationKind_PrintWorkflowForegroundTask = 1018,
                    ExtendedActivationKind_GameUIProvider = 1019,
                    ExtendedActivationKind_StartupTask = 1020,
                    ExtendedActivationKind_CommandLineLaunch = 1021,
                    ExtendedActivationKind_BarcodeScannerProvider = 1022,
                    ExtendedActivationKind_PrintSupportJobUI = 1023,
                    ExtendedActivationKind_PrintSupportSettingsUI = 1024,
                    ExtendedActivationKind_PhoneCallActivation = 1025,
                    ExtendedActivationKind_VpnForeground = 1026,
                    ExtendedActivationKind_Push = 5000,
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000
                    ExtendedActivationKind_AppNotification = 5001,
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000
                };
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IActivationRegistrationManagerStatics
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.ActivationRegistrationManager
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IActivationRegistrationManagerStatics[] = L"Microsoft.Windows.AppLifecycle.IActivationRegistrationManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                MIDL_INTERFACE("5ac4e92e-017b-5d68-8198-f68636ab99d3")
                IActivationRegistrationManagerStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE RegisterForFileTypeActivation(
                        UINT32 supportedFileTypesLength,
                        HSTRING* supportedFileTypes,
                        HSTRING logo,
                        HSTRING displayName,
                        UINT32 supportedVerbsLength,
                        HSTRING* supportedVerbs,
                        HSTRING exePath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RegisterForProtocolActivation(
                        HSTRING scheme,
                        HSTRING logo,
                        HSTRING displayName,
                        HSTRING exePath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RegisterForStartupActivation(
                        HSTRING taskId,
                        HSTRING exePath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UnregisterForFileTypeActivation(
                        UINT32 fileTypesLength,
                        HSTRING* fileTypes,
                        HSTRING exePath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UnregisterForProtocolActivation(
                        HSTRING scheme,
                        HSTRING exePath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE UnregisterForStartupActivation(
                        HSTRING taskId
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IActivationRegistrationManagerStatics = _uuidof(IActivationRegistrationManagerStatics);
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppActivationArguments
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppActivationArguments
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppActivationArguments[] = L"Microsoft.Windows.AppLifecycle.IAppActivationArguments";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                MIDL_INTERFACE("14f99eaf-1580-5062-bdc8-d5d1c31138fb")
                IAppActivationArguments : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Kind(
                        ABI::Microsoft::Windows::AppLifecycle::ExtendedActivationKind* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Data(
                        IInspectable** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppActivationArguments = _uuidof(IAppActivationArguments);
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppInstance
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppInstance
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppInstance[] = L"Microsoft.Windows.AppLifecycle.IAppInstance";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                MIDL_INTERFACE("75766ae4-0239-5a26-b9da-d5bfc75a4866")
                IAppInstance : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE UnregisterKey(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RedirectActivationToAsync(
                        ABI::Microsoft::Windows::AppLifecycle::IAppActivationArguments* args,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetActivatedEventArgs(
                        ABI::Microsoft::Windows::AppLifecycle::IAppActivationArguments** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Activated(
                        __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Activated(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Key(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsCurrent(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessId(
                        UINT32* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppInstance = _uuidof(IAppInstance);
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppInstanceStatics
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppInstance
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppInstanceStatics[] = L"Microsoft.Windows.AppLifecycle.IAppInstanceStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                MIDL_INTERFACE("4f414b25-8330-5a9b-bbc1-8229d479649d")
                IAppInstanceStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetCurrent(
                        ABI::Microsoft::Windows::AppLifecycle::IAppInstance** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetInstances(
                        __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FindOrRegisterForKey(
                        HSTRING key,
                        ABI::Microsoft::Windows::AppLifecycle::IAppInstance** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppInstanceStatics = _uuidof(IAppInstanceStatics);
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppInstanceStatics2
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppInstance
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppInstanceStatics2[] = L"Microsoft.Windows.AppLifecycle.IAppInstanceStatics2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AppLifecycle {
                MIDL_INTERFACE("fe9f1885-7160-5397-ba9b-5890b24fdc04")
                IAppInstanceStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Restart(
                        HSTRING arguments,
                        ABI::Windows::ApplicationModel::Core::AppRestartFailureReason* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppInstanceStatics2 = _uuidof(IAppInstanceStatics2);
            } /* AppLifecycle */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.AppLifecycle.ActivationRegistrationManager
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppLifecycle.IActivationRegistrationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.AppLifecycle.AppLifecycleContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppLifecycle_ActivationRegistrationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppLifecycle_ActivationRegistrationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppLifecycle_ActivationRegistrationManager[] = L"Microsoft.Windows.AppLifecycle.ActivationRegistrationManager";
#endif
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppLifecycle.AppActivationArguments
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppLifecycle.IAppActivationArguments ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppActivationArguments_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppActivationArguments_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppLifecycle_AppActivationArguments[] = L"Microsoft.Windows.AppLifecycle.AppActivationArguments";
#endif
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppLifecycle.AppInstance
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppLifecycle.IAppInstanceStatics interface starting with version 1.0 of the Microsoft.Windows.AppLifecycle.AppLifecycleContract API contract
 *   Static Methods exist on the Microsoft.Windows.AppLifecycle.IAppInstanceStatics2 interface starting with version 2.0 of the Microsoft.Windows.AppLifecycle.AppLifecycleContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppLifecycle.IAppInstance ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppInstance_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppInstance_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppLifecycle_AppInstance[] = L"Microsoft.Windows.AppLifecycle.AppInstance";
#endif
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2 __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2;

#endif // ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

typedef struct __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl;

interface __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

typedef struct __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        __FIIterator_1_Microsoft__CWindows__CAppLifecycle__CAppInstance** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl;

interface __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

typedef struct __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance;

typedef struct __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        __FIVectorView_1_Microsoft__CWindows__CAppLifecycle__CAppInstance** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl;

interface __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance
{
    CONST_VTBL struct __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstanceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments;

typedef struct __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArgumentsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments* This,
        IInspectable* sender,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* args);

    END_INTERFACE
} __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArgumentsVtbl;

interface __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments
{
    CONST_VTBL struct __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArgumentsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

typedef enum __x_ABI_CWindows_CApplicationModel_CCore_CAppRestartFailureReason __x_ABI_CWindows_CApplicationModel_CCore_CAppRestartFailureReason;

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIAsyncAction __x_ABI_CWindows_CFoundation_CIAsyncAction;

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CExtendedActivationKind __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CExtendedActivationKind;

/*
 *
 * Struct Microsoft.Windows.AppLifecycle.ExtendedActivationKind
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CExtendedActivationKind
{
    ExtendedActivationKind_Launch = 0,
    ExtendedActivationKind_Search = 1,
    ExtendedActivationKind_ShareTarget = 2,
    ExtendedActivationKind_File = 3,
    ExtendedActivationKind_Protocol = 4,
    ExtendedActivationKind_FileOpenPicker = 5,
    ExtendedActivationKind_FileSavePicker = 6,
    ExtendedActivationKind_CachedFileUpdater = 7,
    ExtendedActivationKind_ContactPicker = 8,
    ExtendedActivationKind_Device = 9,
    ExtendedActivationKind_PrintTaskSettings = 10,
    ExtendedActivationKind_CameraSettings = 11,
    ExtendedActivationKind_RestrictedLaunch = 12,
    ExtendedActivationKind_AppointmentsProvider = 13,
    ExtendedActivationKind_Contact = 14,
    ExtendedActivationKind_LockScreenCall = 15,
    ExtendedActivationKind_VoiceCommand = 16,
    ExtendedActivationKind_LockScreen = 17,
    ExtendedActivationKind_PickerReturned = 1000,
    ExtendedActivationKind_WalletAction = 1001,
    ExtendedActivationKind_PickFileContinuation = 1002,
    ExtendedActivationKind_PickSaveFileContinuation = 1003,
    ExtendedActivationKind_PickFolderContinuation = 1004,
    ExtendedActivationKind_WebAuthenticationBrokerContinuation = 1005,
    ExtendedActivationKind_WebAccountProvider = 1006,
    ExtendedActivationKind_ComponentUI = 1007,
    ExtendedActivationKind_ProtocolForResults = 1009,
    ExtendedActivationKind_ToastNotification = 1010,
    ExtendedActivationKind_Print3DWorkflow = 1011,
    ExtendedActivationKind_DialReceiver = 1012,
    ExtendedActivationKind_DevicePairing = 1013,
    ExtendedActivationKind_UserDataAccountsProvider = 1014,
    ExtendedActivationKind_FilePickerExperience = 1015,
    ExtendedActivationKind_LockScreenComponent = 1016,
    ExtendedActivationKind_ContactPanel = 1017,
    ExtendedActivationKind_PrintWorkflowForegroundTask = 1018,
    ExtendedActivationKind_GameUIProvider = 1019,
    ExtendedActivationKind_StartupTask = 1020,
    ExtendedActivationKind_CommandLineLaunch = 1021,
    ExtendedActivationKind_BarcodeScannerProvider = 1022,
    ExtendedActivationKind_PrintSupportJobUI = 1023,
    ExtendedActivationKind_PrintSupportSettingsUI = 1024,
    ExtendedActivationKind_PhoneCallActivation = 1025,
    ExtendedActivationKind_VpnForeground = 1026,
    ExtendedActivationKind_Push = 5000,
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000
    ExtendedActivationKind_AppNotification = 5001,
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000
};
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IActivationRegistrationManagerStatics
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.ActivationRegistrationManager
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IActivationRegistrationManagerStatics[] = L"Microsoft.Windows.AppLifecycle.IActivationRegistrationManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RegisterForFileTypeActivation)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        UINT32 supportedFileTypesLength,
        HSTRING* supportedFileTypes,
        HSTRING logo,
        HSTRING displayName,
        UINT32 supportedVerbsLength,
        HSTRING* supportedVerbs,
        HSTRING exePath);
    HRESULT (STDMETHODCALLTYPE* RegisterForProtocolActivation)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        HSTRING scheme,
        HSTRING logo,
        HSTRING displayName,
        HSTRING exePath);
    HRESULT (STDMETHODCALLTYPE* RegisterForStartupActivation)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        HSTRING taskId,
        HSTRING exePath);
    HRESULT (STDMETHODCALLTYPE* UnregisterForFileTypeActivation)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        UINT32 fileTypesLength,
        HSTRING* fileTypes,
        HSTRING exePath);
    HRESULT (STDMETHODCALLTYPE* UnregisterForProtocolActivation)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        HSTRING scheme,
        HSTRING exePath);
    HRESULT (STDMETHODCALLTYPE* UnregisterForStartupActivation)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics* This,
        HSTRING taskId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_RegisterForFileTypeActivation(This, supportedFileTypesLength, supportedFileTypes, logo, displayName, supportedVerbsLength, supportedVerbs, exePath) \
    ((This)->lpVtbl->RegisterForFileTypeActivation(This, supportedFileTypesLength, supportedFileTypes, logo, displayName, supportedVerbsLength, supportedVerbs, exePath))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_RegisterForProtocolActivation(This, scheme, logo, displayName, exePath) \
    ((This)->lpVtbl->RegisterForProtocolActivation(This, scheme, logo, displayName, exePath))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_RegisterForStartupActivation(This, taskId, exePath) \
    ((This)->lpVtbl->RegisterForStartupActivation(This, taskId, exePath))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_UnregisterForFileTypeActivation(This, fileTypesLength, fileTypes, exePath) \
    ((This)->lpVtbl->UnregisterForFileTypeActivation(This, fileTypesLength, fileTypes, exePath))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_UnregisterForProtocolActivation(This, scheme, exePath) \
    ((This)->lpVtbl->UnregisterForProtocolActivation(This, scheme, exePath))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_UnregisterForStartupActivation(This, taskId) \
    ((This)->lpVtbl->UnregisterForStartupActivation(This, taskId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIActivationRegistrationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppActivationArguments
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppActivationArguments
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppActivationArguments[] = L"Microsoft.Windows.AppLifecycle.IAppActivationArguments";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArgumentsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This,
        enum __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CExtendedActivationKind* value);
    HRESULT (STDMETHODCALLTYPE* get_Data)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* This,
        IInspectable** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArgumentsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArgumentsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_get_Data(This, value) \
    ((This)->lpVtbl->get_Data(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppInstance
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppInstance
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppInstance[] = L"Microsoft.Windows.AppLifecycle.IAppInstance";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* UnregisterKey)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This);
    HRESULT (STDMETHODCALLTYPE* RedirectActivationToAsync)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments* args,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* GetActivatedEventArgs)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppActivationArguments** result);
    HRESULT (STDMETHODCALLTYPE* add_Activated)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        __FIEventHandler_1_Microsoft__CWindows__CAppLifecycle__CAppActivationArguments* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Activated)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_IsCurrent)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessId)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance* This,
        UINT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_UnregisterKey(This) \
    ((This)->lpVtbl->UnregisterKey(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_RedirectActivationToAsync(This, args, operation) \
    ((This)->lpVtbl->RedirectActivationToAsync(This, args, operation))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_GetActivatedEventArgs(This, result) \
    ((This)->lpVtbl->GetActivatedEventArgs(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_add_Activated(This, handler, token) \
    ((This)->lpVtbl->add_Activated(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_remove_Activated(This, token) \
    ((This)->lpVtbl->remove_Activated(This, token))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_get_Key(This, value) \
    ((This)->lpVtbl->get_Key(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_get_IsCurrent(This, value) \
    ((This)->lpVtbl->get_IsCurrent(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_get_ProcessId(This, value) \
    ((This)->lpVtbl->get_ProcessId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppInstanceStatics
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppInstance
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppInstanceStatics[] = L"Microsoft.Windows.AppLifecycle.IAppInstanceStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetCurrent)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** result);
    HRESULT (STDMETHODCALLTYPE* GetInstances)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        __FIVector_1_Microsoft__CWindows__CAppLifecycle__CAppInstance** result);
    HRESULT (STDMETHODCALLTYPE* FindOrRegisterForKey)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics* This,
        HSTRING key,
        __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstance** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_GetCurrent(This, result) \
    ((This)->lpVtbl->GetCurrent(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_GetInstances(This, result) \
    ((This)->lpVtbl->GetInstances(This, result))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_FindOrRegisterForKey(This, key, result) \
    ((This)->lpVtbl->FindOrRegisterForKey(This, key, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AppLifecycle.IAppInstanceStatics2
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AppLifecycle.AppInstance
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AppLifecycle_IAppInstanceStatics2[] = L"Microsoft.Windows.AppLifecycle.IAppInstanceStatics2";
typedef struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Restart)(__x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2* This,
        HSTRING arguments,
        enum __x_ABI_CWindows_CApplicationModel_CCore_CAppRestartFailureReason* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_Restart(This, arguments, result) \
    ((This)->lpVtbl->Restart(This, arguments, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAppLifecycle_CIAppInstanceStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.AppLifecycle.ActivationRegistrationManager
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppLifecycle.IActivationRegistrationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.AppLifecycle.AppLifecycleContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppLifecycle_ActivationRegistrationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppLifecycle_ActivationRegistrationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppLifecycle_ActivationRegistrationManager[] = L"Microsoft.Windows.AppLifecycle.ActivationRegistrationManager";
#endif
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppLifecycle.AppActivationArguments
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppLifecycle.IAppActivationArguments ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppActivationArguments_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppActivationArguments_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppLifecycle_AppActivationArguments[] = L"Microsoft.Windows.AppLifecycle.AppActivationArguments";
#endif
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AppLifecycle.AppInstance
 *
 * Introduced to Microsoft.Windows.AppLifecycle.AppLifecycleContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.AppLifecycle.IAppInstanceStatics interface starting with version 1.0 of the Microsoft.Windows.AppLifecycle.AppLifecycleContract API contract
 *   Static Methods exist on the Microsoft.Windows.AppLifecycle.IAppInstanceStatics2 interface starting with version 2.0 of the Microsoft.Windows.AppLifecycle.AppLifecycleContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AppLifecycle.IAppInstance ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppInstance_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AppLifecycle_AppInstance_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AppLifecycle_AppInstance[] = L"Microsoft.Windows.AppLifecycle.AppInstance";
#endif
#endif // MICROSOFT_WINDOWS_APPLIFECYCLE_APPLIFECYCLECONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eapplifecycle_p_h__

#endif // __microsoft2Ewindows2Eapplifecycle_h__
