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
#ifndef __microsoft2Ewindows2Eai_h__
#define __microsoft2Ewindows2Eai_h__
#ifndef __microsoft2Ewindows2Eai_p_h__
#define __microsoft2Ewindows2Eai_p_h__


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
#if !defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                interface IAIFeatureReadyResult;
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult ABI::Microsoft::Windows::AI::IAIFeatureReadyResult

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                typedef enum AIFeatureReadyResultState : int AIFeatureReadyResultState;
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.AI.AIFeatureReadyResultState
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                enum AIFeatureReadyResultState : int
                {
                    AIFeatureReadyResultState_InProgress = 0,
                    AIFeatureReadyResultState_Success = 1,
                    AIFeatureReadyResultState_Failure = 2,
                };
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.AIFeatureReadyState
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                enum AIFeatureReadyState : int
                {
                    AIFeatureReadyState_Ready = 0,
                    AIFeatureReadyState_NotReady = 1,
                    AIFeatureReadyState_NotSupportedOnCurrentSystem = 2,
                    AIFeatureReadyState_DisabledByUser = 3,
                };
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.IAIFeatureReadyResult
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.AIFeatureReadyResult
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_IAIFeatureReadyResult[] = L"Microsoft.Windows.AI.IAIFeatureReadyResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                MIDL_INTERFACE("936a78a6-c242-5937-9814-e512d4193a6d")
                IAIFeatureReadyResult : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Error(
                        HRESULT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ErrorDisplayText(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                        HRESULT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Status(
                        ABI::Microsoft::Windows::AI::AIFeatureReadyResultState* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAIFeatureReadyResult = _uuidof(IAIFeatureReadyResult);
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.AIFeatureReadyResult
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.IAIFeatureReadyResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_AIFeatureReadyResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_AIFeatureReadyResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_AIFeatureReadyResult[] = L"Microsoft.Windows.AI.AIFeatureReadyResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyResultState __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyResultState;

/*
 *
 * Struct Microsoft.Windows.AI.AIFeatureReadyResultState
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyResultState
{
    AIFeatureReadyResultState_InProgress = 0,
    AIFeatureReadyResultState_Success = 1,
    AIFeatureReadyResultState_Failure = 2,
};
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.AI.AIFeatureReadyState
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyState
{
    AIFeatureReadyState_Ready = 0,
    AIFeatureReadyState_NotReady = 1,
    AIFeatureReadyState_NotSupportedOnCurrentSystem = 2,
    AIFeatureReadyState_DisabledByUser = 3,
};
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.IAIFeatureReadyResult
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.AIFeatureReadyResult
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_IAIFeatureReadyResult[] = L"Microsoft.Windows.AI.IAIFeatureReadyResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Error)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorDisplayText)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CAI_CAIFeatureReadyResultState* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_get_Error(This, value) \
    ((This)->lpVtbl->get_Error(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_get_ErrorDisplayText(This, value) \
    ((This)->lpVtbl->get_ErrorDisplayText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CIAIFeatureReadyResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.AIFeatureReadyResult
 *
 * Introduced to Microsoft.Windows.AI.AIFeatureReadyContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.IAIFeatureReadyResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_AIFeatureReadyResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_AIFeatureReadyResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_AIFeatureReadyResult[] = L"Microsoft.Windows.AI.AIFeatureReadyResult";
#endif
#endif // MICROSOFT_WINDOWS_AI_AIFEATUREREADYCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eai_p_h__

#endif // __microsoft2Ewindows2Eai_h__
