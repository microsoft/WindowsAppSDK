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
#ifndef __microsoft2Ewindows2Eapplicationmodel2Ebackground2Euniversalbgtask_h__
#define __microsoft2Ewindows2Eapplicationmodel2Ebackground2Euniversalbgtask_h__
#ifndef __microsoft2Ewindows2Eapplicationmodel2Ebackground2Euniversalbgtask_p_h__
#define __microsoft2Ewindows2Eapplicationmodel2Ebackground2Euniversalbgtask_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION)

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
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Background {
                    namespace UniversalBGTask {
                        interface ITask;
                    } /* UniversalBGTask */
                } /* Background */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask ABI::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::ITask

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundTask;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask ABI::Windows::ApplicationModel::Background::IBackgroundTask

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_FWD_DEFINED__

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.ITask
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.UniversalBackgroundTaskContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_ITask[] = L"Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.ITask";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Background {
                    namespace UniversalBGTask {
                        MIDL_INTERFACE("89cf5f73-8195-590b-8158-bc7d2816ce16")
                        ITask : public IInspectable
                        {
                        public:
                        };

                        MIDL_CONST_ID IID& IID_ITask = _uuidof(ITask);
                    } /* UniversalBGTask */
                } /* Background */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.UniversalBackgroundTaskContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.UniversalBackgroundTaskContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.ITask ** Default Interface **
 *    Windows.ApplicationModel.Background.IBackgroundTask
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_Task_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_Task_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_Task[] = L"Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTask_FWD_DEFINED__

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.ITask
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.UniversalBackgroundTaskContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_ITask[] = L"Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.ITask";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITaskVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITaskVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITaskVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CUniversalBGTask_CITask_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.UniversalBackgroundTaskContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.UniversalBackgroundTaskContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.ITask ** Default Interface **
 *    Windows.ApplicationModel.Background.IBackgroundTask
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_Task_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_Task_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Background_UniversalBGTask_Task[] = L"Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_UNIVERSALBGTASK_UNIVERSALBACKGROUNDTASKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eapplicationmodel2Ebackground2Euniversalbgtask_p_h__

#endif // __microsoft2Ewindows2Eapplicationmodel2Ebackground2Euniversalbgtask_h__
