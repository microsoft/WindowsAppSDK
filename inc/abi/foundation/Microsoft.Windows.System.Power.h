
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
#ifndef __microsoft2Ewindows2Esystem2Epower_h__
#define __microsoft2Ewindows2Esystem2Epower_h__
#ifndef __microsoft2Ewindows2Esystem2Epower_p_h__
#define __microsoft2Ewindows2Esystem2Epower_p_h__


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
#if !defined(MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION)

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

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    interface IPowerManagerStatics;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics ABI::Microsoft::Windows::System::Power::IPowerManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    interface IPowerManagerStatics2;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2 ABI::Microsoft::Windows::System::Power::IPowerManagerStatics2

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum EffectivePowerMode : int EffectivePowerMode;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_USE
#define DEF___FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("c4dc524f-9095-56f2-9acf-e10ffa600fcb"))
IAsyncOperation<enum ABI::Microsoft::Windows::System::Power::EffectivePowerMode> : IAsyncOperation_impl<enum ABI::Microsoft::Windows::System::Power::EffectivePowerMode>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Microsoft.Windows.System.Power.EffectivePowerMode>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<enum ABI::Microsoft::Windows::System::Power::EffectivePowerMode> __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_t;
#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode ABI::Windows::Foundation::__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_USE */

#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_USE
#define DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("897713ea-1f95-5c1b-a24b-9341aabc743a"))
IAsyncOperationCompletedHandler<enum ABI::Microsoft::Windows::System::Power::EffectivePowerMode> : IAsyncOperationCompletedHandler_impl<enum ABI::Microsoft::Windows::System::Power::EffectivePowerMode>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Microsoft.Windows.System.Power.EffectivePowerMode>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<enum ABI::Microsoft::Windows::System::Power::EffectivePowerMode> __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_t;
#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_USE */

