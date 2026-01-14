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
#ifndef __microsoft2Ewindows2Eapplicationmodel2Ewindowsappruntime_h__
#define __microsoft2Ewindows2Eapplicationmodel2Ewindowsappruntime_h__
#ifndef __microsoft2Ewindows2Eapplicationmodel2Ewindowsappruntime_p_h__
#define __microsoft2Ewindows2Eapplicationmodel2Ewindowsappruntime_p_h__


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
#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION 0x40000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION)

#if !defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION 0x10000
#endif // defined(MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION)

#if !defined(WINDOWS_APPLICATIONMODEL_STARTUPTASKCONTRACT_VERSION)
#define WINDOWS_APPLICATIONMODEL_STARTUPTASKCONTRACT_VERSION 0x30000
#endif // defined(WINDOWS_APPLICATIONMODEL_STARTUPTASKCONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Windows.ApplicationModel.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IDeploymentInitializeOptions;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentInitializeOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IDeploymentInitializeOptions2;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2 ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentInitializeOptions2

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IDeploymentManagerStatics;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IDeploymentManagerStatics2;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2 ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentManagerStatics2

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IDeploymentResult;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentResult

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IDeploymentResultFactory;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentResultFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IReleaseInfoStatics;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IReleaseInfoStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IRuntimeCompatibilityOptions;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IRuntimeCompatibilityOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    interface IRuntimeInfoStatics;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IRuntimeInfoStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    typedef enum RuntimeCompatibilityChange : int RuntimeCompatibilityChange;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("25abd83a-a7d6-5c3a-94a4-674fd9cec6b4"))
IIterator<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> : IIterator_impl<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t;
#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE */

#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("79fffbf6-dc39-59e3-a684-fa55fb49238f"))
IIterable<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> : IIterable_impl<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t;
#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE */

#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b3675e71-9db8-5b51-986a-1223964c6f52"))
IVectorView<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> : IVectorView_impl<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t;
#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE */

#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#define DEF___FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b2d54673-319a-5cef-9997-2aa95cae7d4b"))
IVector<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> : IVector_impl<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<enum ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityChange> __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t;
#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange ABI::Windows::Foundation::Collections::__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_USE */

