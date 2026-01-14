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
#ifndef __microsoft2Ewindows2Emanagement2Edeployment_h__
#define __microsoft2Ewindows2Emanagement2Edeployment_h__
#ifndef __microsoft2Ewindows2Emanagement2Edeployment_p_h__
#define __microsoft2Ewindows2Emanagement2Edeployment_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION 0x20000
#endif // defined(MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION)

#if !defined(WINDOWS_APPLICATIONMODEL_STARTUPTASKCONTRACT_VERSION)
#define WINDOWS_APPLICATIONMODEL_STARTUPTASKCONTRACT_VERSION 0x30000
#endif // defined(WINDOWS_APPLICATIONMODEL_STARTUPTASKCONTRACT_VERSION)

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
#include "Microsoft.Windows.ApplicationModel.DynamicDependency.h"
#include "Windows.ApplicationModel.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IAddPackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions ABI::Microsoft::Windows::Management::Deployment::IAddPackageOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IEnsureReadyOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions ABI::Microsoft::Windows::Management::Deployment::IEnsureReadyOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IEnsureReadyOptions2;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2 ABI::Microsoft::Windows::Management::Deployment::IEnsureReadyOptions2

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageDeploymentManager;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentManager

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageDeploymentManager2;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2 ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentManager2

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageDeploymentManagerStatics;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageDeploymentManagerStatics2;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2 ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentManagerStatics2

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageDeploymentResult;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentResult

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageRuntimeManager;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager ABI::Microsoft::Windows::Management::Deployment::IPackageRuntimeManager

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageRuntimeManagerStatics;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics ABI::Microsoft::Windows::Management::Deployment::IPackageRuntimeManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageSet;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet ABI::Microsoft::Windows::Management::Deployment::IPackageSet

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageSetItem;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem ABI::Microsoft::Windows::Management::Deployment::IPackageSetItem

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageSetItemRuntimeDisposition;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition ABI::Microsoft::Windows::Management::Deployment::IPackageSetItemRuntimeDisposition

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageSetRuntimeDisposition;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition ABI::Microsoft::Windows::Management::Deployment::IPackageSetRuntimeDisposition

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageVolume;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume ABI::Microsoft::Windows::Management::Deployment::IPackageVolume

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IPackageVolumeStatics;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics ABI::Microsoft::Windows::Management::Deployment::IPackageVolumeStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IProvisionPackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions ABI::Microsoft::Windows::Management::Deployment::IProvisionPackageOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IRegisterPackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions ABI::Microsoft::Windows::Management::Deployment::IRegisterPackageOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IRemovePackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions ABI::Microsoft::Windows::Management::Deployment::IRemovePackageOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    interface IStagePackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions ABI::Microsoft::Windows::Management::Deployment::IStagePackageOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageDeploymentResult;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    typedef struct PackageDeploymentProgress PackageDeploymentProgress;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("dba3c316-3afa-51e6-a85f-d1af460495e3"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentResult*>, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.Management.Deployment.PackageDeploymentResult, Microsoft.Windows.Management.Deployment.PackageDeploymentProgress>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("446a127a-02de-5b73-ae01-993d4e6ef729"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentResult*>, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.Management.Deployment.PackageDeploymentResult, Microsoft.Windows.Management.Deployment.PackageDeploymentProgress>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a365d7cc-d85a-507b-aa4a-8cfc2b58cb95"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentResult*>, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.Management.Deployment.PackageDeploymentResult, Microsoft.Windows.Management.Deployment.PackageDeploymentProgress>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentResult*, struct ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageSetItem;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("74086841-814d-5f81-8ea4-0fac86b9ae28"))
IIterator<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Management.Deployment.PackageSetItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t;
#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("45be2e06-b238-53c6-ad96-32558da5e19e"))
IIterable<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Management.Deployment.PackageSetItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t;
#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageSetItemRuntimeDisposition;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("2d49cffd-4c79-5c38-99a0-0336074e91d6"))
IIterator<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItemRuntimeDisposition*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t;
#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("9f0e9c51-ad26-5814-a133-3c2fbd16f391"))
IIterable<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItemRuntimeDisposition*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t;
#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageVolume;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("9d883a1c-5ffa-5699-8327-ef5cd96c0291"))
IIterator<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*, ABI::Microsoft::Windows::Management::Deployment::IPackageVolume*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Management.Deployment.PackageVolume>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t;
#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4b7be9cc-af65-50c9-9679-6dedd2ae9e4d"))
IIterable<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*, ABI::Microsoft::Windows::Management::Deployment::IPackageVolume*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Management.Deployment.PackageVolume>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t;
#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIIterator_1_HSTRING_USE
#define DEF___FIIterator_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8c304ebb-6615-50a4-8829-879ecd443236"))
IIterator<HSTRING> : IIterator_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<HSTRING> __FIIterator_1_HSTRING_t;
#define __FIIterator_1_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_HSTRING_USE */



#ifndef DEF___FIIterable_1_HSTRING_USE
#define DEF___FIIterable_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e2fcc7c1-3bfc-5a0b-b2b0-72e769d1cb7e"))
IIterable<HSTRING> : IIterable_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<HSTRING> __FIIterable_1_HSTRING_t;
#define __FIIterable_1_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_HSTRING_USE */


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

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE
#define DEF___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("f1fe0d5e-8449-5479-875f-17daeb0027f0"))
IKeyValuePair<ABI::Windows::Foundation::Uri*, HSTRING> : IKeyValuePair_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<Windows.Foundation.Uri, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<ABI::Windows::Foundation::Uri*, HSTRING> __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_t;
#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("0c11a982-9f05-557f-b3e8-3737b26830d1"))
IIterator<__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING*> : IIterator_impl<__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<Windows.Foundation.Uri, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING*> __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_t;
#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("52129c53-b03d-59b3-a27e-b0385643e9fe"))
IIterable<__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING*> : IIterable_impl<__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<Windows.Foundation.Uri, String>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING*> __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_t;
#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Windows__CFoundation__CUri_USE
#define DEF___FIIterator_1_Windows__CFoundation__CUri_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("1c157d0f-5efe-5cec-bbd6-0c6ce9af07a5"))
IIterator<ABI::Windows::Foundation::Uri*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Uri>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Windows::Foundation::Uri*> __FIIterator_1_Windows__CFoundation__CUri_t;
#define __FIIterator_1_Windows__CFoundation__CUri ABI::Windows::Foundation::Collections::__FIIterator_1_Windows__CFoundation__CUri_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Windows__CFoundation__CUri_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Windows__CFoundation__CUri_USE
#define DEF___FIIterable_1_Windows__CFoundation__CUri_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b0d63b78-78ad-5e31-b6d8-e32a0e16c447"))
IIterable<ABI::Windows::Foundation::Uri*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Uri>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Windows::Foundation::Uri*> __FIIterable_1_Windows__CFoundation__CUri_t;
#define __FIIterable_1_Windows__CFoundation__CUri ABI::Windows::Foundation::Collections::__FIIterable_1_Windows__CFoundation__CUri_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Windows__CFoundation__CUri_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIMapView_2_Windows__CFoundation__CUri_HSTRING_USE
#define DEF___FIMapView_2_Windows__CFoundation__CUri_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("87530605-8bd4-5f0a-85f1-751e8bd20446"))
IMapView<ABI::Windows::Foundation::Uri*, HSTRING> : IMapView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<Windows.Foundation.Uri, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<ABI::Windows::Foundation::Uri*, HSTRING> __FIMapView_2_Windows__CFoundation__CUri_HSTRING_t;
#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING ABI::Windows::Foundation::Collections::__FIMapView_2_Windows__CFoundation__CUri_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_Windows__CFoundation__CUri_HSTRING_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIMap_2_Windows__CFoundation__CUri_HSTRING_USE
#define DEF___FIMap_2_Windows__CFoundation__CUri_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4c522071-01da-5f85-9d52-29952578a301"))
IMap<ABI::Windows::Foundation::Uri*, HSTRING> : IMap_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>, HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMap`2<Windows.Foundation.Uri, String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMap<ABI::Windows::Foundation::Uri*, HSTRING> __FIMap_2_Windows__CFoundation__CUri_HSTRING_t;
#define __FIMap_2_Windows__CFoundation__CUri_HSTRING ABI::Windows::Foundation::Collections::__FIMap_2_Windows__CFoundation__CUri_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMap_2_Windows__CFoundation__CUri_HSTRING_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("8a350fa7-ca4b-57dc-9772-e824e3156aa7"))
IVectorView<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Management.Deployment.PackageSetItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t;
#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c9fc469d-dd12-593c-b554-8aad5d1c6c45"))
IVectorView<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItemRuntimeDisposition*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t;
#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5368a870-6748-50bd-b2bd-e401ebb50bd8"))
IVectorView<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*, ABI::Microsoft::Windows::Management::Deployment::IPackageVolume*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Management.Deployment.PackageVolume>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t;
#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIVectorView_1_HSTRING_USE
#define DEF___FIVectorView_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("2f13c006-a03a-5f69-b090-75a43e33423e"))
IVectorView<HSTRING> : IVectorView_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<HSTRING> __FIVectorView_1_HSTRING_t;
#define __FIVectorView_1_HSTRING ABI::Windows::Foundation::Collections::__FIVectorView_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_HSTRING_USE */


#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Windows__CFoundation__CUri_USE
#define DEF___FIVectorView_1_Windows__CFoundation__CUri_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("4b8385bd-a2cd-5ff1-bf74-7ea580423e50"))
IVectorView<ABI::Windows::Foundation::Uri*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Windows.Foundation.Uri>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Windows::Foundation::Uri*> __FIVectorView_1_Windows__CFoundation__CUri_t;
#define __FIVectorView_1_Windows__CFoundation__CUri ABI::Windows::Foundation::Collections::__FIVectorView_1_Windows__CFoundation__CUri_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Windows__CFoundation__CUri_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#define DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("1a149ede-06c9-5179-aebc-42f8aefcd854"))
IVector<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItem*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.Windows.Management.Deployment.PackageSetItem>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::Windows::Management::Deployment::PackageSetItem*> __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t;
#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#define DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("27772c5b-2d44-5594-acd9-818907ab582c"))
IVector<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*, ABI::Microsoft::Windows::Management::Deployment::IPackageSetItemRuntimeDisposition*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition*> __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t;
#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#define DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("2662562c-57ff-5dc0-af01-0e484793c9cc"))
IVector<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*, ABI::Microsoft::Windows::Management::Deployment::IPackageVolume*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.Windows.Management.Deployment.PackageVolume>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Microsoft::Windows::Management::Deployment::PackageVolume*> __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t;
#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_USE */

#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIVector_1_HSTRING_USE
#define DEF___FIVector_1_HSTRING_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("98b9acc1-4b56-532e-ac73-03d5291cca90"))
IVector<HSTRING> : IVector_impl<HSTRING>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<String>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<HSTRING> __FIVector_1_HSTRING_t;
#define __FIVector_1_HSTRING ABI::Windows::Foundation::Collections::__FIVector_1_HSTRING_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_HSTRING_USE */


#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Windows__CFoundation__CUri_USE
#define DEF___FIVector_1_Windows__CFoundation__CUri_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("0d82bd8d-fe62-5d67-a7b9-7886dd75bc4e"))
IVector<ABI::Windows::Foundation::Uri*> : IVector_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Windows::Foundation::Uri*, ABI::Windows::Foundation::IUriRuntimeClass*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Windows.Foundation.Uri>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Windows::Foundation::Uri*> __FIVector_1_Windows__CFoundation__CUri_t;
#define __FIVector_1_Windows__CFoundation__CUri ABI::Windows::Foundation::Collections::__FIVector_1_Windows__CFoundation__CUri_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Windows__CFoundation__CUri_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    class AddPackageDependencyOptions;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IAddPackageDependencyOptions;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IAddPackageDependencyOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    class CreatePackageDependencyOptions;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface ICreatePackageDependencyOptions;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::ICreatePackageDependencyOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    typedef struct PackageDependencyContextId PackageDependencyContextId;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    typedef enum PackageDependencyProcessorArchitectures : unsigned int PackageDependencyProcessorArchitectures;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace ApplicationModel {
            typedef struct PackageVersion PackageVersion;
        } /* ApplicationModel */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    typedef enum PackageDeploymentFeature : int PackageDeploymentFeature;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    typedef enum PackageDeploymentProgressStatus : int PackageDeploymentProgressStatus;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    typedef enum PackageDeploymentStatus : int PackageDeploymentStatus;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    typedef enum PackageReadyOrNewerAvailableStatus : int PackageReadyOrNewerAvailableStatus;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    typedef enum StubPackageOption : int StubPackageOption;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class AddPackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class EnsureReadyOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageDeploymentManager;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageRuntimeManager;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageSet;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class PackageSetRuntimeDisposition;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class ProvisionPackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class RegisterPackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class RemovePackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    class StagePackageOptions;
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentFeature
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    enum PackageDeploymentFeature : int
                    {
                        PackageDeploymentFeature_PackageUriScheme_ms_uup = 1,
                        PackageDeploymentFeature_IsPackageReadyOrNewerAvailable = 2,
                        PackageDeploymentFeature_RemovePackageByUri = 3,
                        PackageDeploymentFeature_ResetPackage = 4,
                        PackageDeploymentFeature_RepairPackage = 5,
                        PackageDeploymentFeature_ProvisionPackage_Framework = 6,
                    };
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentProgressStatus
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    enum PackageDeploymentProgressStatus : int
                    {
                        PackageDeploymentProgressStatus_Queued = 0,
                        PackageDeploymentProgressStatus_InProgress = 1,
                        PackageDeploymentProgressStatus_CompletedSuccess = 2,
                        PackageDeploymentProgressStatus_CompletedFailure = 3,
                    };
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentStatus
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    enum PackageDeploymentStatus : int
                    {
                        PackageDeploymentStatus_InProgress = 0,
                        PackageDeploymentStatus_CompletedSuccess = 1,
                        PackageDeploymentStatus_CompletedFailure = 2,
                    };
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageReadyOrNewerAvailableStatus
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    enum PackageReadyOrNewerAvailableStatus : int
                    {
                        PackageReadyOrNewerAvailableStatus_NotReady = 0,
                        PackageReadyOrNewerAvailableStatus_Ready = 1,
                        PackageReadyOrNewerAvailableStatus_NewerAvailable = 2,
                    };
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.StubPackageOption
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    enum StubPackageOption : int
                    {
                        StubPackageOption_Default = 0,
                        StubPackageOption_InstallFull = 1,
                        StubPackageOption_InstallStub = 2,
                        StubPackageOption_UsePreference = 3,
                    };
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentProgress
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    struct PackageDeploymentProgress
                    {
                        ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentProgressStatus Status;
                        DOUBLE Progress;
                    };
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IAddPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.AddPackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IAddPackageOptions[] = L"Microsoft.Windows.Management.Deployment.IAddPackageOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("e3db7f39-f9d0-5884-bdef-6153b54574a3")
                    IAddPackageOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TargetVolume(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TargetVolume(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DependencyPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OptionalPackageFamilyNames(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OptionalPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RelatedPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExternalLocationUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExternalLocationUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StubPackageOption(
                            ABI::Microsoft::Windows::Management::Deployment::StubPackageOption* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_StubPackageOption(
                            ABI::Microsoft::Windows::Management::Deployment::StubPackageOption value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AllowUnsigned(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowUnsigned(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeveloperMode(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DeveloperMode(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceAppShutdown(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceAppShutdown(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceTargetAppShutdown(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceTargetAppShutdown(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceUpdateFromAnyVersion(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceUpdateFromAnyVersion(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InstallAllResources(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_InstallAllResources(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RequiredContentGroupOnly(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RequiredContentGroupOnly(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RetainFilesOnFailure(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RetainFilesOnFailure(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StageInPlace(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_StageInPlace(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeferRegistrationWhenPackagesAreInUse(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DeferRegistrationWhenPackagesAreInUse(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsExpectedDigestsSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpectedDigests(
                            __FIMap_2_Windows__CFoundation__CUri_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsLimitToExistingPackagesSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LimitToExistingPackages(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LimitToExistingPackages(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAddPackageOptions = _uuidof(IAddPackageOptions);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IEnsureReadyOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.EnsureReadyOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IEnsureReadyOptions[] = L"Microsoft.Windows.Management.Deployment.IEnsureReadyOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("20102d03-ec44-5c2b-8fd6-1104dc99755d")
                    IEnsureReadyOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AddPackageOptions(
                            ABI::Microsoft::Windows::Management::Deployment::IAddPackageOptions** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IEnsureReadyOptions = _uuidof(IEnsureReadyOptions);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IEnsureReadyOptions2
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.EnsureReadyOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IEnsureReadyOptions2[] = L"Microsoft.Windows.Management.Deployment.IEnsureReadyOptions2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("eefa9259-b13a-50a3-919e-ae116d83c0da")
                    IEnsureReadyOptions2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RegisterNewerIfAvailable(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RegisterNewerIfAvailable(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IEnsureReadyOptions2 = _uuidof(IEnsureReadyOptions2);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManager[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("f41717d8-5ab2-57ac-83cd-d0c48cc784cd")
                    IPackageDeploymentManager : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsPackageReady(
                            HSTRING package,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageReadyByUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageSetReady(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsurePackageReadyAsync(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::IEnsureReadyOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsurePackageReadyByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::IEnsureReadyOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE EnsurePackageSetReadyAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IEnsureReadyOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddPackageAsync(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::IAddPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddPackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::IAddPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddPackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IAddPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StagePackageAsync(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::IStagePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StagePackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::IStagePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StagePackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IStagePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RegisterPackageAsync(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::IRegisterPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RegisterPackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::IRegisterPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RegisterPackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IRegisterPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemovePackageAsync(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::IRemovePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemovePackageByFullNameAsync(
                            HSTRING packageFullName,
                            ABI::Microsoft::Windows::Management::Deployment::IRemovePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemovePackageByFamilyNameAsync(
                            HSTRING packageFamilyName,
                            ABI::Microsoft::Windows::Management::Deployment::IRemovePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemovePackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::IRemovePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemovePackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IRemovePackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ResetPackageAsync(
                            HSTRING package,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ResetPackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ResetPackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RepairPackageAsync(
                            HSTRING package,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RepairPackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RepairPackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ProvisionPackageAsync(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::IProvisionPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ProvisionPackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::IProvisionPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ProvisionPackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IProvisionPackageOptions* options,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DeprovisionPackageAsync(
                            HSTRING package,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DeprovisionPackageByUriAsync(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DeprovisionPackageSetAsync(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageRegistrationPending(
                            HSTRING packageFamilyName,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageRegistrationPendingForUser(
                            HSTRING userSecurityId,
                            HSTRING packageFamilyName,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDeploymentManager = _uuidof(IPackageDeploymentManager);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManager2
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManager2[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManager2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("6fc6d0f3-f9dd-5c14-9d3f-077165eddf98")
                    IPackageDeploymentManager2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsPackageReadyOrNewerAvailable(
                            HSTRING package,
                            ABI::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageReadyOrNewerAvailableByUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            ABI::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageSetReadyOrNewerAvailable(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageProvisioned(
                            HSTRING package,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageProvisionedByUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* packageUri,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsPackageSetProvisioned(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDeploymentManager2 = _uuidof(IPackageDeploymentManager2);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManagerStatics[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("dbda4ac6-ca28-59b8-9fc6-dbfb5765f1c2")
                    IPackageDeploymentManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetDefault(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageDeploymentManager** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDeploymentManagerStatics = _uuidof(IPackageDeploymentManagerStatics);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics2
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManagerStatics2[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("0ec31486-00b5-5937-8cd4-759260fdc4a2")
                    IPackageDeploymentManagerStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE IsPackageDeploymentFeatureSupported(
                            ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature feature,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDeploymentManagerStatics2 = _uuidof(IPackageDeploymentManagerStatics2);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentResult
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentResult
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentResult[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("d6b99601-18c2-599e-8bd1-40a9310ad263")
                    IPackageDeploymentResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Error(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorText(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ActivityId(
                            GUID* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDeploymentResult = _uuidof(IPackageDeploymentResult);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageRuntimeManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageRuntimeManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageRuntimeManager[] = L"Microsoft.Windows.Management.Deployment.IPackageRuntimeManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("6bf0fd29-6c2a-58d1-af0c-abd2eac45e29")
                    IPackageRuntimeManager : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE AddPackageSet(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSetRuntimeDisposition** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddPackageSetWithOptions(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSet* packageSet,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::ICreatePackageDependencyOptions* createOptions,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IAddPackageDependencyOptions* addOptions,
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSetRuntimeDisposition** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemovePackageSet(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageSetRuntimeDisposition* packageSetRuntimeDisposition
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageRuntimeManager = _uuidof(IPackageRuntimeManager);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageRuntimeManagerStatics
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageRuntimeManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageRuntimeManagerStatics[] = L"Microsoft.Windows.Management.Deployment.IPackageRuntimeManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("790947de-01d4-5858-aa69-9c9390fb7d3e")
                    IPackageRuntimeManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetDefault(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageRuntimeManager** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageRuntimeManagerStatics = _uuidof(IPackageRuntimeManagerStatics);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSet
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSet
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSet[] = L"Microsoft.Windows.Management.Deployment.IPackageSet";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("229fdf93-8529-5f8d-988c-af8a39ad46f7")
                    IPackageSet : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Id(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Id(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PackageUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Items(
                            __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageSet = _uuidof(IPackageSet);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSetItem
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSetItem
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSetItem[] = L"Microsoft.Windows.Management.Deployment.IPackageSetItem";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("8f254e15-c371-550f-b4e8-3f0bb1ae375f")
                    IPackageSetItem : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Id(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Id(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageFamilyName(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PackageFamilyName(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MinVersion(
                            ABI::Windows::ApplicationModel::PackageVersion* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MinVersion(
                            ABI::Windows::ApplicationModel::PackageVersion value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ProcessorArchitectureFilter(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ProcessorArchitectureFilter(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PackageUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageSetItem = _uuidof(IPackageSetItem);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSetItemRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSetItemRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.IPackageSetItemRuntimeDisposition";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("7a7f9f70-d416-5f83-a3cd-027bf3d2abfd")
                    IPackageSetItemRuntimeDisposition : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PackageSetItemId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageFullName(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageDependencyId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageDependencyContextId(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageSetItemRuntimeDisposition = _uuidof(IPackageSetItemRuntimeDisposition);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSetRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSetRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.IPackageSetRuntimeDisposition";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("c13f1088-ea36-5db3-bcdd-e6d59e6c9b71")
                    IPackageSetRuntimeDisposition : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PackageSetId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PackageSetId(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageSetItemRuntimeDispositions(
                            __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageSetRuntimeDisposition = _uuidof(IPackageSetRuntimeDisposition);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageVolume
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageVolume
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageVolume[] = L"Microsoft.Windows.Management.Deployment.IPackageVolume";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("9c9710f4-795a-58b3-93f4-c991c4329c49")
                    IPackageVolume : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsSystemVolume(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MountPoint(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Name(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageStorePath(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SupportsHardLinks(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsFullTrustPackageSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsAppxInstallSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsRepairNeeded(
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Repair(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageVolume = _uuidof(IPackageVolume);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageVolumeStatics
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageVolume
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageVolumeStatics[] = L"Microsoft.Windows.Management.Deployment.IPackageVolumeStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("4c731835-8bc0-5313-9b56-8a4100eaea01")
                    IPackageVolumeStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE FindPackageVolumes(
                            __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindPackageVolumeByPath(
                            HSTRING packageStorePath,
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE FindPackageVolumeByName(
                            HSTRING name,
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageVolumeStatics = _uuidof(IPackageVolumeStatics);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IProvisionPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.ProvisionPackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IProvisionPackageOptions[] = L"Microsoft.Windows.Management.Deployment.IProvisionPackageOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("415e300f-d1e3-581e-a114-76d277b06136")
                    IProvisionPackageOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsOptionalPackageFamilyNamesSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OptionalPackageFamilyNames(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsProjectionOrderPackageFamilyNamesSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ProjectionOrderPackageFamilyNames(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IProvisionPackageOptions = _uuidof(IProvisionPackageOptions);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IRegisterPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.RegisterPackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IRegisterPackageOptions[] = L"Microsoft.Windows.Management.Deployment.IRegisterPackageOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("83068623-2046-505f-8425-55226c0f84cc")
                    IRegisterPackageOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AppDataVolume(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AppDataVolume(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DependencyPackageFamilyNames(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DependencyPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OptionalPackageFamilyNames(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExternalLocationUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExternalLocationUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AllowUnsigned(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowUnsigned(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeveloperMode(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DeveloperMode(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceAppShutdown(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceAppShutdown(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceTargetAppShutdown(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceTargetAppShutdown(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceUpdateFromAnyVersion(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceUpdateFromAnyVersion(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InstallAllResources(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_InstallAllResources(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StageInPlace(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_StageInPlace(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeferRegistrationWhenPackagesAreInUse(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DeferRegistrationWhenPackagesAreInUse(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsExpectedDigestsSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpectedDigests(
                            __FIMap_2_Windows__CFoundation__CUri_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRegisterPackageOptions = _uuidof(IRegisterPackageOptions);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IRemovePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.RemovePackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IRemovePackageOptions[] = L"Microsoft.Windows.Management.Deployment.IRemovePackageOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("e7c90595-9a44-5046-8ebf-41ed326b200e")
                    IRemovePackageOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_FailIfNotFound(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_FailIfNotFound(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PreserveApplicationData(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PreserveApplicationData(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PreserveRoamableApplicationData(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PreserveRoamableApplicationData(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RemoveForAllUsers(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RemoveForAllUsers(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRemovePackageOptions = _uuidof(IRemovePackageOptions);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IStagePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.StagePackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IStagePackageOptions[] = L"Microsoft.Windows.Management.Deployment.IStagePackageOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Management {
                namespace Deployment {
                    MIDL_INTERFACE("9b6b3203-fd7c-5ead-a9d6-ab2e8566be5e")
                    IStagePackageOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TargetVolume(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TargetVolume(
                            ABI::Microsoft::Windows::Management::Deployment::IPackageVolume* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DependencyPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OptionalPackageFamilyNames(
                            __FIVector_1_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_OptionalPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RelatedPackageUris(
                            __FIVector_1_Windows__CFoundation__CUri** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExternalLocationUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ExternalLocationUri(
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StubPackageOption(
                            ABI::Microsoft::Windows::Management::Deployment::StubPackageOption* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_StubPackageOption(
                            ABI::Microsoft::Windows::Management::Deployment::StubPackageOption value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeveloperMode(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DeveloperMode(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ForceUpdateFromAnyVersion(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceUpdateFromAnyVersion(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InstallAllResources(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_InstallAllResources(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RequiredContentGroupOnly(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_RequiredContentGroupOnly(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StageInPlace(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_StageInPlace(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AllowUnsigned(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowUnsigned(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsExpectedDigestsSupported(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExpectedDigests(
                            __FIMap_2_Windows__CFoundation__CUri_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IStagePackageOptions = _uuidof(IStagePackageOptions);
                } /* Deployment */
            } /* Management */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.AddPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IAddPackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_AddPackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_AddPackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_AddPackageOptions[] = L"Microsoft.Windows.Management.Deployment.AddPackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.EnsureReadyOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IEnsureReadyOptions ** Default Interface **
 *    Microsoft.Windows.Management.Deployment.IEnsureReadyOptions2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_EnsureReadyOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_EnsureReadyOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_EnsureReadyOptions[] = L"Microsoft.Windows.Management.Deployment.EnsureReadyOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics interface starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageDeploymentManager ** Default Interface **
 *    Microsoft.Windows.Management.Deployment.IPackageDeploymentManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageDeploymentManager[] = L"Microsoft.Windows.Management.Deployment.PackageDeploymentManager";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageDeploymentResult
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageDeploymentResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageDeploymentResult[] = L"Microsoft.Windows.Management.Deployment.PackageDeploymentResult";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageRuntimeManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageRuntimeManagerStatics interface starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageRuntimeManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageRuntimeManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageRuntimeManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageRuntimeManager[] = L"Microsoft.Windows.Management.Deployment.PackageRuntimeManager";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSet
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSet ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSet_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSet_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSet[] = L"Microsoft.Windows.Management.Deployment.PackageSet";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSetItem
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSetItem ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItem_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSetItem[] = L"Microsoft.Windows.Management.Deployment.PackageSetItem";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSetItemRuntimeDisposition ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItemRuntimeDisposition_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItemRuntimeDisposition_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSetItemRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSetRuntimeDisposition ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetRuntimeDisposition_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetRuntimeDisposition_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSetRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageVolume
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageVolumeStatics interface starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageVolume ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageVolume_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageVolume_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageVolume[] = L"Microsoft.Windows.Management.Deployment.PackageVolume";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.ProvisionPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IProvisionPackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_ProvisionPackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_ProvisionPackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_ProvisionPackageOptions[] = L"Microsoft.Windows.Management.Deployment.ProvisionPackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.RegisterPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IRegisterPackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RegisterPackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RegisterPackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_RegisterPackageOptions[] = L"Microsoft.Windows.Management.Deployment.RegisterPackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.RemovePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IRemovePackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RemovePackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RemovePackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_RemovePackageOptions[] = L"Microsoft.Windows.Management.Deployment.RemovePackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.StagePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IStagePackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_StagePackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_StagePackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_StagePackageOptions[] = L"Microsoft.Windows.Management.Deployment.StagePackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2 __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2 __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2 __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgress __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgress;

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress* asyncInfo,
        struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgress progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgressVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

typedef struct __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl;

interface __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

typedef struct __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl;

interface __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

typedef struct __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl;

interface __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

typedef struct __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl;

interface __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

typedef struct __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl;

interface __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

typedef struct __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        __FIIterator_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl;

interface __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if !defined(____FIIterator_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1_HSTRING __FIIterator_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_HSTRING;

typedef struct __FIIterator_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_HSTRING* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_HSTRING* This,
        UINT32 itemsLength,
        HSTRING* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_HSTRINGVtbl;

interface __FIIterator_1_HSTRING
{
    CONST_VTBL struct __FIIterator_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_HSTRING_INTERFACE_DEFINED__

#if !defined(____FIIterable_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1_HSTRING __FIIterable_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_HSTRING;

typedef struct __FIIterable_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_HSTRING* This,
        __FIIterator_1_HSTRING** result);

    END_INTERFACE
} __FIIterable_1_HSTRINGVtbl;

interface __FIIterable_1_HSTRING
{
    CONST_VTBL struct __FIIterable_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_HSTRING_INTERFACE_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING;

typedef struct __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        HSTRING* result);

    END_INTERFACE
} __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl;

interface __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING
{
    CONST_VTBL struct __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING;

typedef struct __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl;

interface __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING;

typedef struct __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING* This,
        __FIIterator_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl;

interface __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__)
#define ____FIIterator_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Windows__CFoundation__CUri __FIIterator_1_Windows__CFoundation__CUri;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Windows__CFoundation__CUri;

typedef struct __FIIterator_1_Windows__CFoundation__CUriVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Windows__CFoundation__CUri* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Windows__CFoundation__CUri* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Windows__CFoundation__CUri* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Windows__CFoundation__CUri* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Windows__CFoundation__CUri* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Windows__CFoundation__CUri* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Windows__CFoundation__CUri* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Windows__CFoundation__CUri* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Windows__CFoundation__CUri* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Windows__CFoundation__CUri* This,
        UINT32 itemsLength,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Windows__CFoundation__CUriVtbl;

interface __FIIterator_1_Windows__CFoundation__CUri
{
    CONST_VTBL struct __FIIterator_1_Windows__CFoundation__CUriVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Windows__CFoundation__CUri_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Windows__CFoundation__CUri_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Windows__CFoundation__CUri_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Windows__CFoundation__CUri_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Windows__CFoundation__CUri_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Windows__CFoundation__CUri_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Windows__CFoundation__CUri_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Windows__CFoundation__CUri_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Windows__CFoundation__CUri_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Windows__CFoundation__CUri_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__)
#define ____FIIterable_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Windows__CFoundation__CUri __FIIterable_1_Windows__CFoundation__CUri;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Windows__CFoundation__CUri;

typedef struct __FIIterable_1_Windows__CFoundation__CUriVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Windows__CFoundation__CUri* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Windows__CFoundation__CUri* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Windows__CFoundation__CUri* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Windows__CFoundation__CUri* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Windows__CFoundation__CUri* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Windows__CFoundation__CUri* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Windows__CFoundation__CUri* This,
        __FIIterator_1_Windows__CFoundation__CUri** result);

    END_INTERFACE
} __FIIterable_1_Windows__CFoundation__CUriVtbl;

interface __FIIterable_1_Windows__CFoundation__CUri
{
    CONST_VTBL struct __FIIterable_1_Windows__CFoundation__CUriVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Windows__CFoundation__CUri_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Windows__CFoundation__CUri_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Windows__CFoundation__CUri_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Windows__CFoundation__CUri_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Windows__CFoundation__CUri_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Windows__CFoundation__CUri_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Windows__CFoundation__CUri_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

typedef interface __FIMapView_2_Windows__CFoundation__CUri_HSTRING __FIMapView_2_Windows__CFoundation__CUri_HSTRING;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIMapView_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__)
#define ____FIMapView_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMapView_2_Windows__CFoundation__CUri_HSTRING __FIMapView_2_Windows__CFoundation__CUri_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_Windows__CFoundation__CUri_HSTRING;

typedef struct __FIMapView_2_Windows__CFoundation__CUri_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_Windows__CFoundation__CUri_HSTRING* This,
        __FIMapView_2_Windows__CFoundation__CUri_HSTRING** first,
        __FIMapView_2_Windows__CFoundation__CUri_HSTRING** second);

    END_INTERFACE
} __FIMapView_2_Windows__CFoundation__CUri_HSTRINGVtbl;

interface __FIMapView_2_Windows__CFoundation__CUri_HSTRING
{
    CONST_VTBL struct __FIMapView_2_Windows__CFoundation__CUri_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_Windows__CFoundation__CUri_HSTRING_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIMap_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__)
#define ____FIMap_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__

typedef interface __FIMap_2_Windows__CFoundation__CUri_HSTRING __FIMap_2_Windows__CFoundation__CUri_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMap_2_Windows__CFoundation__CUri_HSTRING;

typedef struct __FIMap_2_Windows__CFoundation__CUri_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* key,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        __FIMapView_2_Windows__CFoundation__CUri_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* Insert)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* key,
        HSTRING value,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Remove)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* key);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIMap_2_Windows__CFoundation__CUri_HSTRING* This);

    END_INTERFACE
} __FIMap_2_Windows__CFoundation__CUri_HSTRINGVtbl;

interface __FIMap_2_Windows__CFoundation__CUri_HSTRING
{
    CONST_VTBL struct __FIMap_2_Windows__CFoundation__CUri_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_Insert(This, key, value, result) \
    ((This)->lpVtbl->Insert(This, key, value, result))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_Remove(This, key) \
    ((This)->lpVtbl->Remove(This, key))

#define __FIMap_2_Windows__CFoundation__CUri_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#endif /* COBJMACROS */

#endif // ____FIMap_2_Windows__CFoundation__CUri_HSTRING_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

typedef struct __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

typedef struct __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

typedef struct __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if !defined(____FIVectorView_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIVectorView_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_HSTRING __FIVectorView_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_HSTRING;

typedef struct __FIVectorView_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_HSTRING* This,
        UINT32 index,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_HSTRING* This,
        HSTRING value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_HSTRING* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        HSTRING* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_HSTRINGVtbl;

interface __FIVectorView_1_HSTRING
{
    CONST_VTBL struct __FIVectorView_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_HSTRING_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_HSTRING_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_HSTRING_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_HSTRING_INTERFACE_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Windows__CFoundation__CUri __FIVectorView_1_Windows__CFoundation__CUri;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Windows__CFoundation__CUri;

typedef struct __FIVectorView_1_Windows__CFoundation__CUriVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Windows__CFoundation__CUri* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Windows__CFoundation__CUri* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        UINT32 index,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Windows__CFoundation__CUri* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Windows__CFoundation__CUriVtbl;

interface __FIVectorView_1_Windows__CFoundation__CUri
{
    CONST_VTBL struct __FIVectorView_1_Windows__CFoundation__CUriVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Windows__CFoundation__CUri_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Windows__CFoundation__CUri_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Windows__CFoundation__CUri_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Windows__CFoundation__CUri_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Windows__CFoundation__CUri_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Windows__CFoundation__CUri_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Windows__CFoundation__CUri_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Windows__CFoundation__CUri_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Windows__CFoundation__CUri_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Windows__CFoundation__CUri_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem;

typedef struct __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl;

interface __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem
{
    CONST_VTBL struct __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition;

typedef struct __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl;

interface __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition
{
    CONST_VTBL struct __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDispositionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume;

typedef struct __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        __FIVectorView_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** items);

    END_INTERFACE
} __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl;

interface __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume
{
    CONST_VTBL struct __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolumeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#if !defined(____FIVector_1_HSTRING_INTERFACE_DEFINED__)
#define ____FIVector_1_HSTRING_INTERFACE_DEFINED__

typedef interface __FIVector_1_HSTRING __FIVector_1_HSTRING;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_HSTRING;

typedef struct __FIVector_1_HSTRINGVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_HSTRING* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_HSTRING* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_HSTRING* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_HSTRING* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_HSTRING* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_HSTRING* This,
        UINT32 index,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_HSTRING* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_HSTRING* This,
        __FIVectorView_1_HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_HSTRING* This,
        HSTRING value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_HSTRING* This,
        UINT32 index,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_HSTRING* This,
        UINT32 index,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_HSTRING* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_HSTRING* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_HSTRING* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_HSTRING* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        HSTRING* items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_HSTRING* This,
        UINT32 itemsLength,
        HSTRING* items);

    END_INTERFACE
} __FIVector_1_HSTRINGVtbl;

interface __FIVector_1_HSTRING
{
    CONST_VTBL struct __FIVector_1_HSTRINGVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_HSTRING_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_HSTRING_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_HSTRING_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_HSTRING_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_HSTRING_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_HSTRING_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_HSTRING_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_HSTRING_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_HSTRING_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_HSTRING_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_HSTRING_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_HSTRING_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_HSTRING_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_HSTRING_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_HSTRING_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_HSTRING_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_HSTRING_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_HSTRING_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_HSTRING_INTERFACE_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__)
#define ____FIVector_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__

typedef interface __FIVector_1_Windows__CFoundation__CUri __FIVector_1_Windows__CFoundation__CUri;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Windows__CFoundation__CUri;

typedef struct __FIVector_1_Windows__CFoundation__CUriVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Windows__CFoundation__CUri* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Windows__CFoundation__CUri* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Windows__CFoundation__CUri* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Windows__CFoundation__CUri* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Windows__CFoundation__CUri* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Windows__CFoundation__CUri* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32 index,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Windows__CFoundation__CUri* This,
        __FIVectorView_1_Windows__CFoundation__CUri** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Windows__CFoundation__CUri* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32 index,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32 index,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Windows__CFoundation__CUri* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Windows__CFoundation__CUri* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Windows__CFoundation__CUri* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Windows__CFoundation__CUri* This,
        UINT32 itemsLength,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** items);

    END_INTERFACE
} __FIVector_1_Windows__CFoundation__CUriVtbl;

interface __FIVector_1_Windows__CFoundation__CUri
{
    CONST_VTBL struct __FIVector_1_Windows__CFoundation__CUriVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Windows__CFoundation__CUri_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Windows__CFoundation__CUri_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Windows__CFoundation__CUri_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Windows__CFoundation__CUri_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Windows__CFoundation__CUri_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Windows__CFoundation__CUri_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Windows__CFoundation__CUri_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Windows__CFoundation__CUri_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Windows__CFoundation__CUri_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Windows__CFoundation__CUri_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Windows__CFoundation__CUri_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Windows__CFoundation__CUri_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Windows__CFoundation__CUri_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Windows__CFoundation__CUri_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Windows__CFoundation__CUri_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Windows__CFoundation__CUri_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Windows__CFoundation__CUri_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Windows__CFoundation__CUri_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Windows__CFoundation__CUri_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId;

typedef enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures;

typedef struct __x_ABI_CWindows_CApplicationModel_CPackageVersion __x_ABI_CWindows_CApplicationModel_CPackageVersion;

typedef enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentFeature __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentFeature;

typedef enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgressStatus __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgressStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentStatus __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageReadyOrNewerAvailableStatus __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageReadyOrNewerAvailableStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption;

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentFeature
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentFeature
{
    PackageDeploymentFeature_PackageUriScheme_ms_uup = 1,
    PackageDeploymentFeature_IsPackageReadyOrNewerAvailable = 2,
    PackageDeploymentFeature_RemovePackageByUri = 3,
    PackageDeploymentFeature_ResetPackage = 4,
    PackageDeploymentFeature_RepairPackage = 5,
    PackageDeploymentFeature_ProvisionPackage_Framework = 6,
};
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentProgressStatus
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgressStatus
{
    PackageDeploymentProgressStatus_Queued = 0,
    PackageDeploymentProgressStatus_InProgress = 1,
    PackageDeploymentProgressStatus_CompletedSuccess = 2,
    PackageDeploymentProgressStatus_CompletedFailure = 3,
};
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentStatus
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentStatus
{
    PackageDeploymentStatus_InProgress = 0,
    PackageDeploymentStatus_CompletedSuccess = 1,
    PackageDeploymentStatus_CompletedFailure = 2,
};
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageReadyOrNewerAvailableStatus
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageReadyOrNewerAvailableStatus
{
    PackageReadyOrNewerAvailableStatus_NotReady = 0,
    PackageReadyOrNewerAvailableStatus_Ready = 1,
    PackageReadyOrNewerAvailableStatus_NewerAvailable = 2,
};
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.StubPackageOption
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption
{
    StubPackageOption_Default = 0,
    StubPackageOption_InstallFull = 1,
    StubPackageOption_InstallStub = 2,
    StubPackageOption_UsePreference = 3,
};
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Management.Deployment.PackageDeploymentProgress
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgress
{
    enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentProgressStatus Status;
    DOUBLE Progress;
};
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IAddPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.AddPackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IAddPackageOptions[] = L"Microsoft.Windows.Management.Deployment.IAddPackageOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TargetVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** value);
    HRESULT (STDMETHODCALLTYPE* put_TargetVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value);
    HRESULT (STDMETHODCALLTYPE* get_DependencyPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_OptionalPackageFamilyNames)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_OptionalPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_RelatedPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_ExternalLocationUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_ExternalLocationUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_StubPackageOption)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption* value);
    HRESULT (STDMETHODCALLTYPE* put_StubPackageOption)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption value);
    HRESULT (STDMETHODCALLTYPE* get_AllowUnsigned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowUnsigned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_DeveloperMode)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_DeveloperMode)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceTargetAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceTargetAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceUpdateFromAnyVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceUpdateFromAnyVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_InstallAllResources)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_InstallAllResources)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_RequiredContentGroupOnly)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_RequiredContentGroupOnly)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_RetainFilesOnFailure)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_RetainFilesOnFailure)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StageInPlace)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_StageInPlace)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_DeferRegistrationWhenPackagesAreInUse)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_DeferRegistrationWhenPackagesAreInUse)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsExpectedDigestsSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ExpectedDigests)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        __FIMap_2_Windows__CFoundation__CUri_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_IsLimitToExistingPackagesSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_LimitToExistingPackages)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_LimitToExistingPackages)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_TargetVolume(This, value) \
    ((This)->lpVtbl->get_TargetVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_TargetVolume(This, value) \
    ((This)->lpVtbl->put_TargetVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_DependencyPackageUris(This, value) \
    ((This)->lpVtbl->get_DependencyPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_OptionalPackageFamilyNames(This, value) \
    ((This)->lpVtbl->get_OptionalPackageFamilyNames(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_OptionalPackageUris(This, value) \
    ((This)->lpVtbl->get_OptionalPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_RelatedPackageUris(This, value) \
    ((This)->lpVtbl->get_RelatedPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_ExternalLocationUri(This, value) \
    ((This)->lpVtbl->get_ExternalLocationUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_ExternalLocationUri(This, value) \
    ((This)->lpVtbl->put_ExternalLocationUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_StubPackageOption(This, value) \
    ((This)->lpVtbl->get_StubPackageOption(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_StubPackageOption(This, value) \
    ((This)->lpVtbl->put_StubPackageOption(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_AllowUnsigned(This, value) \
    ((This)->lpVtbl->get_AllowUnsigned(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_AllowUnsigned(This, value) \
    ((This)->lpVtbl->put_AllowUnsigned(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_DeveloperMode(This, value) \
    ((This)->lpVtbl->get_DeveloperMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_DeveloperMode(This, value) \
    ((This)->lpVtbl->put_DeveloperMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_ForceAppShutdown(This, value) \
    ((This)->lpVtbl->get_ForceAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_ForceAppShutdown(This, value) \
    ((This)->lpVtbl->put_ForceAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_ForceTargetAppShutdown(This, value) \
    ((This)->lpVtbl->get_ForceTargetAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_ForceTargetAppShutdown(This, value) \
    ((This)->lpVtbl->put_ForceTargetAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_ForceUpdateFromAnyVersion(This, value) \
    ((This)->lpVtbl->get_ForceUpdateFromAnyVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_ForceUpdateFromAnyVersion(This, value) \
    ((This)->lpVtbl->put_ForceUpdateFromAnyVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_InstallAllResources(This, value) \
    ((This)->lpVtbl->get_InstallAllResources(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_InstallAllResources(This, value) \
    ((This)->lpVtbl->put_InstallAllResources(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_RequiredContentGroupOnly(This, value) \
    ((This)->lpVtbl->get_RequiredContentGroupOnly(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_RequiredContentGroupOnly(This, value) \
    ((This)->lpVtbl->put_RequiredContentGroupOnly(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_RetainFilesOnFailure(This, value) \
    ((This)->lpVtbl->get_RetainFilesOnFailure(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_RetainFilesOnFailure(This, value) \
    ((This)->lpVtbl->put_RetainFilesOnFailure(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_StageInPlace(This, value) \
    ((This)->lpVtbl->get_StageInPlace(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_StageInPlace(This, value) \
    ((This)->lpVtbl->put_StageInPlace(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_DeferRegistrationWhenPackagesAreInUse(This, value) \
    ((This)->lpVtbl->get_DeferRegistrationWhenPackagesAreInUse(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_DeferRegistrationWhenPackagesAreInUse(This, value) \
    ((This)->lpVtbl->put_DeferRegistrationWhenPackagesAreInUse(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_IsExpectedDigestsSupported(This, value) \
    ((This)->lpVtbl->get_IsExpectedDigestsSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_ExpectedDigests(This, value) \
    ((This)->lpVtbl->get_ExpectedDigests(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_IsLimitToExistingPackagesSupported(This, value) \
    ((This)->lpVtbl->get_IsLimitToExistingPackagesSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_get_LimitToExistingPackages(This, value) \
    ((This)->lpVtbl->get_LimitToExistingPackages(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_put_LimitToExistingPackages(This, value) \
    ((This)->lpVtbl->put_LimitToExistingPackages(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IEnsureReadyOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.EnsureReadyOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IEnsureReadyOptions[] = L"Microsoft.Windows.Management.Deployment.IEnsureReadyOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AddPackageOptions)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_get_AddPackageOptions(This, value) \
    ((This)->lpVtbl->get_AddPackageOptions(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IEnsureReadyOptions2
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.EnsureReadyOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IEnsureReadyOptions2[] = L"Microsoft.Windows.Management.Deployment.IEnsureReadyOptions2";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RegisterNewerIfAvailable)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_RegisterNewerIfAvailable)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_get_RegisterNewerIfAvailable(This, value) \
    ((This)->lpVtbl->get_RegisterNewerIfAvailable(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_put_RegisterNewerIfAvailable(This, value) \
    ((This)->lpVtbl->put_RegisterNewerIfAvailable(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManager[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsPackageReady)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageReadyByUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageSetReady)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* EnsurePackageReadyAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* EnsurePackageReadyByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* EnsurePackageSetReadyAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIEnsureReadyOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* AddPackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* AddPackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* AddPackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIAddPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* StagePackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* StagePackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* StagePackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RegisterPackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RegisterPackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RegisterPackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RemovePackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RemovePackageByFullNameAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING packageFullName,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RemovePackageByFamilyNameAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING packageFamilyName,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RemovePackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RemovePackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* ResetPackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* ResetPackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* ResetPackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RepairPackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RepairPackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* RepairPackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* ProvisionPackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* ProvisionPackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* ProvisionPackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* options,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* DeprovisionPackageAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING package,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* DeprovisionPackageByUriAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* DeprovisionPackageSetAsync)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentResult_Microsoft__CWindows__CManagement__CDeployment__CPackageDeploymentProgress** operation);
    HRESULT (STDMETHODCALLTYPE* IsPackageRegistrationPending)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING packageFamilyName,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageRegistrationPendingForUser)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager* This,
        HSTRING userSecurityId,
        HSTRING packageFamilyName,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_IsPackageReady(This, package, result) \
    ((This)->lpVtbl->IsPackageReady(This, package, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_IsPackageReadyByUri(This, packageUri, result) \
    ((This)->lpVtbl->IsPackageReadyByUri(This, packageUri, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_IsPackageSetReady(This, packageSet, result) \
    ((This)->lpVtbl->IsPackageSetReady(This, packageSet, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_EnsurePackageReadyAsync(This, package, options, operation) \
    ((This)->lpVtbl->EnsurePackageReadyAsync(This, package, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_EnsurePackageReadyByUriAsync(This, packageUri, options, operation) \
    ((This)->lpVtbl->EnsurePackageReadyByUriAsync(This, packageUri, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_EnsurePackageSetReadyAsync(This, packageSet, options, operation) \
    ((This)->lpVtbl->EnsurePackageSetReadyAsync(This, packageSet, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_AddPackageAsync(This, package, options, operation) \
    ((This)->lpVtbl->AddPackageAsync(This, package, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_AddPackageByUriAsync(This, packageUri, options, operation) \
    ((This)->lpVtbl->AddPackageByUriAsync(This, packageUri, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_AddPackageSetAsync(This, packageSet, options, operation) \
    ((This)->lpVtbl->AddPackageSetAsync(This, packageSet, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_StagePackageAsync(This, package, options, operation) \
    ((This)->lpVtbl->StagePackageAsync(This, package, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_StagePackageByUriAsync(This, packageUri, options, operation) \
    ((This)->lpVtbl->StagePackageByUriAsync(This, packageUri, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_StagePackageSetAsync(This, packageSet, options, operation) \
    ((This)->lpVtbl->StagePackageSetAsync(This, packageSet, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RegisterPackageAsync(This, package, options, operation) \
    ((This)->lpVtbl->RegisterPackageAsync(This, package, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RegisterPackageByUriAsync(This, packageUri, options, operation) \
    ((This)->lpVtbl->RegisterPackageByUriAsync(This, packageUri, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RegisterPackageSetAsync(This, packageSet, options, operation) \
    ((This)->lpVtbl->RegisterPackageSetAsync(This, packageSet, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RemovePackageAsync(This, package, options, operation) \
    ((This)->lpVtbl->RemovePackageAsync(This, package, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RemovePackageByFullNameAsync(This, packageFullName, options, operation) \
    ((This)->lpVtbl->RemovePackageByFullNameAsync(This, packageFullName, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RemovePackageByFamilyNameAsync(This, packageFamilyName, options, operation) \
    ((This)->lpVtbl->RemovePackageByFamilyNameAsync(This, packageFamilyName, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RemovePackageByUriAsync(This, packageUri, options, operation) \
    ((This)->lpVtbl->RemovePackageByUriAsync(This, packageUri, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RemovePackageSetAsync(This, packageSet, options, operation) \
    ((This)->lpVtbl->RemovePackageSetAsync(This, packageSet, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_ResetPackageAsync(This, package, operation) \
    ((This)->lpVtbl->ResetPackageAsync(This, package, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_ResetPackageByUriAsync(This, packageUri, operation) \
    ((This)->lpVtbl->ResetPackageByUriAsync(This, packageUri, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_ResetPackageSetAsync(This, packageSet, operation) \
    ((This)->lpVtbl->ResetPackageSetAsync(This, packageSet, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RepairPackageAsync(This, package, operation) \
    ((This)->lpVtbl->RepairPackageAsync(This, package, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RepairPackageByUriAsync(This, packageUri, operation) \
    ((This)->lpVtbl->RepairPackageByUriAsync(This, packageUri, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_RepairPackageSetAsync(This, packageSet, operation) \
    ((This)->lpVtbl->RepairPackageSetAsync(This, packageSet, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_ProvisionPackageAsync(This, package, options, operation) \
    ((This)->lpVtbl->ProvisionPackageAsync(This, package, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_ProvisionPackageByUriAsync(This, packageUri, options, operation) \
    ((This)->lpVtbl->ProvisionPackageByUriAsync(This, packageUri, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_ProvisionPackageSetAsync(This, packageSet, options, operation) \
    ((This)->lpVtbl->ProvisionPackageSetAsync(This, packageSet, options, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_DeprovisionPackageAsync(This, package, operation) \
    ((This)->lpVtbl->DeprovisionPackageAsync(This, package, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_DeprovisionPackageByUriAsync(This, packageUri, operation) \
    ((This)->lpVtbl->DeprovisionPackageByUriAsync(This, packageUri, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_DeprovisionPackageSetAsync(This, packageSet, operation) \
    ((This)->lpVtbl->DeprovisionPackageSetAsync(This, packageSet, operation))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_IsPackageRegistrationPending(This, packageFamilyName, result) \
    ((This)->lpVtbl->IsPackageRegistrationPending(This, packageFamilyName, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_IsPackageRegistrationPendingForUser(This, userSecurityId, packageFamilyName, result) \
    ((This)->lpVtbl->IsPackageRegistrationPendingForUser(This, userSecurityId, packageFamilyName, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManager2
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManager2[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManager2";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsPackageReadyOrNewerAvailable)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        HSTRING package,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageReadyOrNewerAvailableStatus* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageReadyOrNewerAvailableByUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageReadyOrNewerAvailableStatus* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageSetReadyOrNewerAvailable)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageReadyOrNewerAvailableStatus* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageProvisioned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        HSTRING package,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageProvisionedByUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* packageUri,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* IsPackageSetProvisioned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_IsPackageReadyOrNewerAvailable(This, package, result) \
    ((This)->lpVtbl->IsPackageReadyOrNewerAvailable(This, package, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_IsPackageReadyOrNewerAvailableByUri(This, packageUri, result) \
    ((This)->lpVtbl->IsPackageReadyOrNewerAvailableByUri(This, packageUri, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_IsPackageSetReadyOrNewerAvailable(This, packageSet, result) \
    ((This)->lpVtbl->IsPackageSetReadyOrNewerAvailable(This, packageSet, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_IsPackageProvisioned(This, package, result) \
    ((This)->lpVtbl->IsPackageProvisioned(This, package, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_IsPackageProvisionedByUri(This, packageUri, result) \
    ((This)->lpVtbl->IsPackageProvisionedByUri(This, packageUri, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_IsPackageSetProvisioned(This, packageSet, result) \
    ((This)->lpVtbl->IsPackageSetProvisioned(This, packageSet, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManagerStatics[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDefault)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_GetDefault(This, result) \
    ((This)->lpVtbl->GetDefault(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics2
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentManagerStatics2[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics2";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsPackageDeploymentFeatureSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2* This,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentFeature feature,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_IsPackageDeploymentFeatureSupported(This, feature, result) \
    ((This)->lpVtbl->IsPackageDeploymentFeatureSupported(This, feature, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageDeploymentResult
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageDeploymentResult
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageDeploymentResult[] = L"Microsoft.Windows.Management.Deployment.IPackageDeploymentResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CPackageDeploymentStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_Error)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorText)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ActivityId)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult* This,
        GUID* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_get_Error(This, value) \
    ((This)->lpVtbl->get_Error(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_get_ErrorText(This, value) \
    ((This)->lpVtbl->get_ErrorText(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_get_ActivityId(This, value) \
    ((This)->lpVtbl->get_ActivityId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageDeploymentResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageRuntimeManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageRuntimeManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageRuntimeManager[] = L"Microsoft.Windows.Management.Deployment.IPackageRuntimeManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* AddPackageSet)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition** result);
    HRESULT (STDMETHODCALLTYPE* AddPackageSetWithOptions)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* packageSet,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* createOptions,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* addOptions,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition** result);
    HRESULT (STDMETHODCALLTYPE* RemovePackageSet)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* packageSetRuntimeDisposition);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_AddPackageSet(This, packageSet, result) \
    ((This)->lpVtbl->AddPackageSet(This, packageSet, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_AddPackageSetWithOptions(This, packageSet, createOptions, addOptions, result) \
    ((This)->lpVtbl->AddPackageSetWithOptions(This, packageSet, createOptions, addOptions, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_RemovePackageSet(This, packageSetRuntimeDisposition) \
    ((This)->lpVtbl->RemovePackageSet(This, packageSetRuntimeDisposition))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageRuntimeManagerStatics
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageRuntimeManager
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageRuntimeManagerStatics[] = L"Microsoft.Windows.Management.Deployment.IPackageRuntimeManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDefault)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_GetDefault(This, result) \
    ((This)->lpVtbl->GetDefault(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageRuntimeManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSet
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSet
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSet[] = L"Microsoft.Windows.Management.Deployment.IPackageSet";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Id)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_PackageUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_PackageUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_Items)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet* This,
        __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItem** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_put_Id(This, value) \
    ((This)->lpVtbl->put_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_get_PackageUri(This, value) \
    ((This)->lpVtbl->get_PackageUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_put_PackageUri(This, value) \
    ((This)->lpVtbl->put_PackageUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_get_Items(This, value) \
    ((This)->lpVtbl->get_Items(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSet_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSetItem
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSetItem
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSetItem[] = L"Microsoft.Windows.Management.Deployment.IPackageSetItem";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Id)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_PackageFamilyName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_PackageFamilyName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_MinVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        struct __x_ABI_CWindows_CApplicationModel_CPackageVersion* value);
    HRESULT (STDMETHODCALLTYPE* put_MinVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        struct __x_ABI_CWindows_CApplicationModel_CPackageVersion value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessorArchitectureFilter)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures* value);
    HRESULT (STDMETHODCALLTYPE* put_ProcessorArchitectureFilter)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures value);
    HRESULT (STDMETHODCALLTYPE* get_PackageUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_PackageUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_put_Id(This, value) \
    ((This)->lpVtbl->put_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_get_PackageFamilyName(This, value) \
    ((This)->lpVtbl->get_PackageFamilyName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_put_PackageFamilyName(This, value) \
    ((This)->lpVtbl->put_PackageFamilyName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_get_MinVersion(This, value) \
    ((This)->lpVtbl->get_MinVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_put_MinVersion(This, value) \
    ((This)->lpVtbl->put_MinVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_get_ProcessorArchitectureFilter(This, value) \
    ((This)->lpVtbl->get_ProcessorArchitectureFilter(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_put_ProcessorArchitectureFilter(This, value) \
    ((This)->lpVtbl->put_ProcessorArchitectureFilter(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_get_PackageUri(This, value) \
    ((This)->lpVtbl->get_PackageUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_put_PackageUri(This, value) \
    ((This)->lpVtbl->put_PackageUri(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItem_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSetItemRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSetItemRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.IPackageSetItemRuntimeDisposition";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDispositionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PackageSetItemId)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_PackageFullName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_PackageDependencyId)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_PackageDependencyContextId)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDispositionVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDispositionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_get_PackageSetItemId(This, value) \
    ((This)->lpVtbl->get_PackageSetItemId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_get_PackageFullName(This, value) \
    ((This)->lpVtbl->get_PackageFullName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_get_PackageDependencyId(This, value) \
    ((This)->lpVtbl->get_PackageDependencyId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_get_PackageDependencyContextId(This, value) \
    ((This)->lpVtbl->get_PackageDependencyContextId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetItemRuntimeDisposition_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageSetRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageSetRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.IPackageSetRuntimeDisposition";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDispositionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PackageSetId)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_PackageSetId)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_PackageSetItemRuntimeDispositions)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition* This,
        __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageSetItemRuntimeDisposition** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDispositionVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDispositionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_get_PackageSetId(This, value) \
    ((This)->lpVtbl->get_PackageSetId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_put_PackageSetId(This, value) \
    ((This)->lpVtbl->put_PackageSetId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_get_PackageSetItemRuntimeDispositions(This, value) \
    ((This)->lpVtbl->get_PackageSetItemRuntimeDispositions(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageSetRuntimeDisposition_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageVolume
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageVolume
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageVolume[] = L"Microsoft.Windows.Management.Deployment.IPackageVolume";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsSystemVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_MountPoint)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_PackageStorePath)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_SupportsHardLinks)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsFullTrustPackageSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsAppxInstallSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* IsRepairNeeded)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Repair)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_IsSystemVolume(This, value) \
    ((This)->lpVtbl->get_IsSystemVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_MountPoint(This, value) \
    ((This)->lpVtbl->get_MountPoint(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_PackageStorePath(This, value) \
    ((This)->lpVtbl->get_PackageStorePath(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_SupportsHardLinks(This, value) \
    ((This)->lpVtbl->get_SupportsHardLinks(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_IsFullTrustPackageSupported(This, value) \
    ((This)->lpVtbl->get_IsFullTrustPackageSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_get_IsAppxInstallSupported(This, value) \
    ((This)->lpVtbl->get_IsAppxInstallSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_IsRepairNeeded(This, result) \
    ((This)->lpVtbl->IsRepairNeeded(This, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_Repair(This) \
    ((This)->lpVtbl->Repair(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IPackageVolumeStatics
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.PackageVolume
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IPackageVolumeStatics[] = L"Microsoft.Windows.Management.Deployment.IPackageVolumeStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* FindPackageVolumes)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        __FIVector_1_Microsoft__CWindows__CManagement__CDeployment__CPackageVolume** result);
    HRESULT (STDMETHODCALLTYPE* FindPackageVolumeByPath)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        HSTRING packageStorePath,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** result);
    HRESULT (STDMETHODCALLTYPE* FindPackageVolumeByName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics* This,
        HSTRING name,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FindPackageVolumes(This, result) \
    ((This)->lpVtbl->FindPackageVolumes(This, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FindPackageVolumeByPath(This, packageStorePath, result) \
    ((This)->lpVtbl->FindPackageVolumeByPath(This, packageStorePath, result))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_FindPackageVolumeByName(This, name, result) \
    ((This)->lpVtbl->FindPackageVolumeByName(This, name, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolumeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IProvisionPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.ProvisionPackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IProvisionPackageOptions[] = L"Microsoft.Windows.Management.Deployment.IProvisionPackageOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsOptionalPackageFamilyNamesSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_OptionalPackageFamilyNames)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        __FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_IsProjectionOrderPackageFamilyNamesSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ProjectionOrderPackageFamilyNames)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions* This,
        __FIVector_1_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_get_IsOptionalPackageFamilyNamesSupported(This, value) \
    ((This)->lpVtbl->get_IsOptionalPackageFamilyNamesSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_get_OptionalPackageFamilyNames(This, value) \
    ((This)->lpVtbl->get_OptionalPackageFamilyNames(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_get_IsProjectionOrderPackageFamilyNamesSupported(This, value) \
    ((This)->lpVtbl->get_IsProjectionOrderPackageFamilyNamesSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_get_ProjectionOrderPackageFamilyNames(This, value) \
    ((This)->lpVtbl->get_ProjectionOrderPackageFamilyNames(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIProvisionPackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IRegisterPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.RegisterPackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IRegisterPackageOptions[] = L"Microsoft.Windows.Management.Deployment.IRegisterPackageOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AppDataVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** value);
    HRESULT (STDMETHODCALLTYPE* put_AppDataVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value);
    HRESULT (STDMETHODCALLTYPE* get_DependencyPackageFamilyNames)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_DependencyPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_OptionalPackageFamilyNames)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_ExternalLocationUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_ExternalLocationUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_AllowUnsigned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowUnsigned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_DeveloperMode)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_DeveloperMode)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceTargetAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceTargetAppShutdown)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceUpdateFromAnyVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceUpdateFromAnyVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_InstallAllResources)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_InstallAllResources)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StageInPlace)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_StageInPlace)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_DeferRegistrationWhenPackagesAreInUse)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_DeferRegistrationWhenPackagesAreInUse)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsExpectedDigestsSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ExpectedDigests)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions* This,
        __FIMap_2_Windows__CFoundation__CUri_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_AppDataVolume(This, value) \
    ((This)->lpVtbl->get_AppDataVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_AppDataVolume(This, value) \
    ((This)->lpVtbl->put_AppDataVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_DependencyPackageFamilyNames(This, value) \
    ((This)->lpVtbl->get_DependencyPackageFamilyNames(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_DependencyPackageUris(This, value) \
    ((This)->lpVtbl->get_DependencyPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_OptionalPackageFamilyNames(This, value) \
    ((This)->lpVtbl->get_OptionalPackageFamilyNames(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_ExternalLocationUri(This, value) \
    ((This)->lpVtbl->get_ExternalLocationUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_ExternalLocationUri(This, value) \
    ((This)->lpVtbl->put_ExternalLocationUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_AllowUnsigned(This, value) \
    ((This)->lpVtbl->get_AllowUnsigned(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_AllowUnsigned(This, value) \
    ((This)->lpVtbl->put_AllowUnsigned(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_DeveloperMode(This, value) \
    ((This)->lpVtbl->get_DeveloperMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_DeveloperMode(This, value) \
    ((This)->lpVtbl->put_DeveloperMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_ForceAppShutdown(This, value) \
    ((This)->lpVtbl->get_ForceAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_ForceAppShutdown(This, value) \
    ((This)->lpVtbl->put_ForceAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_ForceTargetAppShutdown(This, value) \
    ((This)->lpVtbl->get_ForceTargetAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_ForceTargetAppShutdown(This, value) \
    ((This)->lpVtbl->put_ForceTargetAppShutdown(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_ForceUpdateFromAnyVersion(This, value) \
    ((This)->lpVtbl->get_ForceUpdateFromAnyVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_ForceUpdateFromAnyVersion(This, value) \
    ((This)->lpVtbl->put_ForceUpdateFromAnyVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_InstallAllResources(This, value) \
    ((This)->lpVtbl->get_InstallAllResources(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_InstallAllResources(This, value) \
    ((This)->lpVtbl->put_InstallAllResources(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_StageInPlace(This, value) \
    ((This)->lpVtbl->get_StageInPlace(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_StageInPlace(This, value) \
    ((This)->lpVtbl->put_StageInPlace(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_DeferRegistrationWhenPackagesAreInUse(This, value) \
    ((This)->lpVtbl->get_DeferRegistrationWhenPackagesAreInUse(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_put_DeferRegistrationWhenPackagesAreInUse(This, value) \
    ((This)->lpVtbl->put_DeferRegistrationWhenPackagesAreInUse(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_IsExpectedDigestsSupported(This, value) \
    ((This)->lpVtbl->get_IsExpectedDigestsSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_get_ExpectedDigests(This, value) \
    ((This)->lpVtbl->get_ExpectedDigests(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRegisterPackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IRemovePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.RemovePackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IRemovePackageOptions[] = L"Microsoft.Windows.Management.Deployment.IRemovePackageOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FailIfNotFound)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_FailIfNotFound)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_PreserveApplicationData)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_PreserveApplicationData)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_PreserveRoamableApplicationData)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_PreserveRoamableApplicationData)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_RemoveForAllUsers)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_RemoveForAllUsers)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_get_FailIfNotFound(This, value) \
    ((This)->lpVtbl->get_FailIfNotFound(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_put_FailIfNotFound(This, value) \
    ((This)->lpVtbl->put_FailIfNotFound(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_get_PreserveApplicationData(This, value) \
    ((This)->lpVtbl->get_PreserveApplicationData(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_put_PreserveApplicationData(This, value) \
    ((This)->lpVtbl->put_PreserveApplicationData(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_get_PreserveRoamableApplicationData(This, value) \
    ((This)->lpVtbl->get_PreserveRoamableApplicationData(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_put_PreserveRoamableApplicationData(This, value) \
    ((This)->lpVtbl->put_PreserveRoamableApplicationData(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_get_RemoveForAllUsers(This, value) \
    ((This)->lpVtbl->get_RemoveForAllUsers(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_put_RemoveForAllUsers(This, value) \
    ((This)->lpVtbl->put_RemoveForAllUsers(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIRemovePackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Management.Deployment.IStagePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Management.Deployment.StagePackageOptions
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Management_Deployment_IStagePackageOptions[] = L"Microsoft.Windows.Management.Deployment.IStagePackageOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TargetVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume** value);
    HRESULT (STDMETHODCALLTYPE* put_TargetVolume)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIPackageVolume* value);
    HRESULT (STDMETHODCALLTYPE* get_DependencyPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_OptionalPackageFamilyNames)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __FIVector_1_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_OptionalPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_RelatedPackageUris)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __FIVector_1_Windows__CFoundation__CUri** value);
    HRESULT (STDMETHODCALLTYPE* get_ExternalLocationUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);
    HRESULT (STDMETHODCALLTYPE* put_ExternalLocationUri)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* get_StubPackageOption)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption* value);
    HRESULT (STDMETHODCALLTYPE* put_StubPackageOption)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CStubPackageOption value);
    HRESULT (STDMETHODCALLTYPE* get_DeveloperMode)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_DeveloperMode)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForceUpdateFromAnyVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceUpdateFromAnyVersion)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_InstallAllResources)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_InstallAllResources)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_RequiredContentGroupOnly)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_RequiredContentGroupOnly)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_StageInPlace)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_StageInPlace)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_AllowUnsigned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowUnsigned)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsExpectedDigestsSupported)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ExpectedDigests)(__x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions* This,
        __FIMap_2_Windows__CFoundation__CUri_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_TargetVolume(This, value) \
    ((This)->lpVtbl->get_TargetVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_TargetVolume(This, value) \
    ((This)->lpVtbl->put_TargetVolume(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_DependencyPackageUris(This, value) \
    ((This)->lpVtbl->get_DependencyPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_OptionalPackageFamilyNames(This, value) \
    ((This)->lpVtbl->get_OptionalPackageFamilyNames(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_OptionalPackageUris(This, value) \
    ((This)->lpVtbl->get_OptionalPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_RelatedPackageUris(This, value) \
    ((This)->lpVtbl->get_RelatedPackageUris(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_ExternalLocationUri(This, value) \
    ((This)->lpVtbl->get_ExternalLocationUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_ExternalLocationUri(This, value) \
    ((This)->lpVtbl->put_ExternalLocationUri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_StubPackageOption(This, value) \
    ((This)->lpVtbl->get_StubPackageOption(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_StubPackageOption(This, value) \
    ((This)->lpVtbl->put_StubPackageOption(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_DeveloperMode(This, value) \
    ((This)->lpVtbl->get_DeveloperMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_DeveloperMode(This, value) \
    ((This)->lpVtbl->put_DeveloperMode(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_ForceUpdateFromAnyVersion(This, value) \
    ((This)->lpVtbl->get_ForceUpdateFromAnyVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_ForceUpdateFromAnyVersion(This, value) \
    ((This)->lpVtbl->put_ForceUpdateFromAnyVersion(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_InstallAllResources(This, value) \
    ((This)->lpVtbl->get_InstallAllResources(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_InstallAllResources(This, value) \
    ((This)->lpVtbl->put_InstallAllResources(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_RequiredContentGroupOnly(This, value) \
    ((This)->lpVtbl->get_RequiredContentGroupOnly(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_RequiredContentGroupOnly(This, value) \
    ((This)->lpVtbl->put_RequiredContentGroupOnly(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_StageInPlace(This, value) \
    ((This)->lpVtbl->get_StageInPlace(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_StageInPlace(This, value) \
    ((This)->lpVtbl->put_StageInPlace(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_AllowUnsigned(This, value) \
    ((This)->lpVtbl->get_AllowUnsigned(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_put_AllowUnsigned(This, value) \
    ((This)->lpVtbl->put_AllowUnsigned(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_IsExpectedDigestsSupported(This, value) \
    ((This)->lpVtbl->get_IsExpectedDigestsSupported(This, value))

#define __x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_get_ExpectedDigests(This, value) \
    ((This)->lpVtbl->get_ExpectedDigests(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CManagement_CDeployment_CIStagePackageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.AddPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IAddPackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_AddPackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_AddPackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_AddPackageOptions[] = L"Microsoft.Windows.Management.Deployment.AddPackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.EnsureReadyOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IEnsureReadyOptions ** Default Interface **
 *    Microsoft.Windows.Management.Deployment.IEnsureReadyOptions2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_EnsureReadyOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_EnsureReadyOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_EnsureReadyOptions[] = L"Microsoft.Windows.Management.Deployment.EnsureReadyOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageDeploymentManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics interface starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageDeploymentManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageDeploymentManager ** Default Interface **
 *    Microsoft.Windows.Management.Deployment.IPackageDeploymentManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageDeploymentManager[] = L"Microsoft.Windows.Management.Deployment.PackageDeploymentManager";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageDeploymentResult
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageDeploymentResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageDeploymentResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageDeploymentResult[] = L"Microsoft.Windows.Management.Deployment.PackageDeploymentResult";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageRuntimeManager
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageRuntimeManagerStatics interface starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageRuntimeManager ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageRuntimeManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageRuntimeManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageRuntimeManager[] = L"Microsoft.Windows.Management.Deployment.PackageRuntimeManager";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSet
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSet ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSet_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSet_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSet[] = L"Microsoft.Windows.Management.Deployment.PackageSet";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSetItem
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSetItem ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItem_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSetItem[] = L"Microsoft.Windows.Management.Deployment.PackageSetItem";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSetItemRuntimeDisposition ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItemRuntimeDisposition_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetItemRuntimeDisposition_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSetItemRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageSetRuntimeDisposition ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetRuntimeDisposition_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageSetRuntimeDisposition_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageSetRuntimeDisposition[] = L"Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.PackageVolume
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Management.Deployment.IPackageVolumeStatics interface starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IPackageVolume ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageVolume_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_PackageVolume_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_PackageVolume[] = L"Microsoft.Windows.Management.Deployment.PackageVolume";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.ProvisionPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IProvisionPackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_ProvisionPackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_ProvisionPackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_ProvisionPackageOptions[] = L"Microsoft.Windows.Management.Deployment.ProvisionPackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.RegisterPackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IRegisterPackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RegisterPackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RegisterPackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_RegisterPackageOptions[] = L"Microsoft.Windows.Management.Deployment.RegisterPackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.RemovePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IRemovePackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RemovePackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_RemovePackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_RemovePackageOptions[] = L"Microsoft.Windows.Management.Deployment.RemovePackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Management.Deployment.StagePackageOptions
 *
 * Introduced to Microsoft.Windows.Management.Deployment.PackageDeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Management.Deployment.PackageDeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Management.Deployment.IStagePackageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Management_Deployment_StagePackageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Management_Deployment_StagePackageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Management_Deployment_StagePackageOptions[] = L"Microsoft.Windows.Management.Deployment.StagePackageOptions";
#endif
#endif // MICROSOFT_WINDOWS_MANAGEMENT_DEPLOYMENT_PACKAGEDEPLOYMENTCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Emanagement2Edeployment_p_h__

#endif // __microsoft2Ewindows2Emanagement2Edeployment_h__
