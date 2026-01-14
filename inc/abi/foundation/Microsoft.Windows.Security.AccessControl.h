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
#ifndef __microsoft2Ewindows2Esecurity2Eaccesscontrol_h__
#define __microsoft2Ewindows2Esecurity2Eaccesscontrol_h__
#ifndef __microsoft2Ewindows2Esecurity2Eaccesscontrol_p_h__
#define __microsoft2Ewindows2Esecurity2Eaccesscontrol_p_h__


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
#if !defined(MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Security {
                namespace AccessControl {
                    interface ISecurityDescriptorHelpersStatics;
                } /* AccessControl */
            } /* Security */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics ABI::Microsoft::Windows::Security::AccessControl::ISecurityDescriptorHelpersStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Security {
                namespace AccessControl {
                    typedef struct AppContainerNameAndAccess AppContainerNameAndAccess;
                } /* AccessControl */
            } /* Security */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Security.AccessControl.AppContainerNameAndAccess
 *
 * Introduced to Microsoft.Windows.Security.AccessControl.AccessControlContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Security {
                namespace AccessControl {
                    struct AppContainerNameAndAccess
                    {
                        HSTRING appContainerName;
                        UINT32 accessMask;
                    };
                } /* AccessControl */
            } /* Security */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Security.AccessControl.ISecurityDescriptorHelpersStatics
 *
 * Introduced to Microsoft.Windows.Security.AccessControl.AccessControlContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers
 *
 */
#if MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Security_AccessControl_ISecurityDescriptorHelpersStatics[] = L"Microsoft.Windows.Security.AccessControl.ISecurityDescriptorHelpersStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Security {
                namespace AccessControl {
                    MIDL_INTERFACE("14fa9e8d-59f0-5017-852f-3ae24fd5ebb1")
                    ISecurityDescriptorHelpersStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetSddlForAppContainerNames(
                            UINT32 accessRequestsLength,
                            ABI::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess* accessRequests,
                            HSTRING principalStringSid,
                            UINT32 principalAccessMask,
                            HSTRING* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetSecurityDescriptorBytesFromAppContainerNames(
                            UINT32 accessRequestsLength,
                            ABI::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess* accessRequests,
                            HSTRING principalStringSid,
                            UINT32 principalAccessMask,
                            UINT32* resultLength,
                            BYTE** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ISecurityDescriptorHelpersStatics = _uuidof(ISecurityDescriptorHelpersStatics);
                } /* AccessControl */
            } /* Security */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers
 *
 * Introduced to Microsoft.Windows.Security.AccessControl.AccessControlContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Security.AccessControl.ISecurityDescriptorHelpersStatics interface starting with version 1.0 of the Microsoft.Windows.Security.AccessControl.AccessControlContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Security_AccessControl_SecurityDescriptorHelpers_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Security_AccessControl_SecurityDescriptorHelpers_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Security_AccessControl_SecurityDescriptorHelpers[] = L"Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers";
#endif
#endif // MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CAppContainerNameAndAccess __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CAppContainerNameAndAccess;

/*
 *
 * Struct Microsoft.Windows.Security.AccessControl.AppContainerNameAndAccess
 *
 * Introduced to Microsoft.Windows.Security.AccessControl.AccessControlContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CAppContainerNameAndAccess
{
    HSTRING appContainerName;
    UINT32 accessMask;
};
#endif // MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Security.AccessControl.ISecurityDescriptorHelpersStatics
 *
 * Introduced to Microsoft.Windows.Security.AccessControl.AccessControlContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers
 *
 */
#if MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Security_AccessControl_ISecurityDescriptorHelpersStatics[] = L"Microsoft.Windows.Security.AccessControl.ISecurityDescriptorHelpersStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetSddlForAppContainerNames)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This,
        UINT32 accessRequestsLength,
        struct __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CAppContainerNameAndAccess* accessRequests,
        HSTRING principalStringSid,
        UINT32 principalAccessMask,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* GetSecurityDescriptorBytesFromAppContainerNames)(__x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics* This,
        UINT32 accessRequestsLength,
        struct __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CAppContainerNameAndAccess* accessRequests,
        HSTRING principalStringSid,
        UINT32 principalAccessMask,
        UINT32* resultLength,
        BYTE** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_GetSddlForAppContainerNames(This, accessRequestsLength, accessRequests, principalStringSid, principalAccessMask, result) \
    ((This)->lpVtbl->GetSddlForAppContainerNames(This, accessRequestsLength, accessRequests, principalStringSid, principalAccessMask, result))

#define __x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_GetSecurityDescriptorBytesFromAppContainerNames(This, accessRequestsLength, accessRequests, principalStringSid, principalAccessMask, resultLength, result) \
    ((This)->lpVtbl->GetSecurityDescriptorBytesFromAppContainerNames(This, accessRequestsLength, accessRequests, principalStringSid, principalAccessMask, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSecurity_CAccessControl_CISecurityDescriptorHelpersStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers
 *
 * Introduced to Microsoft.Windows.Security.AccessControl.AccessControlContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Security.AccessControl.ISecurityDescriptorHelpersStatics interface starting with version 1.0 of the Microsoft.Windows.Security.AccessControl.AccessControlContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Security_AccessControl_SecurityDescriptorHelpers_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Security_AccessControl_SecurityDescriptorHelpers_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Security_AccessControl_SecurityDescriptorHelpers[] = L"Microsoft.Windows.Security.AccessControl.SecurityDescriptorHelpers";
#endif
#endif // MICROSOFT_WINDOWS_SECURITY_ACCESSCONTROL_ACCESSCONTROLCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Esecurity2Eaccesscontrol_p_h__

#endif // __microsoft2Ewindows2Esecurity2Eaccesscontrol_h__
