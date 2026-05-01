
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
#ifndef __microsoft2Ewindows2Estorage_h__
#define __microsoft2Ewindows2Estorage_h__
#ifndef __microsoft2Ewindows2Estorage_p_h__
#define __microsoft2Ewindows2Estorage_p_h__


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
#if !defined(MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION)
#define MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)
#define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
#endif // defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)
#define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
#endif // defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)

#if !defined(WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION)
#define WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION 0x70000
#endif // defined(WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Windows.Storage.h"
#include "Windows.System.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                interface IApplicationData;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData ABI::Microsoft::Windows::Storage::IApplicationData

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                interface IApplicationDataContainer;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer ABI::Microsoft::Windows::Storage::IApplicationDataContainer

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                interface IApplicationDataStatics;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics ABI::Microsoft::Windows::Storage::IApplicationDataStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                class ApplicationDataContainer;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#define DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b6a85d01-ee6a-500f-879f-3cce5723ecd4"))
IKeyValuePair<HSTRING, ABI::Microsoft::Windows::Storage::ApplicationDataContainer*> : IKeyValuePair_impl<HSTRING, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::ApplicationDataContainer*, ABI::Microsoft::Windows::Storage::IApplicationDataContainer*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.Storage.ApplicationDataContainer>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, ABI::Microsoft::Windows::Storage::ApplicationDataContainer*> __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t;
#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("025639f8-aa0e-57a9-8a5d-412b8afc0646"))
IIterator<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.Storage.ApplicationDataContainer>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer*> __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e7030f31-6eb1-5a96-a63c-285edbad7ce9"))
IIterable<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.Storage.ApplicationDataContainer>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer*> __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef DEF___FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#define DEF___FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("9f95d2db-8cfe-5ef4-ae51-4d42ccc21929"))
IMapView<HSTRING, ABI::Microsoft::Windows::Storage::ApplicationDataContainer*> : IMapView_impl<HSTRING, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::ApplicationDataContainer*, ABI::Microsoft::Windows::Storage::IApplicationDataContainer*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, Microsoft.Windows.Storage.ApplicationDataContainer>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, ABI::Microsoft::Windows::Storage::ApplicationDataContainer*> __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t;
#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef DEF___FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#define DEF___FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("bd32b940-93ee-53e5-9637-f9d3b3a32fb0"))
IMap<HSTRING, ABI::Microsoft::Windows::Storage::ApplicationDataContainer*> : IMap_impl<HSTRING, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Storage::ApplicationDataContainer*, ABI::Microsoft::Windows::Storage::IApplicationDataContainer*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMap`2<String, Microsoft.Windows.Storage.ApplicationDataContainer>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMap<HSTRING, ABI::Microsoft::Windows::Storage::ApplicationDataContainer*> __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t;
#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer ABI::Windows::Foundation::Collections::__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_USE */

#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            namespace Collections {
                interface IPropertySet;
            } /* Collections */
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet ABI::Windows::Foundation::Collections::IPropertySet

#endif // ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__

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

namespace ABI {
    namespace Windows {
        namespace Storage {
            class StorageFolder;
        } /* Storage */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CStorage_CIStorageFolder_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CIStorageFolder_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            interface IStorageFolder;
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CIStorageFolder ABI::Windows::Storage::IStorageFolder

#endif // ____x_ABI_CWindows_CStorage_CIStorageFolder_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace System {
            class User;
        } /* System */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CSystem_CIUser_FWD_DEFINED__
#define ____x_ABI_CWindows_CSystem_CIUser_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace System {
            interface IUser;
        } /* System */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CSystem_CIUser ABI::Windows::System::IUser

#endif // ____x_ABI_CWindows_CSystem_CIUser_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                typedef enum ApplicationDataCreateDisposition : int ApplicationDataCreateDisposition;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                typedef enum ApplicationDataLocality : int ApplicationDataLocality;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                class ApplicationData;
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Storage.ApplicationDataCreateDisposition
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                enum ApplicationDataCreateDisposition : int
                {
                    ApplicationDataCreateDisposition_Always = 0,
                    ApplicationDataCreateDisposition_Existing = 1,
                };
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Storage.ApplicationDataLocality
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                enum ApplicationDataLocality : int
                {
                    ApplicationDataLocality_Local = 0,
                    ApplicationDataLocality_LocalCache = 3,
                    ApplicationDataLocality_SharedLocal = 4,
                    ApplicationDataLocality_Temporary = 2,
                    ApplicationDataLocality_Machine = 1000,
                };
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Storage.IApplicationData
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.ApplicationData
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_IApplicationData[] = L"Microsoft.Windows.Storage.IApplicationData";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                MIDL_INTERFACE("fc073ce2-2f7b-5214-95fa-530a3f9d1ea5")
                IApplicationData : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_IsMachinePathSupported(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalCachePath(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalPath(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MachinePath(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SharedLocalPath(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_TemporaryPath(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalCacheFolder(
                        ABI::Windows::Storage::IStorageFolder** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalFolder(
                        ABI::Windows::Storage::IStorageFolder** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_MachineFolder(
                        ABI::Windows::Storage::IStorageFolder** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SharedLocalFolder(
                        ABI::Windows::Storage::IStorageFolder** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_TemporaryFolder(
                        ABI::Windows::Storage::IStorageFolder** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalSettings(
                        ABI::Microsoft::Windows::Storage::IApplicationDataContainer** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ClearAsync(
                        ABI::Microsoft::Windows::Storage::ApplicationDataLocality locality,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ClearPublisherCacheFolderAsync(
                        HSTRING folderName,
                        ABI::Windows::Foundation::IAsyncAction** operation
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetPublisherCachePath(
                        HSTRING folderName,
                        HSTRING* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetPublisherCacheFolder(
                        HSTRING folderName,
                        ABI::Windows::Storage::IStorageFolder** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IApplicationData = _uuidof(IApplicationData);
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Storage.IApplicationDataContainer
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.ApplicationDataContainer
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_IApplicationDataContainer[] = L"Microsoft.Windows.Storage.IApplicationDataContainer";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                MIDL_INTERFACE("d1fa9c23-2e59-55d8-bd86-88c2fdc9e7c9")
                IApplicationDataContainer : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Containers(
                        __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Name(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Locality(
                        ABI::Microsoft::Windows::Storage::ApplicationDataLocality* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Values(
                        ABI::Windows::Foundation::Collections::IPropertySet** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateContainer(
                        HSTRING name,
                        ABI::Microsoft::Windows::Storage::ApplicationDataCreateDisposition disposition,
                        ABI::Microsoft::Windows::Storage::IApplicationDataContainer** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE DeleteContainer(
                        HSTRING name
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IApplicationDataContainer = _uuidof(IApplicationDataContainer);
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Storage.IApplicationDataStatics
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.ApplicationData
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_IApplicationDataStatics[] = L"Microsoft.Windows.Storage.IApplicationDataStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Storage {
                MIDL_INTERFACE("6a8b41f8-5560-56fb-86b0-d59e897d4d95")
                IApplicationDataStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetDefault(
                        ABI::Microsoft::Windows::Storage::IApplicationData** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetForUser(
                        ABI::Windows::System::IUser* user,
                        ABI::Microsoft::Windows::Storage::IApplicationData** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetForPackageFamily(
                        HSTRING packageFamilyName,
                        ABI::Microsoft::Windows::Storage::IApplicationData** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IApplicationDataStatics = _uuidof(IApplicationDataStatics);
            } /* Storage */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Storage.ApplicationData
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Storage.IApplicationDataStatics interface starting with version 1.0 of the Microsoft.Windows.Storage.ApplicationDataContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.IApplicationData ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationData_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationData_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_ApplicationData[] = L"Microsoft.Windows.Storage.ApplicationData";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Storage.ApplicationDataContainer
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.IApplicationDataContainer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationDataContainer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationDataContainer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_ApplicationDataContainer[] = L"Microsoft.Windows.Storage.ApplicationDataContainer";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

typedef struct __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer** result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl;

interface __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

typedef interface __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

typedef struct __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING key,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** first,
        __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** second);

    END_INTERFACE
} __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl;

interface __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer
{
    CONST_VTBL struct __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__)
#define ____FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

typedef interface __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer;

typedef struct __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING key,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        __FIMapView_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** result);
    HRESULT (STDMETHODCALLTYPE* Insert)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING key,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Remove)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This,
        HSTRING key);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer* This);

    END_INTERFACE
} __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl;

interface __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer
{
    CONST_VTBL struct __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Insert(This, key, value, result) \
    ((This)->lpVtbl->Insert(This, key, value, result))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Remove(This, key) \
    ((This)->lpVtbl->Remove(This, key))

#define __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#endif /* COBJMACROS */

#endif // ____FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet;

#endif // ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIAsyncAction __x_ABI_CWindows_CFoundation_CIAsyncAction;

#endif // ____x_ABI_CWindows_CFoundation_CIAsyncAction_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CStorage_CIStorageFolder_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CIStorageFolder_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CIStorageFolder __x_ABI_CWindows_CStorage_CIStorageFolder;

#endif // ____x_ABI_CWindows_CStorage_CIStorageFolder_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CSystem_CIUser_FWD_DEFINED__
#define ____x_ABI_CWindows_CSystem_CIUser_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CSystem_CIUser __x_ABI_CWindows_CSystem_CIUser;

#endif // ____x_ABI_CWindows_CSystem_CIUser_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataCreateDisposition __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataCreateDisposition;

typedef enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataLocality __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataLocality;

/*
 *
 * Struct Microsoft.Windows.Storage.ApplicationDataCreateDisposition
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataCreateDisposition
{
    ApplicationDataCreateDisposition_Always = 0,
    ApplicationDataCreateDisposition_Existing = 1,
};
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Storage.ApplicationDataLocality
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataLocality
{
    ApplicationDataLocality_Local = 0,
    ApplicationDataLocality_LocalCache = 3,
    ApplicationDataLocality_SharedLocal = 4,
    ApplicationDataLocality_Temporary = 2,
    ApplicationDataLocality_Machine = 1000,
};
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Storage.IApplicationData
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.ApplicationData
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_IApplicationData[] = L"Microsoft.Windows.Storage.IApplicationData";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsMachinePathSupported)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_LocalCachePath)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_LocalPath)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_MachinePath)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_SharedLocalPath)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_TemporaryPath)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_LocalCacheFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        __x_ABI_CWindows_CStorage_CIStorageFolder** value);
    HRESULT (STDMETHODCALLTYPE* get_LocalFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        __x_ABI_CWindows_CStorage_CIStorageFolder** value);
    HRESULT (STDMETHODCALLTYPE* get_MachineFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        __x_ABI_CWindows_CStorage_CIStorageFolder** value);
    HRESULT (STDMETHODCALLTYPE* get_SharedLocalFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        __x_ABI_CWindows_CStorage_CIStorageFolder** value);
    HRESULT (STDMETHODCALLTYPE* get_TemporaryFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        __x_ABI_CWindows_CStorage_CIStorageFolder** value);
    HRESULT (STDMETHODCALLTYPE* get_LocalSettings)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer** value);
    HRESULT (STDMETHODCALLTYPE* ClearAsync)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataLocality locality,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* ClearPublisherCacheFolderAsync)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING folderName,
        __x_ABI_CWindows_CFoundation_CIAsyncAction** operation);
    HRESULT (STDMETHODCALLTYPE* GetPublisherCachePath)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING folderName,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* GetPublisherCacheFolder)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData* This,
        HSTRING folderName,
        __x_ABI_CWindows_CStorage_CIStorageFolder** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_IsMachinePathSupported(This, value) \
    ((This)->lpVtbl->get_IsMachinePathSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_LocalCachePath(This, value) \
    ((This)->lpVtbl->get_LocalCachePath(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_LocalPath(This, value) \
    ((This)->lpVtbl->get_LocalPath(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_MachinePath(This, value) \
    ((This)->lpVtbl->get_MachinePath(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_SharedLocalPath(This, value) \
    ((This)->lpVtbl->get_SharedLocalPath(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_TemporaryPath(This, value) \
    ((This)->lpVtbl->get_TemporaryPath(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_LocalCacheFolder(This, value) \
    ((This)->lpVtbl->get_LocalCacheFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_LocalFolder(This, value) \
    ((This)->lpVtbl->get_LocalFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_MachineFolder(This, value) \
    ((This)->lpVtbl->get_MachineFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_SharedLocalFolder(This, value) \
    ((This)->lpVtbl->get_SharedLocalFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_TemporaryFolder(This, value) \
    ((This)->lpVtbl->get_TemporaryFolder(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_get_LocalSettings(This, value) \
    ((This)->lpVtbl->get_LocalSettings(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_ClearAsync(This, locality, operation) \
    ((This)->lpVtbl->ClearAsync(This, locality, operation))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_ClearPublisherCacheFolderAsync(This, folderName, operation) \
    ((This)->lpVtbl->ClearPublisherCacheFolderAsync(This, folderName, operation))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_GetPublisherCachePath(This, folderName, result) \
    ((This)->lpVtbl->GetPublisherCachePath(This, folderName, result))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_GetPublisherCacheFolder(This, folderName, result) \
    ((This)->lpVtbl->GetPublisherCacheFolder(This, folderName, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Storage.IApplicationDataContainer
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.ApplicationDataContainer
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_IApplicationDataContainer[] = L"Microsoft.Windows.Storage.IApplicationDataContainer";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Containers)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        __FIMap_2_HSTRING_Microsoft__CWindows__CStorage__CApplicationDataContainer** value);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Locality)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataLocality* value);
    HRESULT (STDMETHODCALLTYPE* get_Values)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet** value);
    HRESULT (STDMETHODCALLTYPE* CreateContainer)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        HSTRING name,
        enum __x_ABI_CMicrosoft_CWindows_CStorage_CApplicationDataCreateDisposition disposition,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer** result);
    HRESULT (STDMETHODCALLTYPE* DeleteContainer)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer* This,
        HSTRING name);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_get_Containers(This, value) \
    ((This)->lpVtbl->get_Containers(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_get_Locality(This, value) \
    ((This)->lpVtbl->get_Locality(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_get_Values(This, value) \
    ((This)->lpVtbl->get_Values(This, value))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_CreateContainer(This, name, disposition, result) \
    ((This)->lpVtbl->CreateContainer(This, name, disposition, result))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_DeleteContainer(This, name) \
    ((This)->lpVtbl->DeleteContainer(This, name))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Storage.IApplicationDataStatics
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Storage.ApplicationData
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Storage_IApplicationDataStatics[] = L"Microsoft.Windows.Storage.IApplicationDataStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDefault)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData** result);
    HRESULT (STDMETHODCALLTYPE* GetForUser)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        __x_ABI_CWindows_CSystem_CIUser* user,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData** result);
    HRESULT (STDMETHODCALLTYPE* GetForPackageFamily)(__x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics* This,
        HSTRING packageFamilyName,
        __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationData** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_GetDefault(This, result) \
    ((This)->lpVtbl->GetDefault(This, result))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_GetForUser(This, user, result) \
    ((This)->lpVtbl->GetForUser(This, user, result))

#define __x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_GetForPackageFamily(This, packageFamilyName, result) \
    ((This)->lpVtbl->GetForPackageFamily(This, packageFamilyName, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Storage.ApplicationData
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Storage.IApplicationDataStatics interface starting with version 1.0 of the Microsoft.Windows.Storage.ApplicationDataContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.IApplicationData ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationData_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationData_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_ApplicationData[] = L"Microsoft.Windows.Storage.ApplicationData";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Storage.ApplicationDataContainer
 *
 * Introduced to Microsoft.Windows.Storage.ApplicationDataContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Storage.IApplicationDataContainer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationDataContainer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Storage_ApplicationDataContainer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Storage_ApplicationDataContainer[] = L"Microsoft.Windows.Storage.ApplicationDataContainer";
#endif
#endif // MICROSOFT_WINDOWS_STORAGE_APPLICATIONDATACONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Estorage_p_h__

#endif // __microsoft2Ewindows2Estorage_h__
