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
#ifndef __microsoft2Ewindows2Eapplicationmodel2Edynamicdependency_h__
#define __microsoft2Ewindows2Eapplicationmodel2Edynamicdependency_h__
#ifndef __microsoft2Ewindows2Eapplicationmodel2Edynamicdependency_p_h__
#define __microsoft2Ewindows2Eapplicationmodel2Edynamicdependency_p_h__


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

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
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

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IPackageDependency;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependency

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IPackageDependencyContext;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyContext

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IPackageDependencyContextFactory;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyContextFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IPackageDependencyRankStatics;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyRankStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IPackageDependencyStatics;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    interface IPackageDependencyStatics2;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2 ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyStatics2

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
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
                namespace DynamicDependency {
                    typedef enum PackageDependencyLifetimeArtifactKind : int PackageDependencyLifetimeArtifactKind;
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
                    class AddPackageDependencyOptions;
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
                    class CreatePackageDependencyOptions;
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
                    class PackageDependency;
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
                    class PackageDependencyContext;
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeArtifactKind
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    enum PackageDependencyLifetimeArtifactKind : int
                    {
                        PackageDependencyLifetimeArtifactKind_Process = 0,
                        PackageDependencyLifetimeArtifactKind_FilePath = 1,
                        PackageDependencyLifetimeArtifactKind_RegistryKey = 2,
                    };
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    enum PackageDependencyProcessorArchitectures : unsigned int
                    {
                        PackageDependencyProcessorArchitectures_None = 0,
                        PackageDependencyProcessorArchitectures_Neutral = 0x1,
                        PackageDependencyProcessorArchitectures_X86 = 0x2,
                        PackageDependencyProcessorArchitectures_X64 = 0x4,
                        PackageDependencyProcessorArchitectures_Arm = 0x8,
                        PackageDependencyProcessorArchitectures_Arm64 = 0x10,
                        PackageDependencyProcessorArchitectures_X86OnArm64 = 0x20,
                    };

                    DEFINE_ENUM_FLAG_OPERATORS(PackageDependencyProcessorArchitectures)
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContextId
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    struct PackageDependencyContextId
                    {
                        UINT64 Id;
                    };
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IAddPackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IAddPackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IAddPackageDependencyOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("01b801fd-24e3-5e6b-9f1c-805ab410b604")
                    IAddPackageDependencyOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Rank(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Rank(
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PrependIfRankCollision(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_PrependIfRankCollision(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAddPackageDependencyOptions = _uuidof(IAddPackageDependencyOptions);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.ICreatePackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_ICreatePackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.ICreatePackageDependencyOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("cdbb820f-3c69-55dc-a017-b4132574c5d6")
                    ICreatePackageDependencyOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Architectures(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Architectures(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_VerifyDependencyResolution(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_VerifyDependencyResolution(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LifetimeArtifactKind(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LifetimeArtifactKind(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LifetimeArtifact(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_LifetimeArtifact(
                            HSTRING value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ICreatePackageDependencyOptions = _uuidof(ICreatePackageDependencyOptions);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependency
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependency[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependency";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("32ae7b95-e358-5a48-9669-c97d85ad6556")
                    IPackageDependency : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Id(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Delete(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Add(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyContext** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Add2(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IAddPackageDependencyOptions* options,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyContext** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDependency = _uuidof(IPackageDependency);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyContext[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContext";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("9902c35a-a3f5-5645-af0f-cdf9fca00d5e")
                    IPackageDependencyContext : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ContextId(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageDependencyId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PackageFullName(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Remove(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDependencyContext = _uuidof(IPackageDependencyContext);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContextFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyContextFactory[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContextFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("9914f24f-bebf-516b-adab-5c3e8bf323f8")
                    IPackageDependencyContextFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId contextId,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependencyContext** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDependencyContextFactory = _uuidof(IPackageDependencyContextFactory);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyRankStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyRankStatics[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyRankStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("260583bd-a4ab-53fd-a190-c446bfdb5384")
                    IPackageDependencyRankStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Default(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDependencyRankStatics = _uuidof(IPackageDependencyRankStatics);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyStatics[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("17b656e1-1a58-5f3c-84a8-4430f6e749c2")
                    IPackageDependencyStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetFromId(
                            HSTRING id,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependency** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetFromIdForSystem(
                            HSTRING id,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependency** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Create(
                            HSTRING packageFamilyName,
                            ABI::Windows::ApplicationModel::PackageVersion minVersion,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependency** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Create2(
                            HSTRING packageFamilyName,
                            ABI::Windows::ApplicationModel::PackageVersion minVersion,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::ICreatePackageDependencyOptions* options,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependency** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateForSystem(
                            HSTRING packageFamilyName,
                            ABI::Windows::ApplicationModel::PackageVersion minVersion,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::ICreatePackageDependencyOptions* options,
                            ABI::Microsoft::Windows::ApplicationModel::DynamicDependency::IPackageDependency** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_GenerationId(
                            UINT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDependencyStatics = _uuidof(IPackageDependencyStatics);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyStatics2[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace ApplicationModel {
                namespace DynamicDependency {
                    MIDL_INTERFACE("c7c6e4f3-c0ca-5fdb-bef2-57e6020ffe4e")
                    IPackageDependencyStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_PackageGraphRevisionId(
                            UINT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IPackageDependencyStatics2 = _uuidof(IPackageDependencyStatics2);
                } /* DynamicDependency */
            } /* ApplicationModel */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.IAddPackageDependencyOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_AddPackageDependencyOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_AddPackageDependencyOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_AddPackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.ICreatePackageDependencyOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_CreatePackageDependencyOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_CreatePackageDependencyOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_CreatePackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics2 interface starting with version 2.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependency ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependency_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependency_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependency[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContextFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContext ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyContext[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyRankStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyRank_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyRank_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyRank[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2 __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2;

#endif // ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef struct __x_ABI_CWindows_CApplicationModel_CPackageVersion __x_ABI_CWindows_CApplicationModel_CPackageVersion;

typedef enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyLifetimeArtifactKind __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyLifetimeArtifactKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures;

typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId;

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeArtifactKind
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyLifetimeArtifactKind
{
    PackageDependencyLifetimeArtifactKind_Process = 0,
    PackageDependencyLifetimeArtifactKind_FilePath = 1,
    PackageDependencyLifetimeArtifactKind_RegistryKey = 2,
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures
{
    PackageDependencyProcessorArchitectures_None = 0,
    PackageDependencyProcessorArchitectures_Neutral = 0x1,
    PackageDependencyProcessorArchitectures_X86 = 0x2,
    PackageDependencyProcessorArchitectures_X64 = 0x4,
    PackageDependencyProcessorArchitectures_Arm = 0x8,
    PackageDependencyProcessorArchitectures_Arm64 = 0x10,
    PackageDependencyProcessorArchitectures_X86OnArm64 = 0x20,
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContextId
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId
{
    UINT64 Id;
};
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IAddPackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IAddPackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IAddPackageDependencyOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Rank)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_Rank)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* get_PrependIfRankCollision)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_PrependIfRankCollision)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_get_Rank(This, value) \
    ((This)->lpVtbl->get_Rank(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_put_Rank(This, value) \
    ((This)->lpVtbl->put_Rank(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_get_PrependIfRankCollision(This, value) \
    ((This)->lpVtbl->get_PrependIfRankCollision(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_put_PrependIfRankCollision(This, value) \
    ((This)->lpVtbl->put_PrependIfRankCollision(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.ICreatePackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_ICreatePackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.ICreatePackageDependencyOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Architectures)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures* value);
    HRESULT (STDMETHODCALLTYPE* put_Architectures)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyProcessorArchitectures value);
    HRESULT (STDMETHODCALLTYPE* get_VerifyDependencyResolution)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_VerifyDependencyResolution)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_LifetimeArtifactKind)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyLifetimeArtifactKind* value);
    HRESULT (STDMETHODCALLTYPE* put_LifetimeArtifactKind)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyLifetimeArtifactKind value);
    HRESULT (STDMETHODCALLTYPE* get_LifetimeArtifact)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_LifetimeArtifact)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_get_Architectures(This, value) \
    ((This)->lpVtbl->get_Architectures(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_put_Architectures(This, value) \
    ((This)->lpVtbl->put_Architectures(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_get_VerifyDependencyResolution(This, value) \
    ((This)->lpVtbl->get_VerifyDependencyResolution(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_put_VerifyDependencyResolution(This, value) \
    ((This)->lpVtbl->put_VerifyDependencyResolution(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_get_LifetimeArtifactKind(This, value) \
    ((This)->lpVtbl->get_LifetimeArtifactKind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_put_LifetimeArtifactKind(This, value) \
    ((This)->lpVtbl->put_LifetimeArtifactKind(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_get_LifetimeArtifact(This, value) \
    ((This)->lpVtbl->get_LifetimeArtifact(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_put_LifetimeArtifact(This, value) \
    ((This)->lpVtbl->put_LifetimeArtifact(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependency
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependency[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependency";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* Delete)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This);
    HRESULT (STDMETHODCALLTYPE* Add)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext** result);
    HRESULT (STDMETHODCALLTYPE* Add2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency* This,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIAddPackageDependencyOptions* options,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_Delete(This) \
    ((This)->lpVtbl->Delete(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_Add(This, result) \
    ((This)->lpVtbl->Add(This, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_Add2(This, options, result) \
    ((This)->lpVtbl->Add2(This, options, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyContext[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContext";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ContextId)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId* value);
    HRESULT (STDMETHODCALLTYPE* get_PackageDependencyId)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_PackageFullName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* Remove)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_get_ContextId(This, value) \
    ((This)->lpVtbl->get_ContextId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_get_PackageDependencyId(This, value) \
    ((This)->lpVtbl->get_PackageDependencyId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_get_PackageFullName(This, value) \
    ((This)->lpVtbl->get_PackageFullName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_Remove(This) \
    ((This)->lpVtbl->Remove(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContextFactory
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyContextFactory[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContextFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory* This,
        struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CPackageDependencyContextId contextId,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContext** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_CreateInstance(This, contextId, value) \
    ((This)->lpVtbl->CreateInstance(This, contextId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyContextFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyRankStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyRankStatics[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyRankStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Default)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_get_Default(This, value) \
    ((This)->lpVtbl->get_Default(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyRankStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyStatics[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetFromId)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        HSTRING id,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency** result);
    HRESULT (STDMETHODCALLTYPE* GetFromIdForSystem)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        HSTRING id,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency** result);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        HSTRING packageFamilyName,
        struct __x_ABI_CWindows_CApplicationModel_CPackageVersion minVersion,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency** result);
    HRESULT (STDMETHODCALLTYPE* Create2)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        HSTRING packageFamilyName,
        struct __x_ABI_CWindows_CApplicationModel_CPackageVersion minVersion,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* options,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency** result);
    HRESULT (STDMETHODCALLTYPE* CreateForSystem)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        HSTRING packageFamilyName,
        struct __x_ABI_CWindows_CApplicationModel_CPackageVersion minVersion,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CICreatePackageDependencyOptions* options,
        __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependency** result);
    HRESULT (STDMETHODCALLTYPE* get_GenerationId)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics* This,
        UINT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_GetFromId(This, id, result) \
    ((This)->lpVtbl->GetFromId(This, id, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_GetFromIdForSystem(This, id, result) \
    ((This)->lpVtbl->GetFromIdForSystem(This, id, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_Create(This, packageFamilyName, minVersion, result) \
    ((This)->lpVtbl->Create(This, packageFamilyName, minVersion, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_Create2(This, packageFamilyName, minVersion, options, result) \
    ((This)->lpVtbl->Create2(This, packageFamilyName, minVersion, options, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_CreateForSystem(This, packageFamilyName, minVersion, options, result) \
    ((This)->lpVtbl->CreateForSystem(This, packageFamilyName, minVersion, options, result))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_get_GenerationId(This, value) \
    ((This)->lpVtbl->get_GenerationId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics2
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_ApplicationModel_DynamicDependency_IPackageDependencyStatics2[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics2";
typedef struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PackageGraphRevisionId)(__x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2* This,
        UINT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_get_PackageGraphRevisionId(This, value) \
    ((This)->lpVtbl->get_PackageGraphRevisionId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CApplicationModel_CDynamicDependency_CIPackageDependencyStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.IAddPackageDependencyOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_AddPackageDependencyOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_AddPackageDependencyOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_AddPackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.ICreatePackageDependencyOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_CreatePackageDependencyOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_CreatePackageDependencyOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_CreatePackageDependencyOptions[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyStatics2 interface starting with version 2.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependency ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependency_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependency_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependency[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContextFactory interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyContext ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyContext[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank
 *
 * Introduced to Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.ApplicationModel.DynamicDependency.IPackageDependencyRankStatics interface starting with version 1.0 of the Microsoft.Windows.ApplicationModel.DynamicDependency.DynamicDependencyContract API contract
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyRank_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyRank_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_ApplicationModel_DynamicDependency_PackageDependencyRank[] = L"Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyRank";
#endif
#endif // MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_DYNAMICDEPENDENCYCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Eapplicationmodel2Edynamicdependency_p_h__

#endif // __microsoft2Ewindows2Eapplicationmodel2Edynamicdependency_h__
