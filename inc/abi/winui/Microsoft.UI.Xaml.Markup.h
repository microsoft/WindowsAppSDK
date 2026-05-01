
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
#ifndef __microsoft2Eui2Examl2Emarkup_h__
#define __microsoft2Eui2Examl2Emarkup_h__
#ifndef __microsoft2Eui2Examl2Emarkup_p_h__
#define __microsoft2Eui2Examl2Emarkup_p_h__


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
#if !defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)
#define MICROSOFT_UI_XAML_WINUICONTRACT_VERSION 0xa0000
#endif // defined(MICROSOFT_UI_XAML_WINUICONTRACT_VERSION)

#if !defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)
#define MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION 0xa0000
#endif // defined(MICROSOFT_UI_XAML_XAMLCONTRACT_VERSION)

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
#include "Microsoft.UI.Xaml.h"
#include "Windows.Storage.Streams.h"
#include "Windows.UI.Xaml.Interop.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IComponentConnector;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector ABI::Microsoft::UI::Xaml::Markup::IComponentConnector

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IDataTemplateComponent;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent ABI::Microsoft::UI::Xaml::Markup::IDataTemplateComponent

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IMarkupExtension;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension ABI::Microsoft::UI::Xaml::Markup::IMarkupExtension

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IMarkupExtensionFactory;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory ABI::Microsoft::UI::Xaml::Markup::IMarkupExtensionFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IMarkupExtensionOverrides;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides ABI::Microsoft::UI::Xaml::Markup::IMarkupExtensionOverrides

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IProvideValueTarget;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget ABI::Microsoft::UI::Xaml::Markup::IProvideValueTarget

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IProvideValueTargetProperty;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty ABI::Microsoft::UI::Xaml::Markup::IProvideValueTargetProperty

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IRootObjectProvider;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider ABI::Microsoft::UI::Xaml::Markup::IRootObjectProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IUriContext;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext ABI::Microsoft::UI::Xaml::Markup::IUriContext

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlBinaryWriter;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter ABI::Microsoft::UI::Xaml::Markup::IXamlBinaryWriter

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlBinaryWriterStatics;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics ABI::Microsoft::UI::Xaml::Markup::IXamlBinaryWriterStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlBindScopeDiagnostics;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics ABI::Microsoft::UI::Xaml::Markup::IXamlBindScopeDiagnostics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlBindingHelper;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper ABI::Microsoft::UI::Xaml::Markup::IXamlBindingHelper

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlBindingHelperStatics;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics ABI::Microsoft::UI::Xaml::Markup::IXamlBindingHelperStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlCondition;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition ABI::Microsoft::UI::Xaml::Markup::IXamlCondition

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlMarkupHelper;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper ABI::Microsoft::UI::Xaml::Markup::IXamlMarkupHelper

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlMarkupHelperStatics;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics ABI::Microsoft::UI::Xaml::Markup::IXamlMarkupHelperStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlMember;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember ABI::Microsoft::UI::Xaml::Markup::IXamlMember

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlMetadataProvider;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider ABI::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlReader;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader ABI::Microsoft::UI::Xaml::Markup::IXamlReader

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlReaderStatics;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics ABI::Microsoft::UI::Xaml::Markup::IXamlReaderStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlType;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType ABI::Microsoft::UI::Xaml::Markup::IXamlType

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    interface IXamlTypeResolver;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver ABI::Microsoft::UI::Xaml::Markup::IXamlTypeResolver

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            namespace Streams {
                interface IRandomAccessStream;
            } /* Streams */
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream ABI::Windows::Storage::Streams::IRandomAccessStream

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c875446a-587f-58da-897e-3bbe5ec7c30b"))
IIterator<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IIterator_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Storage.Streams.IRandomAccessStream>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::Collections::__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ba666a00-1555-5df4-81a5-07d23f7ffceb"))
IIterable<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IIterable_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Storage.Streams.IRandomAccessStream>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::Collections::__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("92cd0a46-2266-5cd6-9293-e111299f2793"))
IVectorView<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IVectorView_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Windows.Storage.Streams.IRandomAccessStream>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::Collections::__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#define DEF___FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("2736b66b-daa3-5e0c-9842-6a0f44b5440b"))
IVector<ABI::Windows::Storage::Streams::IRandomAccessStream*> : IVector_impl<ABI::Windows::Storage::Streams::IRandomAccessStream*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVector`1<Windows.Storage.Streams.IRandomAccessStream>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVector<ABI::Windows::Storage::Streams::IRandomAccessStream*> __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_t;
#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream ABI::Windows::Foundation::Collections::__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class DependencyObject;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IDependencyObject;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject ABI::Microsoft::UI::Xaml::IDependencyObject

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class DependencyProperty;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IDependencyProperty;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty ABI::Microsoft::UI::Xaml::IDependencyProperty

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IXamlServiceProvider;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider ABI::Microsoft::UI::Xaml::IXamlServiceProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                class UIElement;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                interface IUIElement;
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement ABI::Microsoft::UI::Xaml::IUIElement

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct DateTime DateTime;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Point Point;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Rect Rect;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Size Size;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct TimeSpan TimeSpan;
        } /* Foundation */
    } /* Windows */
} /* ABI */

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
    namespace Windows {
        namespace UI {
            namespace Xaml {
                namespace Interop {
                    typedef struct TypeName TypeName;
                } /* Interop */
            } /* Xaml */
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    typedef struct XamlBinaryWriterErrorInformation XamlBinaryWriterErrorInformation;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    typedef struct XmlnsDefinition XmlnsDefinition;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    class MarkupExtension;
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Markup.XamlBinaryWriterErrorInformation
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    struct XamlBinaryWriterErrorInformation
                    {
                        UINT32 InputStreamIndex;
                        UINT32 LineNumber;
                        UINT32 LinePosition;
                    };
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Markup.XmlnsDefinition
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    struct XmlnsDefinition
                    {
                        HSTRING XmlNamespace;
                        HSTRING Namespace;
                    };
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IComponentConnector
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IComponentConnector[] = L"Microsoft.UI.Xaml.Markup.IComponentConnector";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("ad401812-b091-51d0-b915-2d682cd2af10")
                    IComponentConnector : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Connect(
                            INT32 connectionId,
                            IInspectable* target
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetBindingConnector(
                            INT32 connectionId,
                            IInspectable* target,
                            ABI::Microsoft::UI::Xaml::Markup::IComponentConnector** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IComponentConnector = _uuidof(IComponentConnector);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IDataTemplateComponent
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IDataTemplateComponent[] = L"Microsoft.UI.Xaml.Markup.IDataTemplateComponent";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("1743ddf7-38ba-58c9-a2a6-b0ae28713bee")
                    IDataTemplateComponent : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Recycle(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ProcessBindings(
                            IInspectable* item,
                            INT32 itemIndex,
                            INT32 phase,
                            INT32* nextPhase
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDataTemplateComponent = _uuidof(IDataTemplateComponent);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IMarkupExtension
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IMarkupExtension[] = L"Microsoft.UI.Xaml.Markup.IMarkupExtension";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("c355371e-091d-5136-af4a-baf5e00616bd")
                    IMarkupExtension : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IMarkupExtension = _uuidof(IMarkupExtension);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IMarkupExtensionFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IMarkupExtensionFactory[] = L"Microsoft.UI.Xaml.Markup.IMarkupExtensionFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("20651afa-5f3a-5f0c-adb1-b6551f53a6a0")
                    IMarkupExtensionFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Markup::IMarkupExtension** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IMarkupExtensionFactory = _uuidof(IMarkupExtensionFactory);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IMarkupExtensionOverrides
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IMarkupExtensionOverrides[] = L"Microsoft.UI.Xaml.Markup.IMarkupExtensionOverrides";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("a12aa575-5d31-5b68-a30f-8495412a351d")
                    IMarkupExtensionOverrides : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE ProvideValue(
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ProvideValueWithIXamlServiceProvider(
                            ABI::Microsoft::UI::Xaml::IXamlServiceProvider* serviceProvider,
                            IInspectable** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IMarkupExtensionOverrides = _uuidof(IMarkupExtensionOverrides);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IProvideValueTarget
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IProvideValueTarget[] = L"Microsoft.UI.Xaml.Markup.IProvideValueTarget";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("3f01ff68-3efd-591d-a506-de13fcaabd83")
                    IProvideValueTarget : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TargetObject(
                            IInspectable** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TargetProperty(
                            IInspectable** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IProvideValueTarget = _uuidof(IProvideValueTarget);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IProvideValueTargetProperty
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.ProvideValueTargetProperty
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IProvideValueTargetProperty[] = L"Microsoft.UI.Xaml.Markup.IProvideValueTargetProperty";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("ce777b1f-b42e-59d1-870d-12fdf0629133")
                    IProvideValueTargetProperty : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Name(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Type(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DeclaringType(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IProvideValueTargetProperty = _uuidof(IProvideValueTargetProperty);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IRootObjectProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IRootObjectProvider[] = L"Microsoft.UI.Xaml.Markup.IRootObjectProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("13d63599-352f-5eb8-81c1-bc62fb12d6da")
                    IRootObjectProvider : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RootObject(
                            IInspectable** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IRootObjectProvider = _uuidof(IRootObjectProvider);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IUriContext
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IUriContext[] = L"Microsoft.UI.Xaml.Markup.IUriContext";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("fb8605f6-8f05-52ee-a01c-3a9e118a6ea2")
                    IUriContext : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_BaseUri(
                            ABI::Windows::Foundation::IUriRuntimeClass** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IUriContext = _uuidof(IUriContext);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBinaryWriter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBinaryWriter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBinaryWriter[] = L"Microsoft.UI.Xaml.Markup.IXamlBinaryWriter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("8fb45e3b-e689-55bf-aa11-d83b1c1cdda1")
                    IXamlBinaryWriter : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IXamlBinaryWriter = _uuidof(IXamlBinaryWriter);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBinaryWriterStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBinaryWriter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBinaryWriterStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlBinaryWriterStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("774907fc-c846-517f-abcc-c3f7e8c3ffc9")
                    IXamlBinaryWriterStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Write(
                            __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* inputStreams,
                            __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* outputStreams,
                            ABI::Microsoft::UI::Xaml::Markup::IXamlMetadataProvider* xamlMetadataProvider,
                            ABI::Microsoft::UI::Xaml::Markup::XamlBinaryWriterErrorInformation* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlBinaryWriterStatics = _uuidof(IXamlBinaryWriterStatics);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBindScopeDiagnostics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBindScopeDiagnostics[] = L"Microsoft.UI.Xaml.Markup.IXamlBindScopeDiagnostics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("3ea84e4e-fdfe-55a8-a561-edf5697846d7")
                    IXamlBindScopeDiagnostics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Disable(
                            INT32 lineNumber,
                            INT32 columnNumber
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlBindScopeDiagnostics = _uuidof(IXamlBindScopeDiagnostics);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBindingHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBindingHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBindingHelper[] = L"Microsoft.UI.Xaml.Markup.IXamlBindingHelper";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("607a9bf2-5a6d-5c89-a756-bb44f24f28f8")
                    IXamlBindingHelper : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IXamlBindingHelper = _uuidof(IXamlBindingHelper);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBindingHelperStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBindingHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBindingHelperStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlBindingHelperStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("93c7dad3-f9c2-5372-84dc-9e9c4661d083")
                    IXamlBindingHelperStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_DataTemplateComponentProperty(
                            ABI::Microsoft::UI::Xaml::IDependencyProperty** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetDataTemplateComponent(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::Markup::IDataTemplateComponent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetDataTemplateComponent(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element,
                            ABI::Microsoft::UI::Xaml::Markup::IDataTemplateComponent* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SuspendRendering(
                            ABI::Microsoft::UI::Xaml::IUIElement* target
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ResumeRendering(
                            ABI::Microsoft::UI::Xaml::IUIElement* target
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ConvertValue(
                            ABI::Windows::UI::Xaml::Interop::TypeName type,
                            IInspectable* value,
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromString(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromBoolean(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromChar16(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            WCHAR value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromDateTime(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            ABI::Windows::Foundation::DateTime value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromDouble(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            DOUBLE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromInt32(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromUInt32(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            UINT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromInt64(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            INT64 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromUInt64(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            UINT64 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromSingle(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            FLOAT value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromPoint(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            ABI::Windows::Foundation::Point value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromRect(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            ABI::Windows::Foundation::Rect value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromSize(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            ABI::Windows::Foundation::Size value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromTimeSpan(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            ABI::Windows::Foundation::TimeSpan value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromByte(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            BYTE value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromUri(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            ABI::Windows::Foundation::IUriRuntimeClass* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetPropertyFromObject(
                            IInspectable* dependencyObject,
                            ABI::Microsoft::UI::Xaml::IDependencyProperty* propertyToSet,
                            IInspectable* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlBindingHelperStatics = _uuidof(IXamlBindingHelperStatics);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlCondition
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 10.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xa0000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlCondition[] = L"Microsoft.UI.Xaml.Markup.IXamlCondition";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("9124118d-cdfa-545f-8c12-4cf7bcc5fffa")
                    IXamlCondition : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Evaluate(
                            HSTRING argument,
                            boolean* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlCondition = _uuidof(IXamlCondition);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xa0000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMarkupHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlMarkupHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMarkupHelper[] = L"Microsoft.UI.Xaml.Markup.IXamlMarkupHelper";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("cd677310-3b06-5a13-b31a-401849570858")
                    IXamlMarkupHelper : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IXamlMarkupHelper = _uuidof(IXamlMarkupHelper);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMarkupHelperStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlMarkupHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMarkupHelperStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlMarkupHelperStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("d9a0f6e3-c6cc-5cb6-8999-85788701f339")
                    IXamlMarkupHelperStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE UnloadObject(
                            ABI::Microsoft::UI::Xaml::IDependencyObject* element
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlMarkupHelperStatics = _uuidof(IXamlMarkupHelperStatics);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMember
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMember[] = L"Microsoft.UI.Xaml.Markup.IXamlMember";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("bf3a2913-5c63-50ec-8660-61809be7b9b9")
                    IXamlMember : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsAttachable(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsDependencyProperty(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsReadOnly(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Name(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TargetType(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Type(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetValue(
                            IInspectable* instance,
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetValue(
                            IInspectable* instance,
                            IInspectable* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlMember = _uuidof(IXamlMember);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMetadataProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMetadataProvider[] = L"Microsoft.UI.Xaml.Markup.IXamlMetadataProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("a96251f0-2214-5d53-8746-ce99a2593cd7")
                    IXamlMetadataProvider : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetXamlType(
                            ABI::Windows::UI::Xaml::Interop::TypeName type,
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetXamlTypeByFullName(
                            HSTRING fullName,
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetXmlnsDefinitions(
                            UINT32* resultLength,
                            ABI::Microsoft::UI::Xaml::Markup::XmlnsDefinition** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlMetadataProvider = _uuidof(IXamlMetadataProvider);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlReader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlReader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlReader[] = L"Microsoft.UI.Xaml.Markup.IXamlReader";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("54ce54c8-38c6-50d9-ac98-4b03eddbde9f")
                    IXamlReader : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IXamlReader = _uuidof(IXamlReader);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlReaderStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlReader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlReaderStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlReaderStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("82a4cd9e-435e-5aeb-8c4f-300cece45cae")
                    IXamlReaderStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Load(
                            HSTRING xaml,
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE LoadWithInitialTemplateValidation(
                            HSTRING xaml,
                            IInspectable** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlReaderStatics = _uuidof(IXamlReaderStatics);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlType
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlType[] = L"Microsoft.UI.Xaml.Markup.IXamlType";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("d24219df-7ec9-57f1-a27b-6af251d9c5bc")
                    IXamlType : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_BaseType(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContentProperty(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlMember** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_FullName(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsArray(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsCollection(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsConstructible(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsDictionary(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsMarkupExtension(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsBindable(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ItemType(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_KeyType(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_BoxedType(
                            ABI::Microsoft::UI::Xaml::Markup::IXamlType** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_UnderlyingType(
                            ABI::Windows::UI::Xaml::Interop::TypeName* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE ActivateInstance(
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromString(
                            HSTRING value,
                            IInspectable** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetMember(
                            HSTRING name,
                            ABI::Microsoft::UI::Xaml::Markup::IXamlMember** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddToVector(
                            IInspectable* instance,
                            IInspectable* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddToMap(
                            IInspectable* instance,
                            IInspectable* key,
                            IInspectable* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RunInitializer(void) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlType = _uuidof(IXamlType);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlTypeResolver
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlTypeResolver[] = L"Microsoft.UI.Xaml.Markup.IXamlTypeResolver";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Markup {
                    MIDL_INTERFACE("3fa15615-cacf-547f-b1ed-89dae8c67452")
                    IXamlTypeResolver : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Resolve(
                            HSTRING qualifiedTypeName,
                            ABI::Windows::UI::Xaml::Interop::TypeName* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlTypeResolver = _uuidof(IXamlTypeResolver);
                } /* Markup */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IMarkupExtension ** Default Interface **
 *    Microsoft.UI.Xaml.Markup.IMarkupExtensionOverrides
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_MarkupExtension_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_MarkupExtension_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_MarkupExtension[] = L"Microsoft.UI.Xaml.Markup.MarkupExtension";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.ProvideValueTargetProperty
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IProvideValueTargetProperty ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_ProvideValueTargetProperty_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_ProvideValueTargetProperty_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_ProvideValueTargetProperty[] = L"Microsoft.UI.Xaml.Markup.ProvideValueTargetProperty";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlBinaryWriter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlBinaryWriterStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlBinaryWriter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBinaryWriter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBinaryWriter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlBinaryWriter[] = L"Microsoft.UI.Xaml.Markup.XamlBinaryWriter";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlBindingHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlBindingHelperStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlBindingHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBindingHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBindingHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlBindingHelper[] = L"Microsoft.UI.Xaml.Markup.XamlBindingHelper";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlMarkupHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlMarkupHelperStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlMarkupHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlMarkupHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlMarkupHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlMarkupHelper[] = L"Microsoft.UI.Xaml.Markup.XamlMarkupHelper";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlReader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlReaderStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlReader ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlReader_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlReader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlReader[] = L"Microsoft.UI.Xaml.Markup.XamlReader";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_FWD_DEFINED__

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__)
#define ____FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream;

typedef struct __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 itemsLength,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl;

interface __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream
{
    CONST_VTBL struct __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__)
#define ____FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream;

typedef struct __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream** result);

    END_INTERFACE
} __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl;

interface __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream
{
    CONST_VTBL struct __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream;

typedef struct __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 index,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl;

interface __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream
{
    CONST_VTBL struct __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__)
#define ____FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__

typedef interface __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream;

typedef struct __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 index,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* GetView)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream** result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* SetAt)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 index,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* InsertAt)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 index,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAt)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 index);
    HRESULT (STDMETHODCALLTYPE* Append)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream* value);
    HRESULT (STDMETHODCALLTYPE* RemoveAtEnd)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* Clear)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** items,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* ReplaceAll)(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* This,
        UINT32 itemsLength,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream** items);

    END_INTERFACE
} __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl;

interface __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream
{
    CONST_VTBL struct __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStreamVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetView(This, result) \
    ((This)->lpVtbl->GetView(This, result))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_SetAt(This, index, value) \
    ((This)->lpVtbl->SetAt(This, index, value))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_InsertAt(This, index, value) \
    ((This)->lpVtbl->InsertAt(This, index, value))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_RemoveAt(This, index) \
    ((This)->lpVtbl->RemoveAt(This, index))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_Append(This, value) \
    ((This)->lpVtbl->Append(This, value))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_RemoveAtEnd(This) \
    ((This)->lpVtbl->RemoveAtEnd(This))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_Clear(This) \
    ((This)->lpVtbl->Clear(This))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#define __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_ReplaceAll(This, itemsLength, items) \
    ((This)->lpVtbl->ReplaceAll(This, itemsLength, items))

#endif /* COBJMACROS */

#endif // ____FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider __x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CDateTime __x_ABI_CWindows_CFoundation_CDateTime;

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

typedef struct __x_ABI_CWindows_CFoundation_CSize __x_ABI_CWindows_CFoundation_CSize;

typedef struct __x_ABI_CWindows_CFoundation_CTimeSpan __x_ABI_CWindows_CFoundation_CTimeSpan;

#ifndef ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIUriRuntimeClass __x_ABI_CWindows_CFoundation_CIUriRuntimeClass;

#endif // ____x_ABI_CWindows_CFoundation_CIUriRuntimeClass_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName;

typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXamlBinaryWriterErrorInformation __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXamlBinaryWriterErrorInformation;

typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXmlnsDefinition __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXmlnsDefinition;

/*
 *
 * Struct Microsoft.UI.Xaml.Markup.XamlBinaryWriterErrorInformation
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXamlBinaryWriterErrorInformation
{
    UINT32 InputStreamIndex;
    UINT32 LineNumber;
    UINT32 LinePosition;
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Xaml.Markup.XmlnsDefinition
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXmlnsDefinition
{
    HSTRING XmlNamespace;
    HSTRING Namespace;
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IComponentConnector
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IComponentConnector[] = L"Microsoft.UI.Xaml.Markup.IComponentConnector";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnectorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Connect)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This,
        INT32 connectionId,
        IInspectable* target);
    HRESULT (STDMETHODCALLTYPE* GetBindingConnector)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector* This,
        INT32 connectionId,
        IInspectable* target,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnectorVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnectorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_Connect(This, connectionId, target) \
    ((This)->lpVtbl->Connect(This, connectionId, target))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_GetBindingConnector(This, connectionId, target, result) \
    ((This)->lpVtbl->GetBindingConnector(This, connectionId, target, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIComponentConnector_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IDataTemplateComponent
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IDataTemplateComponent[] = L"Microsoft.UI.Xaml.Markup.IDataTemplateComponent";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponentVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Recycle)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This);
    HRESULT (STDMETHODCALLTYPE* ProcessBindings)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* This,
        IInspectable* item,
        INT32 itemIndex,
        INT32 phase,
        INT32* nextPhase);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponentVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponentVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_Recycle(This) \
    ((This)->lpVtbl->Recycle(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_ProcessBindings(This, item, itemIndex, phase, nextPhase) \
    ((This)->lpVtbl->ProcessBindings(This, item, itemIndex, phase, nextPhase))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IMarkupExtension
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IMarkupExtension[] = L"Microsoft.UI.Xaml.Markup.IMarkupExtension";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IMarkupExtensionFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IMarkupExtensionFactory[] = L"Microsoft.UI.Xaml.Markup.IMarkupExtensionFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtension** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IMarkupExtensionOverrides
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IMarkupExtensionOverrides[] = L"Microsoft.UI.Xaml.Markup.IMarkupExtensionOverrides";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverridesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ProvideValue)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* ProvideValueWithIXamlServiceProvider)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIXamlServiceProvider* serviceProvider,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverridesVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverridesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_ProvideValue(This, result) \
    ((This)->lpVtbl->ProvideValue(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_ProvideValueWithIXamlServiceProvider(This, serviceProvider, result) \
    ((This)->lpVtbl->ProvideValueWithIXamlServiceProvider(This, serviceProvider, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIMarkupExtensionOverrides_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IProvideValueTarget
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IProvideValueTarget[] = L"Microsoft.UI.Xaml.Markup.IProvideValueTarget";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TargetObject)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_TargetProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget* This,
        IInspectable** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_get_TargetObject(This, value) \
    ((This)->lpVtbl->get_TargetObject(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_get_TargetProperty(This, value) \
    ((This)->lpVtbl->get_TargetProperty(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTarget_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IProvideValueTargetProperty
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.ProvideValueTargetProperty
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IProvideValueTargetProperty[] = L"Microsoft.UI.Xaml.Markup.IProvideValueTargetProperty";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetPropertyVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Type)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);
    HRESULT (STDMETHODCALLTYPE* get_DeclaringType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetPropertyVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetPropertyVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_get_Type(This, value) \
    ((This)->lpVtbl->get_Type(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_get_DeclaringType(This, value) \
    ((This)->lpVtbl->get_DeclaringType(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIProvideValueTargetProperty_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IRootObjectProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IRootObjectProvider[] = L"Microsoft.UI.Xaml.Markup.IRootObjectProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RootObject)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider* This,
        IInspectable** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_get_RootObject(This, value) \
    ((This)->lpVtbl->get_RootObject(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIRootObjectProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IUriContext
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IUriContext[] = L"Microsoft.UI.Xaml.Markup.IUriContext";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_BaseUri)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext* This,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContextVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_get_BaseUri(This, value) \
    ((This)->lpVtbl->get_BaseUri(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIUriContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBinaryWriter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBinaryWriter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBinaryWriter[] = L"Microsoft.UI.Xaml.Markup.IXamlBinaryWriter";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBinaryWriterStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBinaryWriter
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBinaryWriterStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlBinaryWriterStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Write)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics* This,
        __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* inputStreams,
        __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream* outputStreams,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* xamlMetadataProvider,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXamlBinaryWriterErrorInformation* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_Write(This, inputStreams, outputStreams, xamlMetadataProvider, result) \
    ((This)->lpVtbl->Write(This, inputStreams, outputStreams, xamlMetadataProvider, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBinaryWriterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBindScopeDiagnostics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBindScopeDiagnostics[] = L"Microsoft.UI.Xaml.Markup.IXamlBindScopeDiagnostics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnosticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Disable)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics* This,
        INT32 lineNumber,
        INT32 columnNumber);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnosticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnosticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_Disable(This, lineNumber, columnNumber) \
    ((This)->lpVtbl->Disable(This, lineNumber, columnNumber))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindScopeDiagnostics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBindingHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBindingHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBindingHelper[] = L"Microsoft.UI.Xaml.Markup.IXamlBindingHelper";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlBindingHelperStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlBindingHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlBindingHelperStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlBindingHelperStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DataTemplateComponentProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty** value);
    HRESULT (STDMETHODCALLTYPE* GetDataTemplateComponent)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent** result);
    HRESULT (STDMETHODCALLTYPE* SetDataTemplateComponent)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIDataTemplateComponent* value);
    HRESULT (STDMETHODCALLTYPE* SuspendRendering)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* target);
    HRESULT (STDMETHODCALLTYPE* ResumeRendering)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* target);
    HRESULT (STDMETHODCALLTYPE* ConvertValue)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName type,
        IInspectable* value,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromString)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromBoolean)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromChar16)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        WCHAR value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromDateTime)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        struct __x_ABI_CWindows_CFoundation_CDateTime value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromDouble)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        DOUBLE value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromInt32)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromUInt32)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        UINT32 value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromInt64)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        INT64 value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromUInt64)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        UINT64 value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromSingle)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromPoint)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        struct __x_ABI_CWindows_CFoundation_CPoint value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromRect)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        struct __x_ABI_CWindows_CFoundation_CRect value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromSize)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        struct __x_ABI_CWindows_CFoundation_CSize value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromTimeSpan)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromByte)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        BYTE value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromUri)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        __x_ABI_CWindows_CFoundation_CIUriRuntimeClass* value);
    HRESULT (STDMETHODCALLTYPE* SetPropertyFromObject)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics* This,
        IInspectable* dependencyObject,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyProperty* propertyToSet,
        IInspectable* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_get_DataTemplateComponentProperty(This, value) \
    ((This)->lpVtbl->get_DataTemplateComponentProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_GetDataTemplateComponent(This, element, result) \
    ((This)->lpVtbl->GetDataTemplateComponent(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetDataTemplateComponent(This, element, value) \
    ((This)->lpVtbl->SetDataTemplateComponent(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SuspendRendering(This, target) \
    ((This)->lpVtbl->SuspendRendering(This, target))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_ResumeRendering(This, target) \
    ((This)->lpVtbl->ResumeRendering(This, target))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_ConvertValue(This, type, value, result) \
    ((This)->lpVtbl->ConvertValue(This, type, value, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromString(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromString(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromBoolean(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromBoolean(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromChar16(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromChar16(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromDateTime(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromDateTime(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromDouble(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromDouble(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromInt32(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromInt32(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromUInt32(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromUInt32(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromInt64(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromInt64(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromUInt64(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromUInt64(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromSingle(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromSingle(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromPoint(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromPoint(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromRect(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromRect(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromSize(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromSize(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromTimeSpan(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromTimeSpan(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromByte(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromByte(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromUri(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromUri(This, dependencyObject, propertyToSet, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_SetPropertyFromObject(This, dependencyObject, propertyToSet, value) \
    ((This)->lpVtbl->SetPropertyFromObject(This, dependencyObject, propertyToSet, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlBindingHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlCondition
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 10.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xa0000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlCondition[] = L"Microsoft.UI.Xaml.Markup.IXamlCondition";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlConditionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Evaluate)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition* This,
        HSTRING argument,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlConditionVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlConditionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_Evaluate(This, argument, result) \
    ((This)->lpVtbl->Evaluate(This, argument, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlCondition_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0xa0000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMarkupHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlMarkupHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMarkupHelper[] = L"Microsoft.UI.Xaml.Markup.IXamlMarkupHelper";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelper_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMarkupHelperStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlMarkupHelper
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMarkupHelperStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlMarkupHelperStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* UnloadObject)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIDependencyObject* element);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_UnloadObject(This, element) \
    ((This)->lpVtbl->UnloadObject(This, element))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMarkupHelperStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMember
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMember[] = L"Microsoft.UI.Xaml.Markup.IXamlMember";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMemberVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsAttachable)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsDependencyProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsReadOnly)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Name)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_TargetType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** value);
    HRESULT (STDMETHODCALLTYPE* get_Type)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** value);
    HRESULT (STDMETHODCALLTYPE* GetValue)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        IInspectable* instance,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* SetValue)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember* This,
        IInspectable* instance,
        IInspectable* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMemberVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMemberVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_get_IsAttachable(This, value) \
    ((This)->lpVtbl->get_IsAttachable(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_get_IsDependencyProperty(This, value) \
    ((This)->lpVtbl->get_IsDependencyProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_get_IsReadOnly(This, value) \
    ((This)->lpVtbl->get_IsReadOnly(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_get_Name(This, value) \
    ((This)->lpVtbl->get_Name(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_get_TargetType(This, value) \
    ((This)->lpVtbl->get_TargetType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_get_Type(This, value) \
    ((This)->lpVtbl->get_Type(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_GetValue(This, instance, result) \
    ((This)->lpVtbl->GetValue(This, instance, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_SetValue(This, instance, value) \
    ((This)->lpVtbl->SetValue(This, instance, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlMetadataProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlMetadataProvider[] = L"Microsoft.UI.Xaml.Markup.IXamlMetadataProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetXamlType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName type,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** result);
    HRESULT (STDMETHODCALLTYPE* GetXamlTypeByFullName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        HSTRING fullName,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** result);
    HRESULT (STDMETHODCALLTYPE* GetXmlnsDefinitions)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider* This,
        UINT32* resultLength,
        struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CXmlnsDefinition** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_GetXamlType(This, type, result) \
    ((This)->lpVtbl->GetXamlType(This, type, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_GetXamlTypeByFullName(This, fullName, result) \
    ((This)->lpVtbl->GetXamlTypeByFullName(This, fullName, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_GetXmlnsDefinitions(This, resultLength, result) \
    ((This)->lpVtbl->GetXmlnsDefinitions(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMetadataProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlReader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlReader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlReader[] = L"Microsoft.UI.Xaml.Markup.IXamlReader";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlReaderStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Markup.XamlReader
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlReaderStatics[] = L"Microsoft.UI.Xaml.Markup.IXamlReaderStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Load)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This,
        HSTRING xaml,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* LoadWithInitialTemplateValidation)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics* This,
        HSTRING xaml,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_Load(This, xaml, result) \
    ((This)->lpVtbl->Load(This, xaml, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_LoadWithInitialTemplateValidation(This, xaml, result) \
    ((This)->lpVtbl->LoadWithInitialTemplateValidation(This, xaml, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlReaderStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlType
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlType[] = L"Microsoft.UI.Xaml.Markup.IXamlType";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_BaseType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** value);
    HRESULT (STDMETHODCALLTYPE* get_ContentProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember** value);
    HRESULT (STDMETHODCALLTYPE* get_FullName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_IsArray)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsCollection)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsConstructible)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsDictionary)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsMarkupExtension)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsBindable)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ItemType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** value);
    HRESULT (STDMETHODCALLTYPE* get_KeyType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** value);
    HRESULT (STDMETHODCALLTYPE* get_BoxedType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType** value);
    HRESULT (STDMETHODCALLTYPE* get_UnderlyingType)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* value);
    HRESULT (STDMETHODCALLTYPE* ActivateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromString)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        HSTRING value,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* GetMember)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        HSTRING name,
        __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlMember** result);
    HRESULT (STDMETHODCALLTYPE* AddToVector)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        IInspectable* instance,
        IInspectable* value);
    HRESULT (STDMETHODCALLTYPE* AddToMap)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This,
        IInspectable* instance,
        IInspectable* key,
        IInspectable* value);
    HRESULT (STDMETHODCALLTYPE* RunInitializer)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_BaseType(This, value) \
    ((This)->lpVtbl->get_BaseType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_ContentProperty(This, value) \
    ((This)->lpVtbl->get_ContentProperty(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_FullName(This, value) \
    ((This)->lpVtbl->get_FullName(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_IsArray(This, value) \
    ((This)->lpVtbl->get_IsArray(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_IsCollection(This, value) \
    ((This)->lpVtbl->get_IsCollection(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_IsConstructible(This, value) \
    ((This)->lpVtbl->get_IsConstructible(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_IsDictionary(This, value) \
    ((This)->lpVtbl->get_IsDictionary(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_IsMarkupExtension(This, value) \
    ((This)->lpVtbl->get_IsMarkupExtension(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_IsBindable(This, value) \
    ((This)->lpVtbl->get_IsBindable(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_ItemType(This, value) \
    ((This)->lpVtbl->get_ItemType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_KeyType(This, value) \
    ((This)->lpVtbl->get_KeyType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_BoxedType(This, value) \
    ((This)->lpVtbl->get_BoxedType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_get_UnderlyingType(This, value) \
    ((This)->lpVtbl->get_UnderlyingType(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_ActivateInstance(This, result) \
    ((This)->lpVtbl->ActivateInstance(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_CreateFromString(This, value, result) \
    ((This)->lpVtbl->CreateFromString(This, value, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_GetMember(This, name, result) \
    ((This)->lpVtbl->GetMember(This, name, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_AddToVector(This, instance, value) \
    ((This)->lpVtbl->AddToVector(This, instance, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_AddToMap(This, instance, key, value) \
    ((This)->lpVtbl->AddToMap(This, instance, key, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_RunInitializer(This) \
    ((This)->lpVtbl->RunInitializer(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlType_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Markup.IXamlTypeResolver
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Markup_IXamlTypeResolver[] = L"Microsoft.UI.Xaml.Markup.IXamlTypeResolver";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolverVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Resolve)(__x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver* This,
        HSTRING qualifiedTypeName,
        struct __x_ABI_CWindows_CUI_CXaml_CInterop_CTypeName* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolverVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolverVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_Resolve(This, qualifiedTypeName, result) \
    ((This)->lpVtbl->Resolve(This, qualifiedTypeName, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CMarkup_CIXamlTypeResolver_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.MarkupExtension
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IMarkupExtension ** Default Interface **
 *    Microsoft.UI.Xaml.Markup.IMarkupExtensionOverrides
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_MarkupExtension_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_MarkupExtension_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_MarkupExtension[] = L"Microsoft.UI.Xaml.Markup.MarkupExtension";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.ProvideValueTargetProperty
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IProvideValueTargetProperty ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_ProvideValueTargetProperty_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_ProvideValueTargetProperty_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_ProvideValueTargetProperty[] = L"Microsoft.UI.Xaml.Markup.ProvideValueTargetProperty";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlBinaryWriter
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlBinaryWriterStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlBinaryWriter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBinaryWriter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBinaryWriter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlBinaryWriter[] = L"Microsoft.UI.Xaml.Markup.XamlBinaryWriter";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlBindingHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlBindingHelperStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlBindingHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBindingHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlBindingHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlBindingHelper[] = L"Microsoft.UI.Xaml.Markup.XamlBindingHelper";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlMarkupHelper
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlMarkupHelperStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlMarkupHelper ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlMarkupHelper_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlMarkupHelper_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlMarkupHelper[] = L"Microsoft.UI.Xaml.Markup.XamlMarkupHelper";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Markup.XamlReader
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Markup.IXamlReaderStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Markup.IXamlReader ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlReader_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Markup_XamlReader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Markup_XamlReader[] = L"Microsoft.UI.Xaml.Markup.XamlReader";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Emarkup_p_h__

#endif // __microsoft2Eui2Examl2Emarkup_h__
