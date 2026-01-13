
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
#ifndef __microsoft2Eui2Ecomposition2Ecore_h__
#define __microsoft2Eui2Ecomposition2Ecore_h__
#ifndef __microsoft2Eui2Ecomposition2Ecore_p_h__
#define __microsoft2Eui2Ecomposition2Ecore_p_h__


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
#include "Microsoft.UI.Composition.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Core {
                    interface ICompositorController;
                } /* Core */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController ABI::Microsoft::UI::Composition::Core::ICompositorController

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Core {
                    class CompositorController;
                } /* Core */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("951d00b7-db3e-522c-b1f7-2bef3e1b9108"))
ITypedEventHandler<ABI::Microsoft::UI::Composition::Core::CompositorController*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Composition::Core::CompositorController*, ABI::Microsoft::UI::Composition::Core::ICompositorController*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Composition.Core.CompositorController, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Composition::Core::CompositorController*, IInspectable*> __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class Compositor;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositor;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositor ABI::Microsoft::UI::Composition::ICompositor

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

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

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IClosable;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIClosable ABI::Windows::Foundation::IClosable

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

/*
 *
 * Interface Microsoft.UI.Composition.Core.ICompositorController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Core.CompositorController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Core_ICompositorController[] = L"Microsoft.UI.Composition.Core.ICompositorController";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                namespace Core {
                    MIDL_INTERFACE("cc107cdc-558f-5d1a-96a5-a735ac04386b")
                    ICompositorController : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Compositor(
                            ABI::Microsoft::UI::Composition::ICompositor** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Commit(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsurePreviousCommitCompletedAsync(
                            ABI::Windows::Foundation::IAsyncAction** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_CommitNeeded(
                            __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_CommitNeeded(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICompositorController = _uuidof(ICompositorController);
                } /* Core */
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Core.CompositorController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Core.ICompositorController ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Core_CompositorController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Core_CompositorController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Core_CompositorController[] = L"Microsoft.UI.Composition.Core.CompositorController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositor __x_ABI_CMicrosoft_CUI_CComposition_CICompositor;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIAsyncAction __x_ABI_CWindows_CFoundation_CIAsyncAction;

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

/*
 *
 * Interface Microsoft.UI.Composition.Core.ICompositorController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Composition.Core.CompositorController
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Composition_Core_ICompositorController[] = L"Microsoft.UI.Composition.Core.ICompositorController";
typedef struct __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorControllerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Compositor)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor** value);
    HRESULT (STDMETHODCALLTYPE* Commit)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This);
    HRESULT (STDMETHODCALLTYPE* EnsurePreviousCommitCompletedAsync)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* add_CommitNeeded)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        __FITypedEventHandler_2_Microsoft__CUI__CComposition__CCore__CCompositorController_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_CommitNeeded)(__x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorControllerVtbl;

interface __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorControllerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_get_Compositor(This, value) \
    ((This)->lpVtbl->get_Compositor(This, value))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_Commit(This) \
    ((This)->lpVtbl->Commit(This))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_EnsurePreviousCommitCompletedAsync(This, operation) \
    ((This)->lpVtbl->EnsurePreviousCommitCompletedAsync(This, operation))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_add_CommitNeeded(This, handler, token) \
    ((This)->lpVtbl->add_CommitNeeded(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_remove_CommitNeeded(This, token) \
    ((This)->lpVtbl->remove_CommitNeeded(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CComposition_CCore_CICompositorController_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Composition.Core.CompositorController
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Composition.Core.ICompositorController ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Composition_Core_CompositorController_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Composition_Core_CompositorController_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Composition_Core_CompositorController[] = L"Microsoft.UI.Composition.Core.CompositorController";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Ecomposition2Ecore_p_h__

#endif // __microsoft2Eui2Ecomposition2Ecore_h__
