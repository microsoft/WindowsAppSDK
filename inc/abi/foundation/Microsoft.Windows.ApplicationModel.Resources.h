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
#ifndef __microsoft2Ewindows2Eapplicationmodel2Eresources_h__
#define __microsoft2Ewindows2Eapplicationmodel2Eresources_h__
#ifndef __microsoft2Ewindows2Eapplicationmodel2Eresources_p_h__
#define __microsoft2Ewindows2Eapplicationmodel2Eresources_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION)

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
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IKnownResourceQualifierNameStatics;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics ABI::Microsoft::Windows::ApplicationModel::Resources::IKnownResourceQualifierNameStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceCandidate;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceCandidateFactory;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidateFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceContext;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceContext2;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2 ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext2

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceLoader;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceLoader

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceLoaderFactory;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceLoaderFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceLoaderStatics;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceLoaderStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceManager;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceManager

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceManager2;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2 ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceManager2

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceManagerFactory;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceManagerFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceMap;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceMap

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    interface IResourceNotFoundEventArgs;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceNotFoundEventArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_FWD_DEFINED__

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


namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    class ResourceCandidate;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

#ifndef DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_USE
#define DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("6a46de21-86a6-536a-937b-1edfa3e16474"))
IKeyValuePair<HSTRING, ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate*> : IKeyValuePair_impl<HSTRING, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate*, ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate*> __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_t;
#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_USE */

#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000


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



