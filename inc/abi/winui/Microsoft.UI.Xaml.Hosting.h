
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
#ifndef __microsoft2Eui2Examl2Ehosting_h__
#define __microsoft2Eui2Examl2Ehosting_h__
#ifndef __microsoft2Eui2Examl2Ehosting_p_h__
#define __microsoft2Eui2Examl2Ehosting_p_h__


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
#include "Microsoft.UI.h"
#include "Microsoft.UI.Composition.h"
#include "Microsoft.UI.Content.h"
#include "Microsoft.UI.Xaml.h"
#include "Microsoft.UI.Xaml.Controls.h"
#include "Microsoft.UI.Xaml.Media.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IDesktopWindowXamlSource;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSource

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IDesktopWindowXamlSource2;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2 ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSource2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IDesktopWindowXamlSourceFactory;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSourceFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IDesktopWindowXamlSourceGotFocusEventArgs;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSourceGotFocusEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IDesktopWindowXamlSourceTakeFocusRequestedEventArgs;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSourceTakeFocusRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IElementCompositionPreview;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview ABI::Microsoft::UI::Xaml::Hosting::IElementCompositionPreview

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IElementCompositionPreviewStatics;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics ABI::Microsoft::UI::Xaml::Hosting::IElementCompositionPreviewStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IWindowsXamlManager;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManager

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IWindowsXamlManager2;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2 ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManager2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IWindowsXamlManagerStatics;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManagerStatics

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IWindowsXamlManagerStatics2;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2 ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManagerStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IXamlShutdownCompletedOnThreadEventArgs;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs ABI::Microsoft::UI::Xaml::Hosting::IXamlShutdownCompletedOnThreadEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IXamlSourceFocusNavigationRequest;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IXamlSourceFocusNavigationRequestFactory;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequestFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IXamlSourceFocusNavigationResult;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationResult

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    interface IXamlSourceFocusNavigationResultFactory;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationResultFactory

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class DesktopWindowXamlSource;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class DesktopWindowXamlSourceGotFocusEventArgs;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("819741f0-1d2d-5731-9489-6bac155a9ef9"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource*, ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSourceGotFocusEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource*, ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSource*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSourceGotFocusEventArgs*, ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSourceGotFocusEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource, Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource*, ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSourceGotFocusEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class DesktopWindowXamlSourceTakeFocusRequestedEventArgs;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("a16513ab-cc2e-57a0-9b6a-0ce9f4837285"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource*, ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource*, ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSource*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs*, ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSourceTakeFocusRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource, Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSource*, ABI::Microsoft::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class WindowsXamlManager;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class XamlShutdownCompletedOnThreadEventArgs;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1056f3f8-d8b3-58ea-b256-490450626c55"))
ITypedEventHandler<ABI::Microsoft::UI::Xaml::Hosting::WindowsXamlManager*, ABI::Microsoft::UI::Xaml::Hosting::XamlShutdownCompletedOnThreadEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Hosting::WindowsXamlManager*, ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManager*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Xaml::Hosting::XamlShutdownCompletedOnThreadEventArgs*, ABI::Microsoft::UI::Xaml::Hosting::IXamlShutdownCompletedOnThreadEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Xaml.Hosting.WindowsXamlManager, Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Xaml::Hosting::WindowsXamlManager*, ABI::Microsoft::UI::Xaml::Hosting::XamlShutdownCompletedOnThreadEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_USE */

#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class CompositionPropertySet;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositionPropertySet;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet ABI::Microsoft::UI::Composition::ICompositionPropertySet

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositionAnimationBase;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase ABI::Microsoft::UI::Composition::ICompositionAnimationBase

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class Visual;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IVisual;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIVisual ABI::Microsoft::UI::Composition::IVisual

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class DesktopChildSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopChildSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge ABI::Microsoft::UI::Content::IDesktopChildSiteBridge

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Controls {
                    class ScrollViewer;
                } /* Controls */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Controls {
                    interface IScrollViewer;
                } /* Controls */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer ABI::Microsoft::UI::Xaml::Controls::IScrollViewer

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    class SystemBackdrop;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Media {
                    interface ISystemBackdrop;
                } /* Media */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop ABI::Microsoft::UI::Xaml::Media::ISystemBackdrop

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop_FWD_DEFINED__

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
            class Deferral;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IDeferral;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIDeferral ABI::Windows::Foundation::IDeferral

#endif // ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__

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
        namespace Foundation {
            typedef struct Rect Rect;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    typedef enum XamlSourceFocusNavigationReason : int XamlSourceFocusNavigationReason;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class XamlSourceFocusNavigationRequest;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    class XamlSourceFocusNavigationResult;
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationReason
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    enum XamlSourceFocusNavigationReason : int
                    {
                        XamlSourceFocusNavigationReason_Programmatic = 0,
                        XamlSourceFocusNavigationReason_Restore = 1,
                        XamlSourceFocusNavigationReason_First = 3,
                        XamlSourceFocusNavigationReason_Last = 4,
                        XamlSourceFocusNavigationReason_Left = 7,
                        XamlSourceFocusNavigationReason_Up = 8,
                        XamlSourceFocusNavigationReason_Right = 9,
                        XamlSourceFocusNavigationReason_Down = 10,
                    };
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSource[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("553af92c-1381-51d6-bee0-f34beb042ea8")
                    IDesktopWindowXamlSource : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Content(
                            ABI::Microsoft::UI::Xaml::IUIElement** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Content(
                            ABI::Microsoft::UI::Xaml::IUIElement* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HasFocus(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SystemBackdrop(
                            ABI::Microsoft::UI::Xaml::Media::ISystemBackdrop** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SystemBackdrop(
                            ABI::Microsoft::UI::Xaml::Media::ISystemBackdrop* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_SiteBridge(
                            ABI::Microsoft::UI::Content::IDesktopChildSiteBridge** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_TakeFocusRequested(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_TakeFocusRequested(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_GotFocus(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_GotFocus(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE NavigateFocus(
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest* request,
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Initialize(
                            ABI::Microsoft::UI::WindowId parentWindowId
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopWindowXamlSource = _uuidof(IDesktopWindowXamlSource);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSource2[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("fb02b9f1-8588-5bd3-8951-4664a675d872")
                    IDesktopWindowXamlSource2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ShouldConstrainPopupsToWorkArea(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ShouldConstrainPopupsToWorkArea(
                            boolean value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopWindowXamlSource2 = _uuidof(IDesktopWindowXamlSource2);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSourceFactory[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("7d2db617-14e7-5d49-aeec-ae10887e595d")
                    IDesktopWindowXamlSourceFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            IInspectable* baseInterface,
                            IInspectable** innerInterface,
                            ABI::Microsoft::UI::Xaml::Hosting::IDesktopWindowXamlSource** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopWindowXamlSourceFactory = _uuidof(IDesktopWindowXamlSourceFactory);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSourceGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceGotFocusEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("cc63d863-2071-5f6b-aef9-c0ba35f3b8df")
                    IDesktopWindowXamlSourceGotFocusEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Request(
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopWindowXamlSourceGotFocusEventArgs = _uuidof(IDesktopWindowXamlSourceGotFocusEventArgs);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceTakeFocusRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSourceTakeFocusRequestedEventArgs[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceTakeFocusRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("4f5a0e2c-4ddc-5c03-939f-6f3bda560363")
                    IDesktopWindowXamlSourceTakeFocusRequestedEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Request(
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDesktopWindowXamlSourceTakeFocusRequestedEventArgs = _uuidof(IDesktopWindowXamlSourceTakeFocusRequestedEventArgs);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IElementCompositionPreview
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.ElementCompositionPreview
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IElementCompositionPreview[] = L"Microsoft.UI.Xaml.Hosting.IElementCompositionPreview";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("c8ad1ef4-a93f-5a25-85bd-7c498d9856d3")
                    IElementCompositionPreview : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IElementCompositionPreview = _uuidof(IElementCompositionPreview);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IElementCompositionPreviewStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.ElementCompositionPreview
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IElementCompositionPreviewStatics[] = L"Microsoft.UI.Xaml.Hosting.IElementCompositionPreviewStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("84da5a6c-0cfa-532b-9b15-ccd986374342")
                    IElementCompositionPreviewStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetElementVisual(
                            ABI::Microsoft::UI::Xaml::IUIElement* element,
                            ABI::Microsoft::UI::Composition::IVisual** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetElementChildVisual(
                            ABI::Microsoft::UI::Xaml::IUIElement* element,
                            ABI::Microsoft::UI::Composition::IVisual** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetElementChildVisual(
                            ABI::Microsoft::UI::Xaml::IUIElement* element,
                            ABI::Microsoft::UI::Composition::IVisual* visual
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetScrollViewerManipulationPropertySet(
                            ABI::Microsoft::UI::Xaml::Controls::IScrollViewer* scrollViewer,
                            ABI::Microsoft::UI::Composition::ICompositionPropertySet** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetImplicitShowAnimation(
                            ABI::Microsoft::UI::Xaml::IUIElement* element,
                            ABI::Microsoft::UI::Composition::ICompositionAnimationBase* animation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetImplicitHideAnimation(
                            ABI::Microsoft::UI::Xaml::IUIElement* element,
                            ABI::Microsoft::UI::Composition::ICompositionAnimationBase* animation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE SetIsTranslationEnabled(
                            ABI::Microsoft::UI::Xaml::IUIElement* element,
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetPointerPositionPropertySet(
                            ABI::Microsoft::UI::Xaml::IUIElement* targetElement,
                            ABI::Microsoft::UI::Composition::ICompositionPropertySet** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IElementCompositionPreviewStatics = _uuidof(IElementCompositionPreviewStatics);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManager[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManager";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("85a2e562-7e8f-5333-a104-a3e672a2ffee")
                    IWindowsXamlManager : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IWindowsXamlManager = _uuidof(IWindowsXamlManager);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManager2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManager2[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManager2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("bd67cff5-b887-56da-b0a2-dad10a6520e9")
                    IWindowsXamlManager2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE add_XamlShutdownCompletedOnThread(
                            __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_XamlShutdownCompletedOnThread(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWindowsXamlManager2 = _uuidof(IWindowsXamlManager2);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManagerStatics[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("56cb591d-de97-539f-881d-8ccdc44fa6c4")
                    IWindowsXamlManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE InitializeForCurrentThread(
                            ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManager** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWindowsXamlManagerStatics = _uuidof(IWindowsXamlManagerStatics);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManagerStatics2[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("1062430e-0898-5240-ba52-89d9225e7e58")
                    IWindowsXamlManagerStatics2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetForCurrentThread(
                            ABI::Microsoft::UI::Xaml::Hosting::IWindowsXamlManager** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWindowsXamlManagerStatics2 = _uuidof(IWindowsXamlManagerStatics2);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlShutdownCompletedOnThreadEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlShutdownCompletedOnThreadEventArgs[] = L"Microsoft.UI.Xaml.Hosting.IXamlShutdownCompletedOnThreadEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("accd20e5-3576-5262-a3dd-990657681f1f")
                    IXamlShutdownCompletedOnThreadEventArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetDispatcherQueueDeferral(
                            ABI::Windows::Foundation::IDeferral** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlShutdownCompletedOnThreadEventArgs = _uuidof(IXamlShutdownCompletedOnThreadEventArgs);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequest
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationRequest[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequest";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("c883ea8b-4ce2-58be-b547-66dedf620312")
                    IXamlSourceFocusNavigationRequest : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Reason(
                            ABI::Microsoft::UI::Xaml::Hosting::XamlSourceFocusNavigationReason* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_HintRect(
                            ABI::Windows::Foundation::Rect* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CorrelationId(
                            GUID* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlSourceFocusNavigationRequest = _uuidof(IXamlSourceFocusNavigationRequest);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequestFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationRequestFactory[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequestFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("7a5124dd-2876-5ed8-b564-5867731d7f1e")
                    IXamlSourceFocusNavigationRequestFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Microsoft::UI::Xaml::Hosting::XamlSourceFocusNavigationReason reason,
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateInstanceWithHintRect(
                            ABI::Microsoft::UI::Xaml::Hosting::XamlSourceFocusNavigationReason reason,
                            ABI::Windows::Foundation::Rect hintRect,
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateInstanceWithHintRectAndCorrelationId(
                            ABI::Microsoft::UI::Xaml::Hosting::XamlSourceFocusNavigationReason reason,
                            ABI::Windows::Foundation::Rect hintRect,
                            GUID correlationId,
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationRequest** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlSourceFocusNavigationRequestFactory = _uuidof(IXamlSourceFocusNavigationRequestFactory);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationResult[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResult";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("d6bf378e-2aac-5e5b-ac8a-6c5d9a4c1cb8")
                    IXamlSourceFocusNavigationResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WasFocusMoved(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlSourceFocusNavigationResult = _uuidof(IXamlSourceFocusNavigationResult);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResultFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationResultFactory[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResultFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Hosting {
                    MIDL_INTERFACE("f533f53b-5c00-5c88-9a41-3888cb86e495")
                    IXamlSourceFocusNavigationResultFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            boolean focusMoved,
                            ABI::Microsoft::UI::Xaml::Hosting::IXamlSourceFocusNavigationResult** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IXamlSourceFocusNavigationResultFactory = _uuidof(IXamlSourceFocusNavigationResultFactory);
                } /* Hosting */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource ** Default Interface **
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource2
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSource_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSource_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSource[] = L"Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceGotFocusEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceGotFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceGotFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceTakeFocusRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceTakeFocusRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceTakeFocusRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceTakeFocusRequestedEventArgs[] = L"Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.ElementCompositionPreview
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Hosting.IElementCompositionPreviewStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IElementCompositionPreview ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_ElementCompositionPreview_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_ElementCompositionPreview_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_ElementCompositionPreview[] = L"Microsoft.UI.Xaml.Hosting.ElementCompositionPreview";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics2 interface starting with version 6.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Static Methods exist on the Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IWindowsXamlManager ** Default Interface **
 *    Microsoft.UI.Xaml.Hosting.IWindowsXamlManager2
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_WindowsXamlManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_WindowsXamlManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_WindowsXamlManager[] = L"Microsoft.UI.Xaml.Hosting.WindowsXamlManager";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IXamlShutdownCompletedOnThreadEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlShutdownCompletedOnThreadEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlShutdownCompletedOnThreadEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_XamlShutdownCompletedOnThreadEventArgs[] = L"Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequestFactory interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequest ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationRequest_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationRequest_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationRequest[] = L"Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResultFactory interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResult ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationResult_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationResult[] = L"Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2 __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2 __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2 __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* sender,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet __x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIVisual __x_ABI_CMicrosoft_CUI_CComposition_CIVisual;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CIUIElement_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIDeferral __x_ABI_CWindows_CFoundation_CIDeferral;

#endif // ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason;

/*
 *
 * Struct Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationReason
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
enum __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason
{
    XamlSourceFocusNavigationReason_Programmatic = 0,
    XamlSourceFocusNavigationReason_Restore = 1,
    XamlSourceFocusNavigationReason_First = 3,
    XamlSourceFocusNavigationReason_Last = 4,
    XamlSourceFocusNavigationReason_Left = 7,
    XamlSourceFocusNavigationReason_Up = 8,
    XamlSourceFocusNavigationReason_Right = 9,
    XamlSourceFocusNavigationReason_Down = 10,
};
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSource[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement** value);
    HRESULT (STDMETHODCALLTYPE* put_Content)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* value);
    HRESULT (STDMETHODCALLTYPE* get_HasFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_SystemBackdrop)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop** value);
    HRESULT (STDMETHODCALLTYPE* put_SystemBackdrop)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CMedia_CISystemBackdrop* value);
    HRESULT (STDMETHODCALLTYPE* get_SiteBridge)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge** value);
    HRESULT (STDMETHODCALLTYPE* add_TakeFocusRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceTakeFocusRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_TakeFocusRequested)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_GotFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSource_Microsoft__CUI__CXaml__CHosting__CDesktopWindowXamlSourceGotFocusEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_GotFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* NavigateFocus)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* request,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult** result);
    HRESULT (STDMETHODCALLTYPE* Initialize)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId parentWindowId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_put_Content(This, value) \
    ((This)->lpVtbl->put_Content(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_get_HasFocus(This, value) \
    ((This)->lpVtbl->get_HasFocus(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_get_SystemBackdrop(This, value) \
    ((This)->lpVtbl->get_SystemBackdrop(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_put_SystemBackdrop(This, value) \
    ((This)->lpVtbl->put_SystemBackdrop(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_get_SiteBridge(This, value) \
    ((This)->lpVtbl->get_SiteBridge(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_add_TakeFocusRequested(This, handler, token) \
    ((This)->lpVtbl->add_TakeFocusRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_remove_TakeFocusRequested(This, token) \
    ((This)->lpVtbl->remove_TakeFocusRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_add_GotFocus(This, handler, token) \
    ((This)->lpVtbl->add_GotFocus(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_remove_GotFocus(This, token) \
    ((This)->lpVtbl->remove_GotFocus(This, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_NavigateFocus(This, request, result) \
    ((This)->lpVtbl->NavigateFocus(This, request, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_Initialize(This, parentWindowId) \
    ((This)->lpVtbl->Initialize(This, parentWindowId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSource2[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ShouldConstrainPopupsToWorkArea)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ShouldConstrainPopupsToWorkArea)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_get_ShouldConstrainPopupsToWorkArea(This, value) \
    ((This)->lpVtbl->get_ShouldConstrainPopupsToWorkArea(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_put_ShouldConstrainPopupsToWorkArea(This, value) \
    ((This)->lpVtbl->put_ShouldConstrainPopupsToWorkArea(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSourceFactory[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory* This,
        IInspectable* baseInterface,
        IInspectable** innerInterface,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSource** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_CreateInstance(This, baseInterface, innerInterface, value) \
    ((This)->lpVtbl->CreateInstance(This, baseInterface, innerInterface, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSourceGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceGotFocusEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Request)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_get_Request(This, value) \
    ((This)->lpVtbl->get_Request(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceGotFocusEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceTakeFocusRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IDesktopWindowXamlSourceTakeFocusRequestedEventArgs[] = L"Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceTakeFocusRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Request)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_get_Request(This, value) \
    ((This)->lpVtbl->get_Request(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIDesktopWindowXamlSourceTakeFocusRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IElementCompositionPreview
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.ElementCompositionPreview
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IElementCompositionPreview[] = L"Microsoft.UI.Xaml.Hosting.IElementCompositionPreview";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreview_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IElementCompositionPreviewStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.ElementCompositionPreview
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IElementCompositionPreviewStatics[] = L"Microsoft.UI.Xaml.Hosting.IElementCompositionPreviewStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetElementVisual)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* element,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual** result);
    HRESULT (STDMETHODCALLTYPE* GetElementChildVisual)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* element,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual** result);
    HRESULT (STDMETHODCALLTYPE* SetElementChildVisual)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* element,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* visual);
    HRESULT (STDMETHODCALLTYPE* GetScrollViewerManipulationPropertySet)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CControls_CIScrollViewer* scrollViewer,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet** result);
    HRESULT (STDMETHODCALLTYPE* SetImplicitShowAnimation)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* element,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase* animation);
    HRESULT (STDMETHODCALLTYPE* SetImplicitHideAnimation)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* element,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionAnimationBase* animation);
    HRESULT (STDMETHODCALLTYPE* SetIsTranslationEnabled)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* element,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* GetPointerPositionPropertySet)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CIUIElement* targetElement,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositionPropertySet** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetElementVisual(This, element, result) \
    ((This)->lpVtbl->GetElementVisual(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetElementChildVisual(This, element, result) \
    ((This)->lpVtbl->GetElementChildVisual(This, element, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_SetElementChildVisual(This, element, visual) \
    ((This)->lpVtbl->SetElementChildVisual(This, element, visual))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetScrollViewerManipulationPropertySet(This, scrollViewer, result) \
    ((This)->lpVtbl->GetScrollViewerManipulationPropertySet(This, scrollViewer, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_SetImplicitShowAnimation(This, element, animation) \
    ((This)->lpVtbl->SetImplicitShowAnimation(This, element, animation))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_SetImplicitHideAnimation(This, element, animation) \
    ((This)->lpVtbl->SetImplicitHideAnimation(This, element, animation))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_SetIsTranslationEnabled(This, element, value) \
    ((This)->lpVtbl->SetIsTranslationEnabled(This, element, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_GetPointerPositionPropertySet(This, targetElement, result) \
    ((This)->lpVtbl->GetPointerPositionPropertySet(This, targetElement, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIElementCompositionPreviewStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManager[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManager";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManager2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManager2[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManager2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* add_XamlShutdownCompletedOnThread)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This,
        __FITypedEventHandler_2_Microsoft__CUI__CXaml__CHosting__CWindowsXamlManager_Microsoft__CUI__CXaml__CHosting__CXamlShutdownCompletedOnThreadEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_XamlShutdownCompletedOnThread)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_add_XamlShutdownCompletedOnThread(This, handler, token) \
    ((This)->lpVtbl->add_XamlShutdownCompletedOnThread(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_remove_XamlShutdownCompletedOnThread(This, token) \
    ((This)->lpVtbl->remove_XamlShutdownCompletedOnThread(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManagerStatics[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* InitializeForCurrentThread)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_InitializeForCurrentThread(This, result) \
    ((This)->lpVtbl->InitializeForCurrentThread(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IWindowsXamlManagerStatics2[] = L"Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetForCurrentThread)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_GetForCurrentThread(This, result) \
    ((This)->lpVtbl->GetForCurrentThread(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIWindowsXamlManagerStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlShutdownCompletedOnThreadEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlShutdownCompletedOnThreadEventArgs[] = L"Microsoft.UI.Xaml.Hosting.IXamlShutdownCompletedOnThreadEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDispatcherQueueDeferral)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs* This,
        __x_ABI_CWindows_CFoundation_CIDeferral** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_GetDispatcherQueueDeferral(This, result) \
    ((This)->lpVtbl->GetDispatcherQueueDeferral(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlShutdownCompletedOnThreadEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequest
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationRequest[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequest";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Reason)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason* value);
    HRESULT (STDMETHODCALLTYPE* get_HintRect)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        struct __x_ABI_CWindows_CFoundation_CRect* value);
    HRESULT (STDMETHODCALLTYPE* get_CorrelationId)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest* This,
        GUID* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_get_Reason(This, value) \
    ((This)->lpVtbl->get_Reason(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_get_HintRect(This, value) \
    ((This)->lpVtbl->get_HintRect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_get_CorrelationId(This, value) \
    ((This)->lpVtbl->get_CorrelationId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequestFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationRequestFactory[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequestFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason reason,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest** value);
    HRESULT (STDMETHODCALLTYPE* CreateInstanceWithHintRect)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason reason,
        struct __x_ABI_CWindows_CFoundation_CRect hintRect,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest** value);
    HRESULT (STDMETHODCALLTYPE* CreateInstanceWithHintRectAndCorrelationId)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CXamlSourceFocusNavigationReason reason,
        struct __x_ABI_CWindows_CFoundation_CRect hintRect,
        GUID correlationId,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequest** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_CreateInstance(This, reason, value) \
    ((This)->lpVtbl->CreateInstance(This, reason, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_CreateInstanceWithHintRect(This, reason, hintRect, value) \
    ((This)->lpVtbl->CreateInstanceWithHintRect(This, reason, hintRect, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_CreateInstanceWithHintRectAndCorrelationId(This, reason, hintRect, correlationId, value) \
    ((This)->lpVtbl->CreateInstanceWithHintRectAndCorrelationId(This, reason, hintRect, correlationId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationRequestFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationResult[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResult";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WasFocusMoved)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_get_WasFocusMoved(This, value) \
    ((This)->lpVtbl->get_WasFocusMoved(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResultFactory
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Hosting_IXamlSourceFocusNavigationResultFactory[] = L"Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResultFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory* This,
        boolean focusMoved,
        __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResult** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_CreateInstance(This, focusMoved, value) \
    ((This)->lpVtbl->CreateInstance(This, focusMoved, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CHosting_CIXamlSourceFocusNavigationResultFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource ** Default Interface **
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSource2
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSource_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSource_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSource[] = L"Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSource";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceGotFocusEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceGotFocusEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceGotFocusEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceGotFocusEventArgs[] = L"Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceGotFocusEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IDesktopWindowXamlSourceTakeFocusRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceTakeFocusRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceTakeFocusRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_DesktopWindowXamlSourceTakeFocusRequestedEventArgs[] = L"Microsoft.UI.Xaml.Hosting.DesktopWindowXamlSourceTakeFocusRequestedEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.ElementCompositionPreview
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Hosting.IElementCompositionPreviewStatics interface starting with version 1.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IElementCompositionPreview ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_ElementCompositionPreview_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_ElementCompositionPreview_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_ElementCompositionPreview[] = L"Microsoft.UI.Xaml.Hosting.ElementCompositionPreview";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.WindowsXamlManager
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics2 interface starting with version 6.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *   Static Methods exist on the Microsoft.UI.Xaml.Hosting.IWindowsXamlManagerStatics interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IWindowsXamlManager ** Default Interface **
 *    Microsoft.UI.Xaml.Hosting.IWindowsXamlManager2
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_WindowsXamlManager_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_WindowsXamlManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_WindowsXamlManager[] = L"Microsoft.UI.Xaml.Hosting.WindowsXamlManager";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IXamlShutdownCompletedOnThreadEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlShutdownCompletedOnThreadEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlShutdownCompletedOnThreadEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_XamlShutdownCompletedOnThreadEventArgs[] = L"Microsoft.UI.Xaml.Hosting.XamlShutdownCompletedOnThreadEventArgs";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequestFactory interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationRequest ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationRequest_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationRequest_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationRequest[] = L"Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationRequest";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResultFactory interface starting with version 5.0 of the Microsoft.UI.Xaml.WinUIContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Hosting.IXamlSourceFocusNavigationResult ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationResult_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Hosting_XamlSourceFocusNavigationResult[] = L"Microsoft.UI.Xaml.Hosting.XamlSourceFocusNavigationResult";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x50000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Ehosting_p_h__

#endif // __microsoft2Eui2Examl2Ehosting_h__