#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIEventHandler_1_IInspectable_USE
#define DEF___FIEventHandler_1_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("c50898f6-c536-5f47-8583-8b2c2438a13b"))
IEventHandler<IInspectable*> : IEventHandler_impl<IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.EventHandler`1<Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IEventHandler<IInspectable*> __FIEventHandler_1_IInspectable_t;
#define __FIEventHandler_1_IInspectable ABI::Windows::Foundation::__FIEventHandler_1_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIEventHandler_1_IInspectable_USE */


namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct TimeSpan TimeSpan;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum BatteryStatus : int BatteryStatus;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum DisplayStatus : int DisplayStatus;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum EnergySaverStatus : int EnergySaverStatus;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum PowerSourceKind : int PowerSourceKind;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum PowerSupplyStatus : int PowerSupplyStatus;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum SystemSuspendStatus : int SystemSuspendStatus;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    typedef enum UserPresenceStatus : int UserPresenceStatus;
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.System.Power.BatteryStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum BatteryStatus : int
                    {
                        BatteryStatus_NotPresent = 0,
                        BatteryStatus_Discharging = 1,
                        BatteryStatus_Idle = 2,
                        BatteryStatus_Charging = 3,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.DisplayStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum DisplayStatus : int
                    {
                        DisplayStatus_Off = 0,
                        DisplayStatus_On = 1,
                        DisplayStatus_Dimmed = 2,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.EffectivePowerMode
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum EffectivePowerMode : int
                    {
                        EffectivePowerMode_BatterySaver = 0,
                        EffectivePowerMode_BetterBattery = 1,
                        EffectivePowerMode_Balanced = 2,
                        EffectivePowerMode_HighPerformance = 3,
                        EffectivePowerMode_MaxPerformance = 4,
                        EffectivePowerMode_GameMode = 5,
                        EffectivePowerMode_MixedReality = 6,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.EnergySaverStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum EnergySaverStatus : int
                    {
                        EnergySaverStatus_Uninitialized = 0,
                        EnergySaverStatus_Disabled = 1,
                        EnergySaverStatus_Off = 2,
                        EnergySaverStatus_On = 3,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.PowerSourceKind
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum PowerSourceKind : int
                    {
                        PowerSourceKind_AC = 0,
                        PowerSourceKind_DC = 1,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.PowerSupplyStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum PowerSupplyStatus : int
                    {
                        PowerSupplyStatus_NotPresent = 0,
                        PowerSupplyStatus_Inadequate = 1,
                        PowerSupplyStatus_Adequate = 2,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.SystemSuspendStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum SystemSuspendStatus : int
                    {
                        SystemSuspendStatus_Uninitialized = 0,
                        SystemSuspendStatus_Entering = 1,
                        SystemSuspendStatus_AutoResume = 2,
                        SystemSuspendStatus_ManualResume = 3,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.UserPresenceStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    enum UserPresenceStatus : int
                    {
                        UserPresenceStatus_Present = 0,
                        UserPresenceStatus_Absent = 1,
                    };
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.System.Power.IPowerManagerStatics
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.Power.PowerManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_Power_IPowerManagerStatics[] = L"Microsoft.Windows.System.Power.IPowerManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    MIDL_INTERFACE("fa3554cc-be1c-534c-bff8-72df78e9f4a4")
                    IPowerManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_EnergySaverStatus(
                            ABI::Microsoft::Windows::System::Power::EnergySaverStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_EnergySaverStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_EnergySaverStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_BatteryStatus(
                            ABI::Microsoft::Windows::System::Power::BatteryStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_BatteryStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_BatteryStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PowerSupplyStatus(
                            ABI::Microsoft::Windows::System::Power::PowerSupplyStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_PowerSupplyStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_PowerSupplyStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RemainingChargePercent(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_RemainingChargePercentChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_RemainingChargePercentChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RemainingDischargeTime(
                            ABI::Windows::Foundation::TimeSpan* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_RemainingDischargeTimeChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_RemainingDischargeTimeChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PowerSourceKind(
                            ABI::Microsoft::Windows::System::Power::PowerSourceKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_PowerSourceKindChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_PowerSourceKindChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DisplayStatus(
                            ABI::Microsoft::Windows::System::Power::DisplayStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_DisplayStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_DisplayStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_SystemIdleStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_SystemIdleStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_EffectivePowerMode(
                            __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_EffectivePowerModeChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_EffectivePowerModeChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_UserPresenceStatus(
                            ABI::Microsoft::Windows::System::Power::UserPresenceStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_UserPresenceStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_UserPresenceStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SystemSuspendStatus(
                            ABI::Microsoft::Windows::System::Power::SystemSuspendStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_SystemSuspendStatusChanged(
                            __FIEventHandler_1_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_SystemSuspendStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPowerManagerStatics = _uuidof(IPowerManagerStatics);
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.System.Power.IPowerManagerStatics2
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.Power.PowerManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_Power_IPowerManagerStatics2[] = L"Microsoft.Windows.System.Power.IPowerManagerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                namespace Power {
                    MIDL_INTERFACE("61f3cc25-65b4-5def-9c9b-990cef3b0833")
                    IPowerManagerStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_EffectivePowerMode2(
                            ABI::Microsoft::Windows::System::Power::EffectivePowerMode* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPowerManagerStatics2 = _uuidof(IPowerManagerStatics2);
                } /* Power */
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.System.Power.PowerManager
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.System.Power.IPowerManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.System.Power.PowerNotificationsContract API contract
 *   Static Methods exist on the Microsoft.Windows.System.Power.IPowerManagerStatics interface starting with version 1.0 of the Microsoft.Windows.System.Power.PowerNotificationsContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_System_Power_PowerManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_System_Power_PowerManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_System_Power_PowerManager[] = L"Microsoft.Windows.System.Power.PowerManager";
#endif
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2 __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2;

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEffectivePowerMode __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEffectivePowerMode;

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode;

#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode;

typedef struct __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerModeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEffectivePowerMode* result);

    END_INTERFACE
} __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerModeVtbl;

interface __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode
{
    CONST_VTBL struct __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerModeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode;

typedef struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerModeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerModeVtbl;

interface __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerModeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#if !defined(____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__)
#define ____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__

typedef interface __FIEventHandler_1_IInspectable __FIEventHandler_1_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIEventHandler_1_IInspectable;

typedef struct __FIEventHandler_1_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIEventHandler_1_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIEventHandler_1_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIEventHandler_1_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIEventHandler_1_IInspectable* This,
        IInspectable* sender,
        IInspectable* args);

    END_INTERFACE
} __FIEventHandler_1_IInspectableVtbl;

interface __FIEventHandler_1_IInspectable
{
    CONST_VTBL struct __FIEventHandler_1_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIEventHandler_1_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIEventHandler_1_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIEventHandler_1_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIEventHandler_1_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FIEventHandler_1_IInspectable_INTERFACE_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CTimeSpan __x_ABI_CWindows_CFoundation_CTimeSpan;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CBatteryStatus __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CBatteryStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CDisplayStatus __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CDisplayStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEnergySaverStatus __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEnergySaverStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSourceKind __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSourceKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSupplyStatus __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSupplyStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CSystemSuspendStatus __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CSystemSuspendStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CUserPresenceStatus __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CUserPresenceStatus;

/*
 *
 * Struct Microsoft.Windows.System.Power.BatteryStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CBatteryStatus
{
    BatteryStatus_NotPresent = 0,
    BatteryStatus_Discharging = 1,
    BatteryStatus_Idle = 2,
    BatteryStatus_Charging = 3,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.DisplayStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CDisplayStatus
{
    DisplayStatus_Off = 0,
    DisplayStatus_On = 1,
    DisplayStatus_Dimmed = 2,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.EffectivePowerMode
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEffectivePowerMode
{
    EffectivePowerMode_BatterySaver = 0,
    EffectivePowerMode_BetterBattery = 1,
    EffectivePowerMode_Balanced = 2,
    EffectivePowerMode_HighPerformance = 3,
    EffectivePowerMode_MaxPerformance = 4,
    EffectivePowerMode_GameMode = 5,
    EffectivePowerMode_MixedReality = 6,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.EnergySaverStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEnergySaverStatus
{
    EnergySaverStatus_Uninitialized = 0,
    EnergySaverStatus_Disabled = 1,
    EnergySaverStatus_Off = 2,
    EnergySaverStatus_On = 3,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.PowerSourceKind
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSourceKind
{
    PowerSourceKind_AC = 0,
    PowerSourceKind_DC = 1,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.PowerSupplyStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSupplyStatus
{
    PowerSupplyStatus_NotPresent = 0,
    PowerSupplyStatus_Inadequate = 1,
    PowerSupplyStatus_Adequate = 2,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.SystemSuspendStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CSystemSuspendStatus
{
    SystemSuspendStatus_Uninitialized = 0,
    SystemSuspendStatus_Entering = 1,
    SystemSuspendStatus_AutoResume = 2,
    SystemSuspendStatus_ManualResume = 3,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.System.Power.UserPresenceStatus
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CUserPresenceStatus
{
    UserPresenceStatus_Present = 0,
    UserPresenceStatus_Absent = 1,
};
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.System.Power.IPowerManagerStatics
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.Power.PowerManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_Power_IPowerManagerStatics[] = L"Microsoft.Windows.System.Power.IPowerManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_EnergySaverStatus)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEnergySaverStatus* value);
    HRESULT (STDMETHODCALLTYPE* add_EnergySaverStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_EnergySaverStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_BatteryStatus)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CBatteryStatus* value);
    HRESULT (STDMETHODCALLTYPE* add_BatteryStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_BatteryStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_PowerSupplyStatus)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSupplyStatus* value);
    HRESULT (STDMETHODCALLTYPE* add_PowerSupplyStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_PowerSupplyStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_RemainingChargePercent)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* add_RemainingChargePercentChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_RemainingChargePercentChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_RemainingDischargeTime)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan* value);
    HRESULT (STDMETHODCALLTYPE* add_RemainingDischargeTimeChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_RemainingDischargeTimeChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_PowerSourceKind)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CPowerSourceKind* value);
    HRESULT (STDMETHODCALLTYPE* add_PowerSourceKindChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_PowerSourceKindChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_DisplayStatus)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CDisplayStatus* value);
    HRESULT (STDMETHODCALLTYPE* add_DisplayStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_DisplayStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_SystemIdleStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_SystemIdleStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_EffectivePowerMode)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIAsyncOperation_1_Microsoft__CWindows__CSystem__CPower__CEffectivePowerMode** value);
    HRESULT (STDMETHODCALLTYPE* add_EffectivePowerModeChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_EffectivePowerModeChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_UserPresenceStatus)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CUserPresenceStatus* value);
    HRESULT (STDMETHODCALLTYPE* add_UserPresenceStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_UserPresenceStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* get_SystemSuspendStatus)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CSystemSuspendStatus* value);
    HRESULT (STDMETHODCALLTYPE* add_SystemSuspendStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        __FIEventHandler_1_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_SystemSuspendStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_EnergySaverStatus(This, value) \
    ((This)->lpVtbl->get_EnergySaverStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_EnergySaverStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_EnergySaverStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_EnergySaverStatusChanged(This, token) \
    ((This)->lpVtbl->remove_EnergySaverStatusChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_BatteryStatus(This, value) \
    ((This)->lpVtbl->get_BatteryStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_BatteryStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_BatteryStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_BatteryStatusChanged(This, token) \
    ((This)->lpVtbl->remove_BatteryStatusChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_PowerSupplyStatus(This, value) \
    ((This)->lpVtbl->get_PowerSupplyStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_PowerSupplyStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_PowerSupplyStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_PowerSupplyStatusChanged(This, token) \
    ((This)->lpVtbl->remove_PowerSupplyStatusChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_RemainingChargePercent(This, value) \
    ((This)->lpVtbl->get_RemainingChargePercent(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_RemainingChargePercentChanged(This, handler, token) \
    ((This)->lpVtbl->add_RemainingChargePercentChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_RemainingChargePercentChanged(This, token) \
    ((This)->lpVtbl->remove_RemainingChargePercentChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_RemainingDischargeTime(This, value) \
    ((This)->lpVtbl->get_RemainingDischargeTime(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_RemainingDischargeTimeChanged(This, handler, token) \
    ((This)->lpVtbl->add_RemainingDischargeTimeChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_RemainingDischargeTimeChanged(This, token) \
    ((This)->lpVtbl->remove_RemainingDischargeTimeChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_PowerSourceKind(This, value) \
    ((This)->lpVtbl->get_PowerSourceKind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_PowerSourceKindChanged(This, handler, token) \
    ((This)->lpVtbl->add_PowerSourceKindChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_PowerSourceKindChanged(This, token) \
    ((This)->lpVtbl->remove_PowerSourceKindChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_DisplayStatus(This, value) \
    ((This)->lpVtbl->get_DisplayStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_DisplayStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_DisplayStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_DisplayStatusChanged(This, token) \
    ((This)->lpVtbl->remove_DisplayStatusChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_SystemIdleStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_SystemIdleStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_SystemIdleStatusChanged(This, token) \
    ((This)->lpVtbl->remove_SystemIdleStatusChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_EffectivePowerMode(This, value) \
    ((This)->lpVtbl->get_EffectivePowerMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_EffectivePowerModeChanged(This, handler, token) \
    ((This)->lpVtbl->add_EffectivePowerModeChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_EffectivePowerModeChanged(This, token) \
    ((This)->lpVtbl->remove_EffectivePowerModeChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_UserPresenceStatus(This, value) \
    ((This)->lpVtbl->get_UserPresenceStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_UserPresenceStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_UserPresenceStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_UserPresenceStatusChanged(This, token) \
    ((This)->lpVtbl->remove_UserPresenceStatusChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_get_SystemSuspendStatus(This, value) \
    ((This)->lpVtbl->get_SystemSuspendStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_add_SystemSuspendStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_SystemSuspendStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_remove_SystemSuspendStatusChanged(This, token) \
    ((This)->lpVtbl->remove_SystemSuspendStatusChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.System.Power.IPowerManagerStatics2
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.Power.PowerManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_Power_IPowerManagerStatics2[] = L"Microsoft.Windows.System.Power.IPowerManagerStatics2";
typedef struct __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_EffectivePowerMode2)(__x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2* This,
        enum __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CEffectivePowerMode* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_get_EffectivePowerMode2(This, value) \
    ((This)->lpVtbl->get_EffectivePowerMode2(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CPower_CIPowerManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.System.Power.PowerManager
 *
 * Introduced to Microsoft.Windows.System.Power.PowerNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.System.Power.IPowerManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.System.Power.PowerNotificationsContract API contract
 *   Static Methods exist on the Microsoft.Windows.System.Power.IPowerManagerStatics interface starting with version 1.0 of the Microsoft.Windows.System.Power.PowerNotificationsContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_System_Power_PowerManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_System_Power_PowerManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_System_Power_PowerManager[] = L"Microsoft.Windows.System.Power.PowerManager";
#endif
#endif // MICROSOFT_WINDOWS_SYSTEM_POWER_POWERNOTIFICATIONSCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Esystem2Epower_p_h__

#endif // __microsoft2Ewindows2Esystem2Epower_h__
