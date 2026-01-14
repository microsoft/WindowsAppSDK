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
#ifndef __microsoft2Ewindows2Eai2Efoundation_h__
#define __microsoft2Ewindows2Eai2Efoundation_h__
#ifndef __microsoft2Ewindows2Eai2Efoundation_p_h__
#define __microsoft2Ewindows2Eai2Efoundation_p_h__


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
#if !defined(MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    interface IEmbeddingVector;
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVector

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    interface IEmbeddingVectorFactory;
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVectorFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    class EmbeddingVector;
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.Windows.AI.Foundation.IEmbeddingVector
 *
 * Introduced to Microsoft.Windows.AI.Foundation.AIFoundationContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Foundation.EmbeddingVector
 *
 */
#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Foundation_IEmbeddingVector[] = L"Microsoft.Windows.AI.Foundation.IEmbeddingVector";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    MIDL_INTERFACE("07bdaa90-b3d2-5701-97d1-c390ec62799c")
                    IEmbeddingVector : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetValues(
                            UINT32 valuesLength,
                            FLOAT* values
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Size(
                            UINT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_VectorSpaceId(
                            GUID* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IEmbeddingVector = _uuidof(IEmbeddingVector);
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Foundation.IEmbeddingVectorFactory
 *
 * Introduced to Microsoft.Windows.AI.Foundation.AIFoundationContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Foundation.EmbeddingVector
 *
 */
#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Foundation_IEmbeddingVectorFactory[] = L"Microsoft.Windows.AI.Foundation.IEmbeddingVectorFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace AI {
                namespace Foundation {
                    MIDL_INTERFACE("16b72758-2b69-5e97-b865-6a6a71683dd0")
                    IEmbeddingVectorFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            UINT32 dataLength,
                            FLOAT* data,
                            GUID vectorSpaceID,
                            ABI::Microsoft::Windows::AI::Foundation::IEmbeddingVector** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IEmbeddingVectorFactory = _uuidof(IEmbeddingVectorFactory);
                } /* Foundation */
            } /* AI */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Foundation.EmbeddingVector
 *
 * Introduced to Microsoft.Windows.AI.Foundation.AIFoundationContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Foundation.IEmbeddingVectorFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Foundation.AIFoundationContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Foundation.IEmbeddingVector ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Foundation_EmbeddingVector_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Foundation_EmbeddingVector_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Foundation_EmbeddingVector[] = L"Microsoft.Windows.AI.Foundation.EmbeddingVector";
#endif
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

/*
 *
 * Interface Microsoft.Windows.AI.Foundation.IEmbeddingVector
 *
 * Introduced to Microsoft.Windows.AI.Foundation.AIFoundationContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Foundation.EmbeddingVector
 *
 */
#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Foundation_IEmbeddingVector[] = L"Microsoft.Windows.AI.Foundation.IEmbeddingVector";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetValues)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        UINT32 valuesLength,
        FLOAT* values);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* get_VectorSpaceId)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector* This,
        GUID* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_GetValues(This, valuesLength, values) \
    ((This)->lpVtbl->GetValues(This, valuesLength, values))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_get_Size(This, value) \
    ((This)->lpVtbl->get_Size(This, value))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_get_VectorSpaceId(This, value) \
    ((This)->lpVtbl->get_VectorSpaceId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.AI.Foundation.IEmbeddingVectorFactory
 *
 * Introduced to Microsoft.Windows.AI.Foundation.AIFoundationContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.AI.Foundation.EmbeddingVector
 *
 */
#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_AI_Foundation_IEmbeddingVectorFactory[] = L"Microsoft.Windows.AI.Foundation.IEmbeddingVectorFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory* This,
        UINT32 dataLength,
        FLOAT* data,
        GUID vectorSpaceID,
        __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVector** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_CreateInstance(This, dataLength, data, vectorSpaceID, value) \
    ((This)->lpVtbl->CreateInstance(This, dataLength, data, vectorSpaceID, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CAI_CFoundation_CIEmbeddingVectorFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.AI.Foundation.EmbeddingVector
 *
 * Introduced to Microsoft.Windows.AI.Foundation.AIFoundationContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.AI.Foundation.IEmbeddingVectorFactory interface starting with version 1.0 of the Microsoft.Windows.AI.Foundation.AIFoundationContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.AI.Foundation.IEmbeddingVector ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_AI_Foundation_EmbeddingVector_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_AI_Foundation_EmbeddingVector_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_AI_Foundation_EmbeddingVector[] = L"Microsoft.Windows.AI.Foundation.EmbeddingVector";
#endif
#endif // MICROSOFT_WINDOWS_AI_FOUNDATION_AIFOUNDATIONCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eai2Efoundation_p_h__

#endif // __microsoft2Ewindows2Eai2Efoundation_h__
