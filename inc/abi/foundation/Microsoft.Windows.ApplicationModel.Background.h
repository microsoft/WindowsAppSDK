
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
#ifndef __microsoft2Ewindows2Eapplicationmodel2Ebackground_h__
#define __microsoft2Ewindows2Eapplicationmodel2Ebackground_h__
#ifndef __microsoft2Ewindows2Eapplicationmodel2Ebackground_p_h__
#define __microsoft2Ewindows2Eapplicationmodel2Ebackground_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION)

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
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Background {
                    interface IBackgroundTaskBuilder;
                } /* Background */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder ABI::Microsoft::Windows::ApplicationModel::Background::IBackgroundTaskBuilder

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                class BackgroundTaskRegistration;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundTaskRegistration;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration ABI::Windows::ApplicationModel::Background::IBackgroundTaskRegistration

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                class BackgroundTaskRegistrationGroup;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundTaskRegistrationGroup;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup ABI::Windows::ApplicationModel::Background::IBackgroundTaskRegistrationGroup

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundCondition;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition ABI::Windows::ApplicationModel::Background::IBackgroundCondition

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            namespace Background {
                interface IBackgroundTrigger;
            } /* Background */
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger ABI::Windows::ApplicationModel::Background::IBackgroundTrigger

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_FWD_DEFINED__

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Background.IBackgroundTaskBuilder
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.BackgroundTaskContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Background_IBackgroundTaskBuilder[] = L"Microsoft.Windows.ApplicationModel.Background.IBackgroundTaskBuilder";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Background {
                    MIDL_INTERFACE("32a355a0-75ca-5cb8-9f8e-2c4ea62d1ee3")
                    IBackgroundTaskBuilder : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SetTrigger(
                            ABI::Windows::ApplicationModel::Background::IBackgroundTrigger* trigger
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetTaskEntryPointClsid(
                            GUID clsId
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddCondition(
                            ABI::Windows::ApplicationModel::Background::IBackgroundCondition* condition
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Name(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Name(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TaskGroup(
                            ABI::Windows::ApplicationModel::Background::IBackgroundTaskRegistrationGroup* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TaskGroup(
                            ABI::Windows::ApplicationModel::Background::IBackgroundTaskRegistrationGroup** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Register(
                            ABI::Windows::ApplicationModel::Background::IBackgroundTaskRegistration** task
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Register2(
                            HSTRING name,
                            ABI::Windows::ApplicationModel::Background::IBackgroundTaskRegistration** task
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IBackgroundTaskBuilder = _uuidof(IBackgroundTaskBuilder);
                } /* Background */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.BackgroundTaskContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Background.BackgroundTaskContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Background.IBackgroundTaskBuilder ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_BackgroundTaskBuilder_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_BackgroundTaskBuilder_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Background_BackgroundTaskBuilder[] = L"Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_FWD_DEFINED__
#define ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger;

#endif // ____x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger_FWD_DEFINED__

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Background.IBackgroundTaskBuilder
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.BackgroundTaskContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Background_IBackgroundTaskBuilder[] = L"Microsoft.Windows.ApplicationModel.Background.IBackgroundTaskBuilder";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SetTrigger)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTrigger* trigger);
    HRESULT (STDMETHODCALLTYPE* SetTaskEntryPointClsid)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        GUID clsId);
    HRESULT (STDMETHODCALLTYPE* AddCondition)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundCondition* condition);
    HRESULT (STDMETHODCALLTYPE* put_Name)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_TaskGroup)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup* value);
    HRESULT (STDMETHODCALLTYPE* get_TaskGroup)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistrationGroup** value);
    HRESULT (STDMETHODCALLTYPE* Register)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration** task);
    HRESULT (STDMETHODCALLTYPE* Register2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder* This,
        HSTRING name,
        __x_ABI_CWindows_CApplicationModel_CBackground_CIBackgroundTaskRegistration** task);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_SetTrigger(This, trigger) \
    ((This)->lpVtbl->SetTrigger(This, trigger))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_SetTaskEntryPointClsid(This, clsId) \
    ((This)->lpVtbl->SetTaskEntryPointClsid(This, clsId))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_AddCondition(This, condition) \
    ((This)->lpVtbl->AddCondition(This, condition))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_put_Name(This, value) \
    ((This)->lpVtbl->put_Name(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_put_TaskGroup(This, value) \
    ((This)->lpVtbl->put_TaskGroup(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_get_TaskGroup(This, value) \
    ((This)->lpVtbl->get_TaskGroup(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_Register(This, task) \
    ((This)->lpVtbl->Register(This, task))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_Register2(This, name, task) \
    ((This)->lpVtbl->Register2(This, name, task))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CBackground_CIBackgroundTaskBuilder_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Background.BackgroundTaskContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Background.BackgroundTaskContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Background.IBackgroundTaskBuilder ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_BackgroundTaskBuilder_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Background_BackgroundTaskBuilder_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Background_BackgroundTaskBuilder[] = L"Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_BACKGROUND_BACKGROUNDTASKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eapplicationmodel2Ebackground_p_h__

#endif // __microsoft2Ewindows2Eapplicationmodel2Ebackground_h__
