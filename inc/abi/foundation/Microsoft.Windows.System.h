
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
#ifndef __microsoft2Ewindows2Esystem_h__
#define __microsoft2Ewindows2Esystem_h__
#ifndef __microsoft2Ewindows2Esystem_p_h__
#define __microsoft2Ewindows2Esystem_p_h__


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
#if !defined(MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                interface IEnvironmentManager;
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager ABI::Microsoft::Windows::System::IEnvironmentManager

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                interface IEnvironmentManager2;
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2 ABI::Microsoft::Windows::System::IEnvironmentManager2

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                interface IEnvironmentManagerStatics;
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics ABI::Microsoft::Windows::System::IEnvironmentManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions

#ifndef DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("60310303-49c5-52e6-abc6-a9b36eccc716"))
IKeyValuePair<HSTRING, HSTRING> : IKeyValuePair_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, HSTRING> __FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("05eb86f1-7140-5517-b88d-cbaebe57e6b1"))
IIterator<__FIKeyValuePair_2_HSTRING_HSTRING*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING_HSTRING*> __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e9bdaaf0-cbf6-5c72-be90-29cbf3a1319b"))
IIterable<__FIKeyValuePair_2_HSTRING_HSTRING*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING_HSTRING*> __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_USE */



#ifndef DEF___FIMapView_2_HSTRING_HSTRING_USE
#define DEF___FIMapView_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ac7f26f2-feb7-5b2a-8ac4-345bc62caede"))
IMapView<HSTRING, HSTRING> : IMapView_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, HSTRING> __FIMapView_2_HSTRING_HSTRING_t;
#define __FIMapView_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING_HSTRING_USE */


namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                class EnvironmentManager;
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.Windows.System.IEnvironmentManager
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.EnvironmentManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_IEnvironmentManager[] = L"Microsoft.Windows.System.IEnvironmentManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                MIDL_INTERFACE("d1b239bb-7013-5176-b02a-63477410d986")
                IEnvironmentManager : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetEnvironmentVariables(
                        __FIMapView_2_HSTRING_HSTRING** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetEnvironmentVariable(
                        HSTRING name,
                        HSTRING* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetEnvironmentVariable(
                        HSTRING name,
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE AppendToPath(
                        HSTRING path
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveFromPath(
                        HSTRING path
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE AddExecutableFileExtension(
                        HSTRING pathExt
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RemoveExecutableFileExtension(
                        HSTRING pathExt
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IEnvironmentManager = _uuidof(IEnvironmentManager);
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.System.IEnvironmentManager2
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.EnvironmentManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_IEnvironmentManager2[] = L"Microsoft.Windows.System.IEnvironmentManager2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                MIDL_INTERFACE("cfc0ad51-02b7-57ff-8ca7-e015251737cb")
                IEnvironmentManager2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AreChangesTracked(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IEnvironmentManager2 = _uuidof(IEnvironmentManager2);
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.System.IEnvironmentManagerStatics
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.EnvironmentManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_IEnvironmentManagerStatics[] = L"Microsoft.Windows.System.IEnvironmentManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace System {
                MIDL_INTERFACE("407b1522-6156-5398-93fd-d6411c35e7b1")
                IEnvironmentManagerStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetForProcess(
                        ABI::Microsoft::Windows::System::IEnvironmentManager** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetForUser(
                        ABI::Microsoft::Windows::System::IEnvironmentManager** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetForMachine(
                        ABI::Microsoft::Windows::System::IEnvironmentManager** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSupported(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IEnvironmentManagerStatics = _uuidof(IEnvironmentManagerStatics);
            } /* System */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.System.EnvironmentManager
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.System.IEnvironmentManagerStatics interface starting with version 1.0 of the Microsoft.Windows.System.EnvironmentManagerContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.System.IEnvironmentManager ** Default Interface **
 *    Microsoft.Windows.System.IEnvironmentManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_System_EnvironmentManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_System_EnvironmentManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_System_EnvironmentManager[] = L"Microsoft.Windows.System.EnvironmentManager";
#endif
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2 __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2;

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if !defined(____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_HSTRING __FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_HSTRING_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_HSTRING_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        __FIKeyValuePair_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING_HSTRING** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING_HSTRING** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_HSTRING __FIMapView_2_HSTRING_HSTRING;

#if !defined(____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_HSTRING __FIMapView_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING_HSTRING;

typedef struct __FIMapView_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING_HSTRING* This,
        __FIMapView_2_HSTRING_HSTRING** first,
        __FIMapView_2_HSTRING_HSTRING** second);

    END_INTERFACE
} __FIMapView_2_HSTRING_HSTRINGVtbl;

interface __FIMapView_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIMapView_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING_HSTRING_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING_HSTRING_INTERFACE_DEFINED__

/*
 *
 * Interface Microsoft.Windows.System.IEnvironmentManager
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.EnvironmentManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_IEnvironmentManager[] = L"Microsoft.Windows.System.IEnvironmentManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetEnvironmentVariables)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        __FIMapView_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* GetEnvironmentVariable)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING name,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* SetEnvironmentVariable)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING name,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* AppendToPath)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING path);
    HRESULT (STDMETHODCALLTYPE* RemoveFromPath)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING path);
    HRESULT (STDMETHODCALLTYPE* AddExecutableFileExtension)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING pathExt);
    HRESULT (STDMETHODCALLTYPE* RemoveExecutableFileExtension)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager* This,
        HSTRING pathExt);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_GetEnvironmentVariables(This, result) \
    ((This)->lpVtbl->GetEnvironmentVariables(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_GetEnvironmentVariable(This, name, result) \
    ((This)->lpVtbl->GetEnvironmentVariable(This, name, result))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_SetEnvironmentVariable(This, name, value) \
    ((This)->lpVtbl->SetEnvironmentVariable(This, name, value))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_AppendToPath(This, path) \
    ((This)->lpVtbl->AppendToPath(This, path))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_RemoveFromPath(This, path) \
    ((This)->lpVtbl->RemoveFromPath(This, path))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_AddExecutableFileExtension(This, pathExt) \
    ((This)->lpVtbl->AddExecutableFileExtension(This, pathExt))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_RemoveExecutableFileExtension(This, pathExt) \
    ((This)->lpVtbl->RemoveExecutableFileExtension(This, pathExt))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.System.IEnvironmentManager2
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.EnvironmentManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_IEnvironmentManager2[] = L"Microsoft.Windows.System.IEnvironmentManager2";
typedef struct __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AreChangesTracked)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_get_AreChangesTracked(This, value) \
    ((This)->lpVtbl->get_AreChangesTracked(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.System.IEnvironmentManagerStatics
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.System.EnvironmentManager
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_System_IEnvironmentManagerStatics[] = L"Microsoft.Windows.System.IEnvironmentManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetForProcess)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager** result);
    HRESULT (STDMETHODCALLTYPE* GetForUser)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager** result);
    HRESULT (STDMETHODCALLTYPE* GetForMachine)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManager** result);
    HRESULT (STDMETHODCALLTYPE* get_IsSupported)(__x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_GetForProcess(This, result) \
    ((This)->lpVtbl->GetForProcess(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_GetForUser(This, result) \
    ((This)->lpVtbl->GetForUser(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_GetForMachine(This, result) \
    ((This)->lpVtbl->GetForMachine(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_get_IsSupported(This, value) \
    ((This)->lpVtbl->get_IsSupported(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSystem_CIEnvironmentManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.System.EnvironmentManager
 *
 * Introduced to Microsoft.Windows.System.EnvironmentManagerContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.System.IEnvironmentManagerStatics interface starting with version 1.0 of the Microsoft.Windows.System.EnvironmentManagerContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.System.IEnvironmentManager ** Default Interface **
 *    Microsoft.Windows.System.IEnvironmentManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_System_EnvironmentManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_System_EnvironmentManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_System_EnvironmentManager[] = L"Microsoft.Windows.System.EnvironmentManager";
#endif
#endif // MICROSOFT_WINDOWS_SYSTEM_ENVIRONMENTMANAGERCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Esystem_p_h__

#endif // __microsoft2Ewindows2Esystem_h__