#ifndef DEF___FIMap_2_HSTRING_HSTRING_USE
#define DEF___FIMap_2_HSTRING_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f6d1f700-49c2-52ae-8154-826f9908773c"))
IMap<HSTRING, HSTRING> : IMap_impl<HSTRING, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMap`2<String, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMap<HSTRING, HSTRING> __FIMap_2_HSTRING_HSTRING_t;
#define __FIMap_2_HSTRING_HSTRING ABI::Windows::Foundation::Collections::__FIMap_2_HSTRING_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMap_2_HSTRING_HSTRING_USE */


namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    class ResourceManager;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    class ResourceNotFoundEventArgs;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("30bb9803-2b8a-58e0-8812-93967822d6d0"))
ITypedEventHandler<ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceManager*, ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceManager*, ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceManager*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs*, ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceNotFoundEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.ApplicationModel.Resources.ResourceManager, Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceManager*, ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs*> __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_USE */

#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Windows {
        namespace Foundation {
            class Uri;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IUriRuntimeClass;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIUriRuntimeClass ABI::Windows::Foundation::IUriRuntimeClass

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    typedef enum ResourceCandidateKind : int ResourceCandidateKind;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    class ResourceContext;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    class ResourceLoader;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    class ResourceMap;
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.Resources.ResourceCandidateKind
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    enum ResourceCandidateKind : int
                    {
                        ResourceCandidateKind_Unknown = 0,
                        ResourceCandidateKind_String = 1,
                        ResourceCandidateKind_FilePath = 2,
                        ResourceCandidateKind_EmbeddedData = 3,
                    };
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IKnownResourceQualifierNameStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.KnownResourceQualifierName
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IKnownResourceQualifierNameStatics[] = L"Microsoft.Windows.ApplicationModel.Resources.IKnownResourceQualifierNameStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("dd6cdedc-559b-50c8-ac53-82fe21f915f3")
                    IKnownResourceQualifierNameStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Contrast(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Custom(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeviceFamily(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HomeRegion(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LayoutDirection(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Scale(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TargetSize(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Theme(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IKnownResourceQualifierNameStatics = _uuidof(IKnownResourceQualifierNameStatics);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceCandidate
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceCandidate[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceCandidate";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("6c54bc0c-ef1e-57b8-b478-34fece737356")
                    IResourceCandidate : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ValueAsString(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ValueAsBytes(
                            UINT32* valueLength,
                            BYTE** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Kind(
                            ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceCandidateKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_QualifierValues(
                            __FIMapView_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceCandidate = _uuidof(IResourceCandidate);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceCandidateFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceCandidateFactory[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceCandidateFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("bb2b30f8-c19b-5f43-88d9-69ad728a32f4")
                    IResourceCandidateFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::ApplicationModel::Resources::ResourceCandidateKind kind,
                            HSTRING data,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance2(
                            UINT32 dataLength,
                            BYTE* data,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceCandidateFactory = _uuidof(IResourceCandidateFactory);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceContext[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceContext";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("96fb48dc-f77d-55ff-af12-34861e3d4939")
                    IResourceContext : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_QualifierValues(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceContext = _uuidof(IResourceContext);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceContext2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceContext
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceContext2[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceContext2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("7a3b1158-798c-5949-969d-03510b9ce6ca")
                    IResourceContext2 : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IResourceContext2 = _uuidof(IResourceContext2);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceLoader
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceLoader[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceLoader";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("bc3f76bf-da46-54cd-8715-8b8aaf16eaac")
                    IResourceLoader : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetString(
                            HSTRING resourceId,
                            HSTRING* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetStringForUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* resourceUri,
                            HSTRING* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceLoader = _uuidof(IResourceLoader);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceLoaderFactory[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("871f83aa-fb34-50d6-b9b9-2c35f3ffc004")
                    IResourceLoaderFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING fileName,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceLoader** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance2(
                            HSTRING fileName,
                            HSTRING resourceMap,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceLoader** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceLoaderFactory = _uuidof(IResourceLoaderFactory);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceLoaderStatics[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("ec9c894a-1466-5f2f-8eee-a70cbd2b51bb")
                    IResourceLoaderStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetDefaultResourceFilePath(
                            HSTRING* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceLoaderStatics = _uuidof(IResourceLoaderStatics);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceManager
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceManager[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("ac2291ef-81be-5c99-a0ae-bcee0180b8a8")
                    IResourceManager : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_MainResourceMap(
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceMap** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateResourceContext(
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_ResourceNotFound(
                            __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_ResourceNotFound(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceManager = _uuidof(IResourceManager);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceManager2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceManager2[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceManager2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("7ec10160-a154-5c42-8268-30e306b1f585")
                    IResourceManager2 : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IResourceManager2 = _uuidof(IResourceManager2);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceManagerFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceManagerFactory[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceManagerFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("d6acf18f-458a-535b-a5c4-ac2dc4e49099")
                    IResourceManagerFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING fileName,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceManager** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceManagerFactory = _uuidof(IResourceManagerFactory);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceMap
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceMap
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceMap[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceMap";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("4abbd9bc-df4e-5c7b-812c-7e7bb0c22377")
                    IResourceMap : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ResourceCount(
                            UINT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetSubtree(
                            HSTRING reference,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceMap** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryGetSubtree(
                            HSTRING reference,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceMap** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetValue(
                            HSTRING resource,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetValueWithContext(
                            HSTRING resource,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext* context,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetValueByIndex(
                            UINT32 index,
                            __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetValueByIndexWithContext(
                            UINT32 index,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext* context,
                            __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryGetValue(
                            HSTRING resource,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE TryGetValueWithContext(
                            HSTRING resource,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext* context,
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceMap = _uuidof(IResourceMap);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceNotFoundEventArgs
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceNotFoundEventArgs[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceNotFoundEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace Resources {
                    MIDL_INTERFACE("64abb08b-e77d-5b26-830f-15941e0e8200")
                    IResourceNotFoundEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Context(
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Name(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetResolvedCandidate(
                            ABI::Microsoft::Windows::ApplicationModel::Resources::IResourceCandidate* candidate
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IResourceNotFoundEventArgs = _uuidof(IResourceNotFoundEventArgs);
                } /* Resources */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.KnownResourceQualifierName
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.Resources.IKnownResourceQualifierNameStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_KnownResourceQualifierName_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_KnownResourceQualifierName_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_KnownResourceQualifierName[] = L"Microsoft.Windows.ApplicationModel.Resources.KnownResourceQualifierName";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.Resources.IResourceCandidateFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceCandidate ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceCandidate_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceCandidate_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceCandidate[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceContext2
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceContext ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceContext[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceContext";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceLoader ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceLoader_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceLoader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceLoader[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceLoader";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceManager
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.Resources.IResourceManagerFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceManager2
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceManager[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceManager";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceMap
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceMap ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceMap_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceMap_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceMap[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceMap";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceNotFoundEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceNotFoundEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceNotFoundEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceNotFoundEventArgs[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2 __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2 __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_FWD_DEFINED__

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

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate;

typedef struct __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidateVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidateVtbl;

interface __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidateVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

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

#if !defined(____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__)
#define ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMap_2_HSTRING_HSTRING __FIMap_2_HSTRING_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMap_2_HSTRING_HSTRING;

typedef struct __FIMap_2_HSTRING_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMap_2_HSTRING_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMap_2_HSTRING_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMap_2_HSTRING_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMap_2_HSTRING_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMap_2_HSTRING_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMap_2_HSTRING_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIMap_2_HSTRING_HSTRING* This,
        __FIMapView_2_HSTRING_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* Insert)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key,
        HSTRING value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Remove)(__FIMap_2_HSTRING_HSTRING* This,
        HSTRING key);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIMap_2_HSTRING_HSTRING* This);

    END_INTERFACE
} __FIMap_2_HSTRING_HSTRINGVtbl;

interface __FIMap_2_HSTRING_HSTRING
{
    CONST_VTBL struct __FIMap_2_HSTRING_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMap_2_HSTRING_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMap_2_HSTRING_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMap_2_HSTRING_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMap_2_HSTRING_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMap_2_HSTRING_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMap_2_HSTRING_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMap_2_HSTRING_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMap_2_HSTRING_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMap_2_HSTRING_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMap_2_HSTRING_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIMap_2_HSTRING_HSTRING_Insert(This, key, value, result) \
    ((This)->lpVtbl->Insert(This, key, value, result))

#define __FIMap_2_HSTRING_HSTRING_Remove(This, key) \
    ((This)->lpVtbl->Remove(This, key))

#define __FIMap_2_HSTRING_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#endif /* COBJMACROS */

#endif // ____FIMap_2_HSTRING_HSTRING_INTERFACE_DEFINED__

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* sender,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CResourceCandidateKind __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CResourceCandidateKind;

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.Resources.ResourceCandidateKind
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CResourceCandidateKind
{
    ResourceCandidateKind_Unknown = 0,
    ResourceCandidateKind_String = 1,
    ResourceCandidateKind_FilePath = 2,
    ResourceCandidateKind_EmbeddedData = 3,
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IKnownResourceQualifierNameStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.KnownResourceQualifierName
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IKnownResourceQualifierNameStatics[] = L"Microsoft.Windows.ApplicationModel.Resources.IKnownResourceQualifierNameStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Contrast)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Custom)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_DeviceFamily)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_HomeRegion)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_LayoutDirection)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Scale)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_TargetSize)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Theme)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_Contrast(This, value) \
    ((This)->lpVtbl->get_Contrast(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_Custom(This, value) \
    ((This)->lpVtbl->get_Custom(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_DeviceFamily(This, value) \
    ((This)->lpVtbl->get_DeviceFamily(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_HomeRegion(This, value) \
    ((This)->lpVtbl->get_HomeRegion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_LayoutDirection(This, value) \
    ((This)->lpVtbl->get_LayoutDirection(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_Scale(This, value) \
    ((This)->lpVtbl->get_Scale(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_TargetSize(This, value) \
    ((This)->lpVtbl->get_TargetSize(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_get_Theme(This, value) \
    ((This)->lpVtbl->get_Theme(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIKnownResourceQualifierNameStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceCandidate
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceCandidate[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceCandidate";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ValueAsString)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ValueAsBytes)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        UINT32* valueLength,
        BYTE** value);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CResourceCandidateKind* value);
    HRESULT (STDMETHODCALLTYPE* get_QualifierValues)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* This,
        __FIMapView_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_get_ValueAsString(This, value) \
    ((This)->lpVtbl->get_ValueAsString(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_get_ValueAsBytes(This, valueLength, value) \
    ((This)->lpVtbl->get_ValueAsBytes(This, valueLength, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_get_QualifierValues(This, value) \
    ((This)->lpVtbl->get_QualifierValues(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceCandidateFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceCandidateFactory[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceCandidateFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CResourceCandidateKind kind,
        HSTRING data,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** value);
    HRESULT (STDMETHODCALLTYPE* CreateInstance2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory* This,
        UINT32 dataLength,
        BYTE* data,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_CreateInstance(This, kind, data, value) \
    ((This)->lpVtbl->CreateInstance(This, kind, data, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_CreateInstance2(This, dataLength, data, value) \
    ((This)->lpVtbl->CreateInstance2(This, dataLength, data, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidateFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceContext[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceContext";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_QualifierValues)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContextVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_get_QualifierValues(This, value) \
    ((This)->lpVtbl->get_QualifierValues(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceContext2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceContext
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceContext2[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceContext2";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceLoader
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceLoader[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceLoader";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetString)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This,
        HSTRING resourceId,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* GetStringForUri)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* resourceUri,
        HSTRING* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_GetString(This, resourceId, result) \
    ((This)->lpVtbl->GetString(This, resourceId, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_GetStringForUri(This, resourceUri, result) \
    ((This)->lpVtbl->GetStringForUri(This, resourceUri, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceLoaderFactory[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This,
        HSTRING fileName,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader** value);
    HRESULT (STDMETHODCALLTYPE* CreateInstance2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory* This,
        HSTRING fileName,
        HSTRING resourceMap,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoader** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_CreateInstance(This, fileName, value) \
    ((This)->lpVtbl->CreateInstance(This, fileName, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_CreateInstance2(This, fileName, resourceMap, value) \
    ((This)->lpVtbl->CreateInstance2(This, fileName, resourceMap, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceLoaderStatics[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDefaultResourceFilePath)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics* This,
        HSTRING* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_GetDefaultResourceFilePath(This, result) \
    ((This)->lpVtbl->GetDefaultResourceFilePath(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceLoaderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceManager
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceManager[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_MainResourceMap)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap** value);
    HRESULT (STDMETHODCALLTYPE* CreateResourceContext)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext** result);
    HRESULT (STDMETHODCALLTYPE* add_ResourceNotFound)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CApplicationModel__CResources__CResourceManager_Microsoft__CWindows__CApplicationModel__CResources__CResourceNotFoundEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ResourceNotFound)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_get_MainResourceMap(This, value) \
    ((This)->lpVtbl->get_MainResourceMap(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_CreateResourceContext(This, result) \
    ((This)->lpVtbl->CreateResourceContext(This, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_add_ResourceNotFound(This, handler, token) \
    ((This)->lpVtbl->add_ResourceNotFound(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_remove_ResourceNotFound(This, token) \
    ((This)->lpVtbl->remove_ResourceNotFound(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceManager2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceManager2[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceManager2";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceManagerFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceManagerFactory[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceManagerFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory* This,
        HSTRING fileName,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManager** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_CreateInstance(This, fileName, value) \
    ((This)->lpVtbl->CreateInstance(This, fileName, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceManagerFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceMap
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceMap
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceMap[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceMap";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMapVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ResourceCount)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        UINT32* value);
    HRESULT (STDMETHODCALLTYPE* GetSubtree)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING reference,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap** result);
    HRESULT (STDMETHODCALLTYPE* TryGetSubtree)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING reference,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap** result);
    HRESULT (STDMETHODCALLTYPE* GetValue)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING resource,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** result);
    HRESULT (STDMETHODCALLTYPE* GetValueWithContext)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING resource,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* context,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** result);
    HRESULT (STDMETHODCALLTYPE* GetValueByIndex)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        UINT32 index,
        __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate** result);
    HRESULT (STDMETHODCALLTYPE* GetValueByIndexWithContext)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* context,
        __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CApplicationModel__CResources__CResourceCandidate** result);
    HRESULT (STDMETHODCALLTYPE* TryGetValue)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING resource,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** result);
    HRESULT (STDMETHODCALLTYPE* TryGetValueWithContext)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap* This,
        HSTRING resource,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext* context,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMapVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMapVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_get_ResourceCount(This, value) \
    ((This)->lpVtbl->get_ResourceCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetSubtree(This, reference, result) \
    ((This)->lpVtbl->GetSubtree(This, reference, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_TryGetSubtree(This, reference, result) \
    ((This)->lpVtbl->TryGetSubtree(This, reference, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetValue(This, resource, result) \
    ((This)->lpVtbl->GetValue(This, resource, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetValueWithContext(This, resource, context, result) \
    ((This)->lpVtbl->GetValueWithContext(This, resource, context, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetValueByIndex(This, index, result) \
    ((This)->lpVtbl->GetValueByIndex(This, index, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_GetValueByIndexWithContext(This, index, context, result) \
    ((This)->lpVtbl->GetValueByIndexWithContext(This, index, context, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_TryGetValue(This, resource, result) \
    ((This)->lpVtbl->TryGetValue(This, resource, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_TryGetValueWithContext(This, resource, context, result) \
    ((This)->lpVtbl->TryGetValueWithContext(This, resource, context, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceMap_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.Resources.IResourceNotFoundEventArgs
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_Resources_IResourceNotFoundEventArgs[] = L"Microsoft.Windows.ApplicationModel.Resources.IResourceNotFoundEventArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Context)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceContext** value);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* SetResolvedCandidate)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceCandidate* candidate);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_get_Context(This, value) \
    ((This)->lpVtbl->get_Context(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_SetResolvedCandidate(This, candidate) \
    ((This)->lpVtbl->SetResolvedCandidate(This, candidate))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CResources_CIResourceNotFoundEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.KnownResourceQualifierName
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.Resources.IKnownResourceQualifierNameStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_KnownResourceQualifierName_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_KnownResourceQualifierName_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_KnownResourceQualifierName[] = L"Microsoft.Windows.ApplicationModel.Resources.KnownResourceQualifierName";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.Resources.IResourceCandidateFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceCandidate ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceCandidate_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceCandidate_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceCandidate[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceCandidate";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceContext2
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceContext ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceContext[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceContext";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceLoader
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.Resources.IResourceLoaderStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceLoader ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceLoader_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceLoader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceLoader[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceLoader";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceManager
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.Resources.IResourceManagerFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceManager2
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceManager[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceManager";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceMap
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceMap ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceMap_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceMap_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceMap[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceMap";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs
 *
 * Introduced to Microsoft.Windows.ApplicationModel.Resources.MrtCoreContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.Resources.IResourceNotFoundEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceNotFoundEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_Resources_ResourceNotFoundEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_Resources_ResourceNotFoundEventArgs[] = L"Microsoft.Windows.ApplicationModel.Resources.ResourceNotFoundEventArgs";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_RESOURCES_MRTCORECONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eapplicationmodel2Eresources_p_h__

#endif // __microsoft2Ewindows2Eapplicationmodel2Eresources_h__
