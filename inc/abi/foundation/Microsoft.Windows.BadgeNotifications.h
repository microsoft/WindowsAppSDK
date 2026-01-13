
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
#ifndef __microsoft2Ewindows2Ebadgenotifications_h__
#define __microsoft2Ewindows2Ebadgenotifications_h__
#ifndef __microsoft2Ewindows2Ebadgenotifications_p_h__
#define __microsoft2Ewindows2Ebadgenotifications_p_h__


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
#if !defined(MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                interface IBadgeNotificationManager;
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager ABI::Microsoft::Windows::BadgeNotifications::IBadgeNotificationManager

#endif // ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                interface IBadgeNotificationManagerStatics;
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics ABI::Microsoft::Windows::BadgeNotifications::IBadgeNotificationManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                typedef enum BadgeNotificationGlyph : int BadgeNotificationGlyph;
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                class BadgeNotificationManager;
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.BadgeNotifications.BadgeNotificationGlyph
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                enum BadgeNotificationGlyph : int
                {
                    BadgeNotificationGlyph_None = 0,
                    BadgeNotificationGlyph_Activity = 1,
                    BadgeNotificationGlyph_Alarm = 2,
                    BadgeNotificationGlyph_Alert = 3,
                    BadgeNotificationGlyph_Attention = 4,
                    BadgeNotificationGlyph_Available = 5,
                    BadgeNotificationGlyph_Away = 6,
                    BadgeNotificationGlyph_Busy = 7,
                    BadgeNotificationGlyph_Error = 8,
                    BadgeNotificationGlyph_NewMessage = 9,
                    BadgeNotificationGlyph_Paused = 10,
                    BadgeNotificationGlyph_Playing = 11,
                    BadgeNotificationGlyph_Unavailable = 12,
                };
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.BadgeNotifications.IBadgeNotificationManager
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.BadgeNotifications.BadgeNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_BadgeNotifications_IBadgeNotificationManager[] = L"Microsoft.Windows.BadgeNotifications.IBadgeNotificationManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                MIDL_INTERFACE("11cb6e8f-11ca-53f8-80f6-5330d44ba908")
                IBadgeNotificationManager : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE SetBadgeAsCount(
                        UINT32 notificationCount
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetBadgeAsGlyph(
                        ABI::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ClearBadge(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IBadgeNotificationManager = _uuidof(IBadgeNotificationManager);
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.BadgeNotifications.IBadgeNotificationManagerStatics
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.BadgeNotifications.BadgeNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_BadgeNotifications_IBadgeNotificationManagerStatics[] = L"Microsoft.Windows.BadgeNotifications.IBadgeNotificationManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace BadgeNotifications {
                MIDL_INTERFACE("a6e71616-7c9f-5d22-ad1c-f4ab874087b5")
                IBadgeNotificationManagerStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Current(
                        ABI::Microsoft::Windows::BadgeNotifications::IBadgeNotificationManager** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IBadgeNotificationManagerStatics = _uuidof(IBadgeNotificationManagerStatics);
            } /* BadgeNotifications */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.BadgeNotifications.BadgeNotificationManager
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.BadgeNotifications.IBadgeNotificationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.BadgeNotifications.IBadgeNotificationManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_BadgeNotifications_BadgeNotificationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_BadgeNotifications_BadgeNotificationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_BadgeNotifications_BadgeNotificationManager[] = L"Microsoft.Windows.BadgeNotifications.BadgeNotificationManager";
#endif
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CBadgeNotificationGlyph __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CBadgeNotificationGlyph;

/*
 *
 * Struct Microsoft.Windows.BadgeNotifications.BadgeNotificationGlyph
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CBadgeNotificationGlyph
{
    BadgeNotificationGlyph_None = 0,
    BadgeNotificationGlyph_Activity = 1,
    BadgeNotificationGlyph_Alarm = 2,
    BadgeNotificationGlyph_Alert = 3,
    BadgeNotificationGlyph_Attention = 4,
    BadgeNotificationGlyph_Available = 5,
    BadgeNotificationGlyph_Away = 6,
    BadgeNotificationGlyph_Busy = 7,
    BadgeNotificationGlyph_Error = 8,
    BadgeNotificationGlyph_NewMessage = 9,
    BadgeNotificationGlyph_Paused = 10,
    BadgeNotificationGlyph_Playing = 11,
    BadgeNotificationGlyph_Unavailable = 12,
};
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.BadgeNotifications.IBadgeNotificationManager
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.BadgeNotifications.BadgeNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_BadgeNotifications_IBadgeNotificationManager[] = L"Microsoft.Windows.BadgeNotifications.IBadgeNotificationManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SetBadgeAsCount)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This,
        UINT32 notificationCount);
    HRESULT (STDMETHODCALLTYPE* SetBadgeAsGlyph)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This,
        enum __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CBadgeNotificationGlyph glyphValue);
    HRESULT (STDMETHODCALLTYPE* ClearBadge)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_SetBadgeAsCount(This, notificationCount) \
    ((This)->lpVtbl->SetBadgeAsCount(This, notificationCount))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_SetBadgeAsGlyph(This, glyphValue) \
    ((This)->lpVtbl->SetBadgeAsGlyph(This, glyphValue))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_ClearBadge(This) \
    ((This)->lpVtbl->ClearBadge(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.BadgeNotifications.IBadgeNotificationManagerStatics
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.BadgeNotifications.BadgeNotificationManager
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_BadgeNotifications_IBadgeNotificationManagerStatics[] = L"Microsoft.Windows.BadgeNotifications.IBadgeNotificationManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManager** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_get_Current(This, value) \
    ((This)->lpVtbl->get_Current(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CBadgeNotifications_CIBadgeNotificationManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.BadgeNotifications.BadgeNotificationManager
 *
 * Introduced to Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.BadgeNotifications.IBadgeNotificationManagerStatics interface starting with version 1.0 of the Microsoft.Windows.BadgeNotifications.BadgeNotificationsContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.BadgeNotifications.IBadgeNotificationManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_BadgeNotifications_BadgeNotificationManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_BadgeNotifications_BadgeNotificationManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_BadgeNotifications_BadgeNotificationManager[] = L"Microsoft.Windows.BadgeNotifications.BadgeNotificationManager";
#endif
#endif // MICROSOFT_WINDOWS_BADGENOTIFICATIONS_BADGENOTIFICATIONSCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Ebadgenotifications_p_h__

#endif // __microsoft2Ewindows2Ebadgenotifications_h__