#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

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
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    typedef enum DeploymentStatus : int DeploymentStatus;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    typedef struct WindowsAppRuntimeVersion WindowsAppRuntimeVersion;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    class DeploymentInitializeOptions;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    class DeploymentResult;
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentStatus
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    enum DeploymentStatus : int
                    {
                        DeploymentStatus_Unknown = 0,
                        DeploymentStatus_Ok = 1,
                        DeploymentStatus_PackageInstallRequired = 2,
                        DeploymentStatus_PackageInstallFailed = 3,
                    };
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    enum RuntimeCompatibilityChange : int
                    {
                        RuntimeCompatibilityChange_None = 0,
                        RuntimeCompatibilityChange_OrientedVirtualizingPanel_FixBoundsOverflow = 59890419,
                    };
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.WindowsAppRuntime.WindowsAppRuntimeVersion
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    struct WindowsAppRuntimeVersion
                    {
                        UINT32 Major;
                        UINT32 Minor;
                        UINT32 Patch;
                    };
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentInitializeOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("578a5fd4-9d7f-5e01-97b8-d8ea61db4027")
                    IDeploymentInitializeOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ForceDeployment(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ForceDeployment(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeploymentInitializeOptions = _uuidof(IDeploymentInitializeOptions);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 3.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x30000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentInitializeOptions2[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("ad902820-149f-5e16-a566-9b2363997de2")
                    IDeploymentInitializeOptions2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_OnErrorShowUI(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_OnErrorShowUI(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeploymentInitializeOptions2 = _uuidof(IDeploymentInitializeOptions2);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x30000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentManagerStatics[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("6782a9d0-bfd0-50ea-81b0-32e9ed37cdf0")
                    IDeploymentManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetStatus(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Initialize(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentResult** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeploymentManagerStatics = _uuidof(IDeploymentManagerStatics);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentManagerStatics2[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("f49c16ee-6ebc-5f15-bebb-2ba49f8c0b30")
                    IDeploymentManagerStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Initialize(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentInitializeOptions* deploymentInitializeOptions,
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentResult** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeploymentManagerStatics2 = _uuidof(IDeploymentManagerStatics2);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResult
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentResult[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("27203f62-463d-587a-8eb7-870098901078")
                    IDeploymentResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeploymentResult = _uuidof(IDeploymentResult);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResultFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentResultFactory[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResultFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("acd7bdae-4ae6-5cac-8205-1e8c305f953b")
                    IDeploymentResultFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus status,
                            HRESULT extendedError,
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::IDeploymentResult** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeploymentResultFactory = _uuidof(IDeploymentResultFactory);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IReleaseInfoStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IReleaseInfoStatics[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IReleaseInfoStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("ed9be8ff-073c-5c66-bf97-ef0ce67405c3")
                    IReleaseInfoStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Major(
                            UINT16* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Minor(
                            UINT16* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Patch(
                            UINT16* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_VersionTag(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AsString(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IReleaseInfoStatics = _uuidof(IReleaseInfoStatics);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeCompatibilityOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IRuntimeCompatibilityOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeCompatibilityOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("d7403bd9-b25d-5b8f-8de1-9dcb57d99f6c")
                    IRuntimeCompatibilityOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PatchLevel1(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::WindowsAppRuntimeVersion* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PatchLevel1(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::WindowsAppRuntimeVersion value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PatchLevel2(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::WindowsAppRuntimeVersion* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PatchLevel2(
                            ABI::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::WindowsAppRuntimeVersion value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DisabledChanges(
                            __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Apply(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRuntimeCompatibilityOptions = _uuidof(IRuntimeCompatibilityOptions);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeInfoStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IRuntimeInfoStatics[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeInfoStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace WindowsAppRuntime {
                    MIDL_INTERFACE("e5cb9549-8951-590e-a753-8f281cd77ab5")
                    IRuntimeInfoStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Version(
                            ABI::Windows::ApplicationModel::PackageVersion* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AsString(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRuntimeInfoStatics = _uuidof(IRuntimeInfoStatics);
                } /* WindowsAppRuntime */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 2.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 2.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions ** Default Interface **
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentInitializeOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentInitializeOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentInitializeOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentManager[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResultFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResult ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentResult[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IReleaseInfoStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_ReleaseInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_ReleaseInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_ReleaseInfo[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeCompatibilityOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeCompatibilityOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeCompatibilityOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeCompatibilityOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeInfoStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeInfo[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2 __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2 __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange;

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

typedef struct __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 itemsLength,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl;

interface __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

typedef struct __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        __FIIterator_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl;

interface __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

typedef struct __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 index,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__)
#define ____FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__

typedef interface __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange;

typedef struct __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 index,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        __FIVectorView_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 index,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 index,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange* This,
        UINT32 itemsLength,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange* items);

    END_INTERFACE
} __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl;

interface __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange
{
    CONST_VTBL struct __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChangeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

typedef struct __x_ABI_CWindows_CApplicationModel_CPackageVersion __x_ABI_CWindows_CApplicationModel_CPackageVersion;

typedef enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CDeploymentStatus __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CDeploymentStatus;

typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion;

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentStatus
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CDeploymentStatus
{
    DeploymentStatus_Unknown = 0,
    DeploymentStatus_Ok = 1,
    DeploymentStatus_PackageInstallRequired = 2,
    DeploymentStatus_PackageInstallFailed = 3,
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CRuntimeCompatibilityChange
{
    RuntimeCompatibilityChange_None = 0,
    RuntimeCompatibilityChange_OrientedVirtualizingPanel_FixBoundsOverflow = 59890419,
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.WindowsAppRuntime.WindowsAppRuntimeVersion
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion
{
    UINT32 Major;
    UINT32 Minor;
    UINT32 Patch;
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentInitializeOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ForceDeployment)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ForceDeployment)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_get_ForceDeployment(This, value) \
    ((This)->lpVtbl->get_ForceDeployment(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_put_ForceDeployment(This, value) \
    ((This)->lpVtbl->put_ForceDeployment(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 3.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x30000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentInitializeOptions2[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions2";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_OnErrorShowUI)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_OnErrorShowUI)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_get_OnErrorShowUI(This, value) \
    ((This)->lpVtbl->get_OnErrorShowUI(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_put_OnErrorShowUI(This, value) \
    ((This)->lpVtbl->put_OnErrorShowUI(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x30000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentManagerStatics[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetStatus)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult** result);
    HRESULT (STDMETHODCALLTYPE* Initialize)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_GetStatus(This, result) \
    ((This)->lpVtbl->GetStatus(This, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_Initialize(This, result) \
    ((This)->lpVtbl->Initialize(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentManagerStatics2[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics2";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Initialize)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentInitializeOptions* deploymentInitializeOptions,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_Initialize(This, deploymentInitializeOptions, result) \
    ((This)->lpVtbl->Initialize(This, deploymentInitializeOptions, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResult
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentResult[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CDeploymentStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult* This,
        HRESULT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResultFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IDeploymentResultFactory[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResultFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CDeploymentStatus status,
        HRESULT extendedError,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResult** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_CreateInstance(This, status, extendedError, value) \
    ((This)->lpVtbl->CreateInstance(This, status, extendedError, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIDeploymentResultFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IReleaseInfoStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IReleaseInfoStatics[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IReleaseInfoStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Major)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        UINT16* value);
    HRESULT (STDMETHODCALLTYPE* get_Minor)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        UINT16* value);
    HRESULT (STDMETHODCALLTYPE* get_Patch)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        UINT16* value);
    HRESULT (STDMETHODCALLTYPE* get_VersionTag)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AsString)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_get_Major(This, value) \
    ((This)->lpVtbl->get_Major(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_get_Minor(This, value) \
    ((This)->lpVtbl->get_Minor(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_get_Patch(This, value) \
    ((This)->lpVtbl->get_Patch(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_get_VersionTag(This, value) \
    ((This)->lpVtbl->get_VersionTag(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_get_AsString(This, value) \
    ((This)->lpVtbl->get_AsString(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIReleaseInfoStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeCompatibilityOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IRuntimeCompatibilityOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeCompatibilityOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PatchLevel1)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion* value);
    HRESULT (STDMETHODCALLTYPE* put_PatchLevel1)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion value);
    HRESULT (STDMETHODCALLTYPE* get_PatchLevel2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion* value);
    HRESULT (STDMETHODCALLTYPE* put_PatchLevel2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CWindowsAppRuntimeVersion value);
    HRESULT (STDMETHODCALLTYPE* get_DisabledChanges)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This,
        __FIVector_1_Microsoft__CWindows__CApplicationModel__CWindowsAppRuntime__CRuntimeCompatibilityChange** value);
    HRESULT (STDMETHODCALLTYPE* Apply)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_get_PatchLevel1(This, value) \
    ((This)->lpVtbl->get_PatchLevel1(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_put_PatchLevel1(This, value) \
    ((This)->lpVtbl->put_PatchLevel1(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_get_PatchLevel2(This, value) \
    ((This)->lpVtbl->get_PatchLevel2(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_put_PatchLevel2(This, value) \
    ((This)->lpVtbl->put_PatchLevel2(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_get_DisabledChanges(This, value) \
    ((This)->lpVtbl->get_DisabledChanges(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_Apply(This) \
    ((This)->lpVtbl->Apply(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeCompatibilityOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeInfoStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_IRuntimeInfoStatics[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeInfoStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Version)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This,
        struct __x_ABI_CWindows_CApplicationModel_CPackageVersion* value);
    HRESULT (STDMETHODCALLTYPE* get_AsString)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_get_Version(This, value) \
    ((This)->lpVtbl->get_Version(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_get_AsString(This, value) \
    ((This)->lpVtbl->get_AsString(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CWindowsAppRuntime_CIRuntimeInfoStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 2.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 2.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions ** Default Interface **
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentInitializeOptions2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentInitializeOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentInitializeOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentInitializeOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics2 interface starting with version 2.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentManagerStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentManager[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResultFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IDeploymentResult ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_DeploymentResult[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_DEPLOYMENTCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IReleaseInfoStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_ReleaseInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_ReleaseInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_ReleaseInfo[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeCompatibilityOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeCompatibilityOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeCompatibilityOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeCompatibilityOptions[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_RUNTIMECOMPATIBILITYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo
 *
 * Introduced to Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.IRuntimeInfoStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfoContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_WindowsAppRuntime_RuntimeInfo[] = L"Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_VERSIONINFOCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eapplicationmodel2Ewindowsappruntime_p_h__

#endif // __microsoft2Ewindows2Eapplicationmodel2Ewindowsappruntime_h__
