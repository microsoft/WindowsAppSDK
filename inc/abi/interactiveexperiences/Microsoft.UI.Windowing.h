
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
#ifndef __microsoft2Eui2Ewindowing_h__
#define __microsoft2Eui2Ewindowing_h__
#ifndef __microsoft2Eui2Ewindowing_p_h__
#define __microsoft2Eui2Ewindowing_p_h__


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
#if !defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)
#define MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION 0x10008
#endif // defined(MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION)

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
#include "Microsoft.Foundation.h"
#include "Microsoft.UI.h"
#include "Microsoft.UI.Dispatching.h"
#include "Windows.Graphics.h"
#include "Windows.UI.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindow;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow ABI::Microsoft::UI::Windowing::IAppWindow

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindow2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2 ABI::Microsoft::UI::Windowing::IAppWindow2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindow3;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3 ABI::Microsoft::UI::Windowing::IAppWindow3

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindow4;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4 ABI::Microsoft::UI::Windowing::IAppWindow4

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowChangedEventArgs;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs ABI::Microsoft::UI::Windowing::IAppWindowChangedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowChangedEventArgs2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2 ABI::Microsoft::UI::Windowing::IAppWindowChangedEventArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowClosingEventArgs;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs ABI::Microsoft::UI::Windowing::IAppWindowClosingEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter ABI::Microsoft::UI::Windowing::IAppWindowPresenter

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowPresenterFactory;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory ABI::Microsoft::UI::Windowing::IAppWindowPresenterFactory

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowStatics;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics ABI::Microsoft::UI::Windowing::IAppWindowStatics

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowStatics2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2 ABI::Microsoft::UI::Windowing::IAppWindowStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowTitleBar;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar ABI::Microsoft::UI::Windowing::IAppWindowTitleBar

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowTitleBar2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2 ABI::Microsoft::UI::Windowing::IAppWindowTitleBar2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowTitleBar3;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3 ABI::Microsoft::UI::Windowing::IAppWindowTitleBar3

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IAppWindowTitleBarStatics;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics ABI::Microsoft::UI::Windowing::IAppWindowTitleBarStatics

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface ICompactOverlayPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter ABI::Microsoft::UI::Windowing::ICompactOverlayPresenter

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface ICompactOverlayPresenterStatics;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics ABI::Microsoft::UI::Windowing::ICompactOverlayPresenterStatics

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IDisplayArea;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea ABI::Microsoft::UI::Windowing::IDisplayArea

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IDisplayAreaStatics;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics ABI::Microsoft::UI::Windowing::IDisplayAreaStatics

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IDisplayAreaStatics2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2 ABI::Microsoft::UI::Windowing::IDisplayAreaStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IDisplayAreaWatcher;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher ABI::Microsoft::UI::Windowing::IDisplayAreaWatcher

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IFullScreenPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter ABI::Microsoft::UI::Windowing::IFullScreenPresenter

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IFullScreenPresenterStatics;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics ABI::Microsoft::UI::Windowing::IFullScreenPresenterStatics

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IOverlappedPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter ABI::Microsoft::UI::Windowing::IOverlappedPresenter

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IOverlappedPresenter2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2 ABI::Microsoft::UI::Windowing::IOverlappedPresenter2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IOverlappedPresenter3;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3 ABI::Microsoft::UI::Windowing::IOverlappedPresenter3

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IOverlappedPresenterStatics;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics ABI::Microsoft::UI::Windowing::IOverlappedPresenterStatics

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                interface IOverlappedPresenterStatics2;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2 ABI::Microsoft::UI::Windowing::IOverlappedPresenterStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class DisplayArea;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_USE
#define DEF___FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("3d833884-2258-5c48-8d45-3642fe8c6755"))
IIterator<ABI::Microsoft::UI::Windowing::DisplayArea*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::DisplayArea*, ABI::Microsoft::UI::Windowing::IDisplayArea*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Windowing.DisplayArea>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Windowing::DisplayArea*> __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_t;
#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_USE
#define DEF___FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("fb253085-6cfc-5fa6-948e-97383f5be36c"))
IIterable<ABI::Microsoft::UI::Windowing::DisplayArea*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::DisplayArea*, ABI::Microsoft::UI::Windowing::IDisplayArea*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Windowing.DisplayArea>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Windowing::DisplayArea*> __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_t;
#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_USE
#define DEF___FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("63490e13-d075-5fe2-b6a4-86a44095215f"))
IVectorView<ABI::Microsoft::UI::Windowing::DisplayArea*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::DisplayArea*, ABI::Microsoft::UI::Windowing::IDisplayArea*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.UI.Windowing.DisplayArea>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::UI::Windowing::DisplayArea*> __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_t;
#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000


#ifndef DEF___FIReference_1_int_USE
#define DEF___FIReference_1_int_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("548cefbd-bc8a-5fa0-8df2-957440fc8bf4"))
IReference<int> : IReference_impl<int>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Int32>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<int> __FIReference_1_int_t;
#define __FIReference_1_int ABI::Windows::Foundation::__FIReference_1_int_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_int_USE */


namespace ABI {
    namespace Windows {
        namespace UI {
            typedef struct Color Color;
        } /* UI */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#ifndef DEF___FIReference_1_Windows__CUI__CColor_USE
#define DEF___FIReference_1_Windows__CUI__CColor_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ab8e5d11-b0c1-5a21-95ae-f16bf3a37624"))
IReference<struct ABI::Windows::UI::Color> : IReference_impl<struct ABI::Windows::UI::Color>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Windows.UI.Color>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<struct ABI::Windows::UI::Color> __FIReference_1_Windows__CUI__CColor_t;
#define __FIReference_1_Windows__CUI__CColor ABI::Windows::Foundation::__FIReference_1_Windows__CUI__CColor_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_Windows__CUI__CColor_USE */

#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class AppWindow;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class AppWindowChangedEventArgs;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("cda07756-1584-5049-9ad1-cca782242d34"))
ITypedEventHandler<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::AppWindowChangedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::IAppWindow*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::AppWindowChangedEventArgs*, ABI::Microsoft::UI::Windowing::IAppWindowChangedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Windowing.AppWindow, Microsoft.UI.Windowing.AppWindowChangedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::AppWindowChangedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class AppWindowClosingEventArgs;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("fd0e72c8-8daa-50a2-959f-4d41446f1fc7"))
ITypedEventHandler<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::AppWindowClosingEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::IAppWindow*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::AppWindowClosingEventArgs*, ABI::Microsoft::UI::Windowing::IAppWindowClosingEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Windowing.AppWindow, Microsoft.UI.Windowing.AppWindowClosingEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::AppWindowClosingEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("eddd665f-7d53-5b2d-901d-9c12010816e7"))
ITypedEventHandler<ABI::Microsoft::UI::Windowing::AppWindow*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::AppWindow*, ABI::Microsoft::UI::Windowing::IAppWindow*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Windowing.AppWindow, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Windowing::AppWindow*, IInspectable*> __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class DisplayAreaWatcher;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1ab60859-caaf-5b34-bab0-3d9035eb80cb"))
ITypedEventHandler<ABI::Microsoft::UI::Windowing::DisplayAreaWatcher*, ABI::Microsoft::UI::Windowing::DisplayArea*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::DisplayAreaWatcher*, ABI::Microsoft::UI::Windowing::IDisplayAreaWatcher*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::DisplayArea*, ABI::Microsoft::UI::Windowing::IDisplayArea*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Windowing.DisplayAreaWatcher, Microsoft.UI.Windowing.DisplayArea>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Windowing::DisplayAreaWatcher*, ABI::Microsoft::UI::Windowing::DisplayArea*> __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("2ddb3359-9837-5ba8-803e-eb5ab1ccb67f"))
ITypedEventHandler<ABI::Microsoft::UI::Windowing::DisplayAreaWatcher*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Windowing::DisplayAreaWatcher*, ABI::Microsoft::UI::Windowing::IDisplayAreaWatcher*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Windowing.DisplayAreaWatcher, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Windowing::DisplayAreaWatcher*, IInspectable*> __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                class DispatcherQueue;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Dispatching {
                interface IDispatcherQueue;
            } /* Dispatching */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue ABI::Microsoft::UI::Dispatching::IDispatcherQueue

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct DisplayId DisplayId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct IconId IconId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            interface IPropertyValue;
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CIPropertyValue ABI::Windows::Foundation::IPropertyValue

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Graphics {
            typedef struct PointInt32 PointInt32;
        } /* Graphics */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Graphics {
            typedef struct RectInt32 RectInt32;
        } /* Graphics */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Graphics {
            typedef struct SizeInt32 SizeInt32;
        } /* Graphics */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum AppWindowPresenterKind : int AppWindowPresenterKind;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum CompactOverlaySize : int CompactOverlaySize;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum DisplayAreaFallback : int DisplayAreaFallback;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum DisplayAreaWatcherStatus : int DisplayAreaWatcherStatus;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum IconShowOptions : int IconShowOptions;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum OverlappedPresenterState : int OverlappedPresenterState;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum TitleBarHeightOption : int TitleBarHeightOption;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                typedef enum TitleBarTheme : int TitleBarTheme;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class AppWindowPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class AppWindowTitleBar;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class CompactOverlayPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class FullScreenPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                class OverlappedPresenter;
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Windowing.AppWindowPresenterKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum AppWindowPresenterKind : int
                {
                    AppWindowPresenterKind_Default = 0,
                    AppWindowPresenterKind_CompactOverlay = 1,
                    AppWindowPresenterKind_FullScreen = 2,
                    AppWindowPresenterKind_Overlapped = 3,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.CompactOverlaySize
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum CompactOverlaySize : int
                {
                    CompactOverlaySize_Small = 0,
                    CompactOverlaySize_Medium = 1,
                    CompactOverlaySize_Large = 2,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.DisplayAreaFallback
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum DisplayAreaFallback : int
                {
                    DisplayAreaFallback_None = 0,
                    DisplayAreaFallback_Primary = 1,
                    DisplayAreaFallback_Nearest = 2,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.DisplayAreaWatcherStatus
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum DisplayAreaWatcherStatus : int
                {
                    DisplayAreaWatcherStatus_Created = 0,
                    DisplayAreaWatcherStatus_Started = 1,
                    DisplayAreaWatcherStatus_EnumerationCompleted = 2,
                    DisplayAreaWatcherStatus_Stopping = 3,
                    DisplayAreaWatcherStatus_Stopped = 4,
                    DisplayAreaWatcherStatus_Aborted = 5,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.IconShowOptions
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum IconShowOptions : int
                {
                    IconShowOptions_ShowIconAndSystemMenu = 0,
                    IconShowOptions_HideIconAndSystemMenu = 1,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.OverlappedPresenterState
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum OverlappedPresenterState : int
                {
                    OverlappedPresenterState_Maximized = 0,
                    OverlappedPresenterState_Minimized = 1,
                    OverlappedPresenterState_Restored = 2,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.TitleBarHeightOption
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum TitleBarHeightOption : int
                {
                    TitleBarHeightOption_Standard = 0,
                    TitleBarHeightOption_Tall = 1,
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
                    TitleBarHeightOption_Collapsed = 2,
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Struct Microsoft.UI.Windowing.TitleBarTheme
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                enum TitleBarTheme : int
                {
                    TitleBarTheme_Legacy = 0,
                    TitleBarTheme_UseDefaultAppMode = 1,
                    TitleBarTheme_Light = 2,
                    TitleBarTheme_Dark = 3,
                };
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow[] = L"Microsoft.UI.Windowing.IAppWindow";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("cfa788b3-643b-5c5e-ad4e-321d48a82acd")
                IAppWindow : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Id(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsShownInSwitchers(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsShownInSwitchers(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_OwnerWindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Position(
                        ABI::Windows::Graphics::PointInt32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Presenter(
                        ABI::Microsoft::UI::Windowing::IAppWindowPresenter** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Size(
                        ABI::Windows::Graphics::SizeInt32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Title(
                        HSTRING* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Title(
                        HSTRING value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_TitleBar(
                        ABI::Microsoft::UI::Windowing::IAppWindowTitleBar** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Destroy(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Hide(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Move(
                        ABI::Windows::Graphics::PointInt32 position
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveAndResize(
                        ABI::Windows::Graphics::RectInt32 rect
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveAndResizeRelativeToDisplayArea(
                        ABI::Windows::Graphics::RectInt32 rect,
                        ABI::Microsoft::UI::Windowing::IDisplayArea* displayarea
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Resize(
                        ABI::Windows::Graphics::SizeInt32 size
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetIcon(
                        HSTRING iconPath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetIconWithIconId(
                        ABI::Microsoft::UI::IconId iconId
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetPresenter(
                        ABI::Microsoft::UI::Windowing::IAppWindowPresenter* appWindowPresenter
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetPresenterByKind(
                        ABI::Microsoft::UI::Windowing::AppWindowPresenterKind appWindowPresenterKind
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Show(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ShowWithActivation(
                        boolean activateWindow
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Changed(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Changed(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Closing(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Closing(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Destroying(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Destroying(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindow = _uuidof(IAppWindow);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow2[] = L"Microsoft.UI.Windowing.IAppWindow2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("6cd41292-794c-5cac-8961-210d012c6ebc")
                IAppWindow2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ClientSize(
                        ABI::Windows::Graphics::SizeInt32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderAtBottom(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderAtTop(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderBelow(
                        ABI::Microsoft::UI::WindowId windowId
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ResizeClient(
                        ABI::Windows::Graphics::SizeInt32 size
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ShowOnceWithRequestedStartupState(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindow2 = _uuidof(IAppWindow2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow3[] = L"Microsoft.UI.Windowing.IAppWindow3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("2f260cea-193d-5dd6-a904-d7649a608d2f")
                IAppWindow3 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE AssociateWithDispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue* dispatcherQueue
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindow3 = _uuidof(IAppWindow3);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow4
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow4[] = L"Microsoft.UI.Windowing.IAppWindow4";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("383bfb91-ea29-5414-80cd-6c76d981eb31")
                IAppWindow4 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE SetTaskbarIcon(
                        HSTRING iconPath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetTaskbarIconWithIconId(
                        ABI::Microsoft::UI::IconId iconId
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetTitleBarIcon(
                        HSTRING iconPath
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetTitleBarIconWithIconId(
                        ABI::Microsoft::UI::IconId iconId
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindow4 = _uuidof(IAppWindow4);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowChangedEventArgs[] = L"Microsoft.UI.Windowing.IAppWindowChangedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("2182bc5d-fdac-5c3e-bf37-7d8d684e9d1d")
                IAppWindowChangedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidPositionChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidPresenterChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidSizeChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidVisibilityChange(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowChangedEventArgs = _uuidof(IAppWindowChangedEventArgs);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowChangedEventArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowChangedEventArgs2[] = L"Microsoft.UI.Windowing.IAppWindowChangedEventArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("a773ab4c-a5ec-50e8-98ac-247fe6cd4227")
                IAppWindowChangedEventArgs2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidZOrderChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsZOrderAtBottom(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsZOrderAtTop(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ZOrderBelowWindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowChangedEventArgs2 = _uuidof(IAppWindowChangedEventArgs2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowClosingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowClosingEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowClosingEventArgs[] = L"Microsoft.UI.Windowing.IAppWindowClosingEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("0e09d90b-2261-590b-9ad1-8504991d8754")
                IAppWindowClosingEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Cancel(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Cancel(
                        boolean value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowClosingEventArgs = _uuidof(IAppWindowClosingEventArgs);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowPresenter[] = L"Microsoft.UI.Windowing.IAppWindowPresenter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("bc3042c2-c6c6-5632-8989-ff0ec6d3b40d")
                IAppWindowPresenter : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Kind(
                        ABI::Microsoft::UI::Windowing::AppWindowPresenterKind* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowPresenter = _uuidof(IAppWindowPresenter);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowPresenterFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowPresenterFactory[] = L"Microsoft.UI.Windowing.IAppWindowPresenterFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("62082e3c-1368-5238-90d1-e932dc718a82")
                IAppWindowPresenterFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IAppWindowPresenterFactory = _uuidof(IAppWindowPresenterFactory);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowStatics[] = L"Microsoft.UI.Windowing.IAppWindowStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("3c315c24-d540-5d72-b518-b226b83627cb")
                IAppWindowStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Windowing::IAppWindow** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateWithPresenter(
                        ABI::Microsoft::UI::Windowing::IAppWindowPresenter* appWindowPresenter,
                        ABI::Microsoft::UI::Windowing::IAppWindow** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateWithPresenterAndOwner(
                        ABI::Microsoft::UI::Windowing::IAppWindowPresenter* appWindowPresenter,
                        ABI::Microsoft::UI::WindowId ownerWindowId,
                        ABI::Microsoft::UI::Windowing::IAppWindow** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetFromWindowId(
                        ABI::Microsoft::UI::WindowId windowId,
                        ABI::Microsoft::UI::Windowing::IAppWindow** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowStatics = _uuidof(IAppWindowStatics);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowStatics2[] = L"Microsoft.UI.Windowing.IAppWindowStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("cabc23db-4606-5d6e-89a5-06de1d8bd3e2")
                IAppWindowStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateWithDispatcherQueue(
                        ABI::Microsoft::UI::Windowing::IAppWindowPresenter* appWindowPresenter,
                        ABI::Microsoft::UI::WindowId ownerWindowId,
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue* DispatcherQueue,
                        ABI::Microsoft::UI::Windowing::IAppWindow** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowStatics2 = _uuidof(IAppWindowStatics2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBar
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBar[] = L"Microsoft.UI.Windowing.IAppWindowTitleBar";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("5574efa2-c91c-5700-a363-539c71a7aaf4")
                IAppWindowTitleBar : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_BackgroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_BackgroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonForegroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonForegroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonHoverBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonHoverBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonHoverForegroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonHoverForegroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonInactiveBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonInactiveBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonInactiveForegroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonInactiveForegroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonPressedBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonPressedBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ButtonPressedForegroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ButtonPressedForegroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ExtendsContentIntoTitleBar(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ExtendsContentIntoTitleBar(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ForegroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ForegroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Height(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IconShowOptions(
                        ABI::Microsoft::UI::Windowing::IconShowOptions* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IconShowOptions(
                        ABI::Microsoft::UI::Windowing::IconShowOptions value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_InactiveBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_InactiveBackgroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_InactiveForegroundColor(
                        __FIReference_1_Windows__CUI__CColor** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_InactiveForegroundColor(
                        __FIReference_1_Windows__CUI__CColor* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LeftInset(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RightInset(
                        INT32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ResetToDefault(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetDragRectangles(
                        UINT32 valueLength,
                        ABI::Windows::Graphics::RectInt32* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowTitleBar = _uuidof(IAppWindowTitleBar);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBar2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBar2[] = L"Microsoft.UI.Windowing.IAppWindowTitleBar2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("86faed38-748a-5b4b-9ccf-3ba0496c9041")
                IAppWindowTitleBar2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_PreferredHeightOption(
                        ABI::Microsoft::UI::Windowing::TitleBarHeightOption* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PreferredHeightOption(
                        ABI::Microsoft::UI::Windowing::TitleBarHeightOption value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowTitleBar2 = _uuidof(IAppWindowTitleBar2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBar3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBar3[] = L"Microsoft.UI.Windowing.IAppWindowTitleBar3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("07146e74-0410-5597-aba7-1af276d2ae07")
                IAppWindowTitleBar3 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_PreferredTheme(
                        ABI::Microsoft::UI::Windowing::TitleBarTheme* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PreferredTheme(
                        ABI::Microsoft::UI::Windowing::TitleBarTheme value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowTitleBar3 = _uuidof(IAppWindowTitleBar3);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBarStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBarStatics[] = L"Microsoft.UI.Windowing.IAppWindowTitleBarStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("9e1da52e-8b15-54d6-a886-f7b9f9d930b2")
                IAppWindowTitleBarStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE IsCustomizationSupported(
                        boolean* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IAppWindowTitleBarStatics = _uuidof(IAppWindowTitleBarStatics);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.ICompactOverlayPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.CompactOverlayPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_ICompactOverlayPresenter[] = L"Microsoft.UI.Windowing.ICompactOverlayPresenter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("efeb0812-6fc7-5b7d-bd92-cc8f9a6454c9")
                ICompactOverlayPresenter : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_InitialSize(
                        ABI::Microsoft::UI::Windowing::CompactOverlaySize* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_InitialSize(
                        ABI::Microsoft::UI::Windowing::CompactOverlaySize value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ICompactOverlayPresenter = _uuidof(ICompactOverlayPresenter);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.ICompactOverlayPresenterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.CompactOverlayPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_ICompactOverlayPresenterStatics[] = L"Microsoft.UI.Windowing.ICompactOverlayPresenterStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("eab93186-4f6a-52f9-8c03-da57a1522f6e")
                ICompactOverlayPresenterStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Windowing::ICompactOverlayPresenter** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_ICompactOverlayPresenterStatics = _uuidof(ICompactOverlayPresenterStatics);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayArea
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayArea
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayArea[] = L"Microsoft.UI.Windowing.IDisplayArea";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("5c7e0537-b621-5579-bcae-a84aa8746167")
                IDisplayArea : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayId(
                        ABI::Microsoft::UI::DisplayId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsPrimary(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_OuterBounds(
                        ABI::Windows::Graphics::RectInt32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_WorkArea(
                        ABI::Windows::Graphics::RectInt32* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayArea = _uuidof(IDisplayArea);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayAreaStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayArea
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayAreaStatics[] = L"Microsoft.UI.Windowing.IDisplayAreaStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("02ab4926-211e-5d49-8e4b-2af193daed09")
                IDisplayAreaStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Primary(
                        ABI::Microsoft::UI::Windowing::IDisplayArea** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateWatcher(
                        ABI::Microsoft::UI::Windowing::IDisplayAreaWatcher** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FindAll(
                        __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetFromWindowId(
                        ABI::Microsoft::UI::WindowId windowId,
                        ABI::Microsoft::UI::Windowing::DisplayAreaFallback displayAreaFallback,
                        ABI::Microsoft::UI::Windowing::IDisplayArea** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetFromPoint(
                        ABI::Windows::Graphics::PointInt32 point,
                        ABI::Microsoft::UI::Windowing::DisplayAreaFallback displayAreaFallback,
                        ABI::Microsoft::UI::Windowing::IDisplayArea** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetFromRect(
                        ABI::Windows::Graphics::RectInt32 rect,
                        ABI::Microsoft::UI::Windowing::DisplayAreaFallback displayAreaFallback,
                        ABI::Microsoft::UI::Windowing::IDisplayArea** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayAreaStatics = _uuidof(IDisplayAreaStatics);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayAreaStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayArea
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayAreaStatics2[] = L"Microsoft.UI.Windowing.IDisplayAreaStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("7207ad4b-890d-5dd7-bc18-78ffd9544d8f")
                IDisplayAreaStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE GetFromDisplayId(
                        ABI::Microsoft::UI::DisplayId displayId,
                        ABI::Microsoft::UI::Windowing::IDisplayArea** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayAreaStatics2 = _uuidof(IDisplayAreaStatics2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayAreaWatcher
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayAreaWatcher
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayAreaWatcher[] = L"Microsoft.UI.Windowing.IDisplayAreaWatcher";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("83f6562f-d3a0-548b-8e4f-a99be3d95c9c")
                IDisplayAreaWatcher : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Status(
                        ABI::Microsoft::UI::Windowing::DisplayAreaWatcherStatus* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Start(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Stop(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Added(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Added(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_EnumerationCompleted(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_EnumerationCompleted(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Removed(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Removed(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Stopped(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Stopped(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_Updated(
                        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_Updated(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDisplayAreaWatcher = _uuidof(IDisplayAreaWatcher);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IFullScreenPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.FullScreenPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IFullScreenPresenter[] = L"Microsoft.UI.Windowing.IFullScreenPresenter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("fa9141fd-b8dd-5da1-8b2b-7cdadb76f593")
                IFullScreenPresenter : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IFullScreenPresenter = _uuidof(IFullScreenPresenter);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IFullScreenPresenterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.FullScreenPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IFullScreenPresenterStatics[] = L"Microsoft.UI.Windowing.IFullScreenPresenterStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("2ec0d2c1-e086-55bb-a3b2-44942e231c67")
                IFullScreenPresenterStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Windowing::IFullScreenPresenter** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IFullScreenPresenterStatics = _uuidof(IFullScreenPresenterStatics);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenter[] = L"Microsoft.UI.Windowing.IOverlappedPresenter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("21693970-4f4c-5172-9e9d-682a2d174884")
                IOverlappedPresenter : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_HasBorder(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_HasTitleBar(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsAlwaysOnTop(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsAlwaysOnTop(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsMaximizable(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsMaximizable(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsMinimizable(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsMinimizable(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsModal(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsModal(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsResizable(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsResizable(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_State(
                        ABI::Microsoft::UI::Windowing::OverlappedPresenterState* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Maximize(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Minimize(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Restore(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE SetBorderAndTitleBar(
                        boolean hasBorder,
                        boolean hasTitleBar
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IOverlappedPresenter = _uuidof(IOverlappedPresenter);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenter2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenter2[] = L"Microsoft.UI.Windowing.IOverlappedPresenter2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("5c6ccd93-4244-5cd2-b355-ed5ea34df730")
                IOverlappedPresenter2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE MinimizeWithActivation(
                        boolean activateWindow
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RestoreWithActivation(
                        boolean activateWindow
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IOverlappedPresenter2 = _uuidof(IOverlappedPresenter2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenter3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenter3[] = L"Microsoft.UI.Windowing.IOverlappedPresenter3";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("55d26138-4c38-57e7-a0c1-d467b774db8c")
                IOverlappedPresenter3 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_PreferredMinimumHeight(
                        __FIReference_1_int** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PreferredMinimumHeight(
                        __FIReference_1_int* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PreferredMinimumWidth(
                        __FIReference_1_int** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PreferredMinimumWidth(
                        __FIReference_1_int* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PreferredMaximumWidth(
                        __FIReference_1_int** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PreferredMaximumWidth(
                        __FIReference_1_int* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PreferredMaximumHeight(
                        __FIReference_1_int** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_PreferredMaximumHeight(
                        __FIReference_1_int* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IOverlappedPresenter3 = _uuidof(IOverlappedPresenter3);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenterStatics[] = L"Microsoft.UI.Windowing.IOverlappedPresenterStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("997225e4-7b00-5aee-a4be-d4068d1999e2")
                IOverlappedPresenterStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Windowing::IOverlappedPresenter** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateForContextMenu(
                        ABI::Microsoft::UI::Windowing::IOverlappedPresenter** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateForDialog(
                        ABI::Microsoft::UI::Windowing::IOverlappedPresenter** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateForToolWindow(
                        ABI::Microsoft::UI::Windowing::IOverlappedPresenter** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IOverlappedPresenterStatics = _uuidof(IOverlappedPresenterStatics);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenterStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenterStatics2[] = L"Microsoft.UI.Windowing.IOverlappedPresenterStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Windowing {
                MIDL_INTERFACE("ed5c4f92-32f4-5d15-80d0-b2a5efa04d39")
                IOverlappedPresenterStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_RequestedStartupState(
                        ABI::Microsoft::UI::Windowing::OverlappedPresenterState* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IOverlappedPresenterStatics2 = _uuidof(IOverlappedPresenterStatics2);
            } /* Windowing */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Class Microsoft.UI.Windowing.AppWindow
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IAppWindowStatics2 interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Windowing.IAppWindowStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindow ** Default Interface **
 *    Microsoft.UI.Windowing.IAppWindow2
 *    Microsoft.UI.Windowing.IAppWindow3
 *    Microsoft.UI.Windowing.IAppWindow4
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindow_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindow_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindow[] = L"Microsoft.UI.Windowing.AppWindow";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowChangedEventArgs ** Default Interface **
 *    Microsoft.UI.Windowing.IAppWindowChangedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowChangedEventArgs[] = L"Microsoft.UI.Windowing.AppWindowChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowClosingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowClosingEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowClosingEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowClosingEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowClosingEventArgs[] = L"Microsoft.UI.Windowing.AppWindowClosingEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowPresenter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowPresenter[] = L"Microsoft.UI.Windowing.AppWindowPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowTitleBar
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IAppWindowTitleBarStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowTitleBar ** Default Interface **
 *    Microsoft.UI.Windowing.IAppWindowTitleBar2
 *    Microsoft.UI.Windowing.IAppWindowTitleBar3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowTitleBar_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowTitleBar_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowTitleBar[] = L"Microsoft.UI.Windowing.AppWindowTitleBar";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.CompactOverlayPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.ICompactOverlayPresenterStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.ICompactOverlayPresenter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_CompactOverlayPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_CompactOverlayPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_CompactOverlayPresenter[] = L"Microsoft.UI.Windowing.CompactOverlayPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.DisplayArea
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IDisplayAreaStatics2 interface starting with version 1.2 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Windowing.IDisplayAreaStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IDisplayArea ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_DisplayArea_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_DisplayArea_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_DisplayArea[] = L"Microsoft.UI.Windowing.DisplayArea";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.DisplayAreaWatcher
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IDisplayAreaWatcher ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_DisplayAreaWatcher_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_DisplayAreaWatcher_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_DisplayAreaWatcher[] = L"Microsoft.UI.Windowing.DisplayAreaWatcher";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.FullScreenPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IFullScreenPresenterStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IFullScreenPresenter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_FullScreenPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_FullScreenPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_FullScreenPresenter[] = L"Microsoft.UI.Windowing.FullScreenPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.OverlappedPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IOverlappedPresenterStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Windowing.IOverlappedPresenterStatics2 interface starting with version 1.1 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IOverlappedPresenter ** Default Interface **
 *    Microsoft.UI.Windowing.IOverlappedPresenter2
 *    Microsoft.UI.Windowing.IOverlappedPresenter3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_OverlappedPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_OverlappedPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_OverlappedPresenter[] = L"Microsoft.UI.Windowing.OverlappedPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3 __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2 __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2 __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3 __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2 __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea;

typedef struct __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl;

interface __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea;

typedef struct __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        __FIIterator_1_Microsoft__CUI__CWindowing__CDisplayArea** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl;

interface __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea;

typedef struct __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl;

interface __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayAreaVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if !defined(____FIReference_1_int_INTERFACE_DEFINED__)
#define ____FIReference_1_int_INTERFACE_DEFINED__

typedef interface __FIReference_1_int __FIReference_1_int;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_int;

typedef struct __FIReference_1_intVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_int* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_int* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_int* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_int* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_int* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_int* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_int* This,
        INT32* result);

    END_INTERFACE
} __FIReference_1_intVtbl;

interface __FIReference_1_int
{
    CONST_VTBL struct __FIReference_1_intVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_int_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_int_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_int_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_int_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_int_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_int_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_int_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_int_INTERFACE_DEFINED__

typedef struct __x_ABI_CWindows_CUI_CColor __x_ABI_CWindows_CUI_CColor;

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000
#if !defined(____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__)
#define ____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__

typedef interface __FIReference_1_Windows__CUI__CColor __FIReference_1_Windows__CUI__CColor;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_Windows__CUI__CColor;

typedef struct __FIReference_1_Windows__CUI__CColorVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_Windows__CUI__CColor* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_Windows__CUI__CColor* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_Windows__CUI__CColor* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_Windows__CUI__CColor* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_Windows__CUI__CColor* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_Windows__CUI__CColor* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_Windows__CUI__CColor* This,
        struct __x_ABI_CWindows_CUI_CColor* result);

    END_INTERFACE
} __FIReference_1_Windows__CUI__CColorVtbl;

interface __FIReference_1_Windows__CUI__CColor
{
    CONST_VTBL struct __FIReference_1_Windows__CUI__CColorVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_Windows__CUI__CColor_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_Windows__CUI__CColor_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_Windows__CUI__CColor_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_Windows__CUI__CColor_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_Windows__CUI__CColor_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_Windows__CUI__CColor_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_Windows__CUI__CColor_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* sender,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* sender,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayAreaVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* sender,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayAreaVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayAreaVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CDisplayId __x_ABI_CMicrosoft_CUI_CDisplayId;

typedef struct __x_ABI_CMicrosoft_CUI_CIconId __x_ABI_CMicrosoft_CUI_CIconId;

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIPropertyValue __x_ABI_CWindows_CFoundation_CIPropertyValue;

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CGraphics_CPointInt32 __x_ABI_CWindows_CGraphics_CPointInt32;

typedef struct __x_ABI_CWindows_CGraphics_CRectInt32 __x_ABI_CWindows_CGraphics_CRectInt32;

typedef struct __x_ABI_CWindows_CGraphics_CSizeInt32 __x_ABI_CWindows_CGraphics_CSizeInt32;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CAppWindowPresenterKind __x_ABI_CMicrosoft_CUI_CWindowing_CAppWindowPresenterKind;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CCompactOverlaySize __x_ABI_CMicrosoft_CUI_CWindowing_CCompactOverlaySize;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaFallback __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaFallback;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaWatcherStatus __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaWatcherStatus;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CIconShowOptions __x_ABI_CMicrosoft_CUI_CWindowing_CIconShowOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_COverlappedPresenterState __x_ABI_CMicrosoft_CUI_CWindowing_COverlappedPresenterState;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarHeightOption __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarHeightOption;

typedef enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarTheme __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarTheme;

/*
 *
 * Struct Microsoft.UI.Windowing.AppWindowPresenterKind
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CWindowing_CAppWindowPresenterKind
{
    AppWindowPresenterKind_Default = 0,
    AppWindowPresenterKind_CompactOverlay = 1,
    AppWindowPresenterKind_FullScreen = 2,
    AppWindowPresenterKind_Overlapped = 3,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.CompactOverlaySize
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CWindowing_CCompactOverlaySize
{
    CompactOverlaySize_Small = 0,
    CompactOverlaySize_Medium = 1,
    CompactOverlaySize_Large = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.DisplayAreaFallback
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaFallback
{
    DisplayAreaFallback_None = 0,
    DisplayAreaFallback_Primary = 1,
    DisplayAreaFallback_Nearest = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.DisplayAreaWatcherStatus
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaWatcherStatus
{
    DisplayAreaWatcherStatus_Created = 0,
    DisplayAreaWatcherStatus_Started = 1,
    DisplayAreaWatcherStatus_EnumerationCompleted = 2,
    DisplayAreaWatcherStatus_Stopping = 3,
    DisplayAreaWatcherStatus_Stopped = 4,
    DisplayAreaWatcherStatus_Aborted = 5,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.IconShowOptions
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CWindowing_CIconShowOptions
{
    IconShowOptions_ShowIconAndSystemMenu = 0,
    IconShowOptions_HideIconAndSystemMenu = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.OverlappedPresenterState
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CUI_CWindowing_COverlappedPresenterState
{
    OverlappedPresenterState_Maximized = 0,
    OverlappedPresenterState_Minimized = 1,
    OverlappedPresenterState_Restored = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.UI.Windowing.TitleBarHeightOption
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarHeightOption
{
    TitleBarHeightOption_Standard = 0,
    TitleBarHeightOption_Tall = 1,
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
    TitleBarHeightOption_Collapsed = 2,
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Struct Microsoft.UI.Windowing.TitleBarTheme
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarTheme
{
    TitleBarTheme_Legacy = 0,
    TitleBarTheme_UseDefaultAppMode = 1,
    TitleBarTheme_Light = 2,
    TitleBarTheme_Dark = 3,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow[] = L"Microsoft.UI.Windowing.IAppWindow";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* get_IsShownInSwitchers)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsShownInSwitchers)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsVisible)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_OwnerWindowId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* get_Position)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* value);
    HRESULT (STDMETHODCALLTYPE* get_Presenter)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter** value);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32* value);
    HRESULT (STDMETHODCALLTYPE* get_Title)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Title)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_TitleBar)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar** value);
    HRESULT (STDMETHODCALLTYPE* Destroy)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This);
    HRESULT (STDMETHODCALLTYPE* Hide)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This);
    HRESULT (STDMETHODCALLTYPE* Move)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 position);
    HRESULT (STDMETHODCALLTYPE* MoveAndResize)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 rect);
    HRESULT (STDMETHODCALLTYPE* MoveAndResizeRelativeToDisplayArea)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 rect,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* displayarea);
    HRESULT (STDMETHODCALLTYPE* Resize)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32 size);
    HRESULT (STDMETHODCALLTYPE* SetIcon)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        HSTRING iconPath);
    HRESULT (STDMETHODCALLTYPE* SetIconWithIconId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        struct __x_ABI_CMicrosoft_CUI_CIconId iconId);
    HRESULT (STDMETHODCALLTYPE* SetPresenter)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* appWindowPresenter);
    HRESULT (STDMETHODCALLTYPE* SetPresenterByKind)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CAppWindowPresenterKind appWindowPresenterKind);
    HRESULT (STDMETHODCALLTYPE* Show)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This);
    HRESULT (STDMETHODCALLTYPE* ShowWithActivation)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        boolean activateWindow);
    HRESULT (STDMETHODCALLTYPE* add_Changed)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowChangedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Changed)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_Closing)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_Microsoft__CUI__CWindowing__CAppWindowClosingEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Closing)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_Destroying)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CAppWindow_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Destroying)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_IsShownInSwitchers(This, value) \
    ((This)->lpVtbl->get_IsShownInSwitchers(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_put_IsShownInSwitchers(This, value) \
    ((This)->lpVtbl->put_IsShownInSwitchers(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_IsVisible(This, value) \
    ((This)->lpVtbl->get_IsVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_OwnerWindowId(This, value) \
    ((This)->lpVtbl->get_OwnerWindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_Position(This, value) \
    ((This)->lpVtbl->get_Position(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_Presenter(This, value) \
    ((This)->lpVtbl->get_Presenter(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_Size(This, value) \
    ((This)->lpVtbl->get_Size(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_Title(This, value) \
    ((This)->lpVtbl->get_Title(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_put_Title(This, value) \
    ((This)->lpVtbl->put_Title(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_get_TitleBar(This, value) \
    ((This)->lpVtbl->get_TitleBar(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_Destroy(This) \
    ((This)->lpVtbl->Destroy(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_Hide(This) \
    ((This)->lpVtbl->Hide(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_Move(This, position) \
    ((This)->lpVtbl->Move(This, position))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_MoveAndResize(This, rect) \
    ((This)->lpVtbl->MoveAndResize(This, rect))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_MoveAndResizeRelativeToDisplayArea(This, rect, displayarea) \
    ((This)->lpVtbl->MoveAndResizeRelativeToDisplayArea(This, rect, displayarea))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_Resize(This, size) \
    ((This)->lpVtbl->Resize(This, size))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_SetIcon(This, iconPath) \
    ((This)->lpVtbl->SetIcon(This, iconPath))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_SetIconWithIconId(This, iconId) \
    ((This)->lpVtbl->SetIconWithIconId(This, iconId))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_SetPresenter(This, appWindowPresenter) \
    ((This)->lpVtbl->SetPresenter(This, appWindowPresenter))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_SetPresenterByKind(This, appWindowPresenterKind) \
    ((This)->lpVtbl->SetPresenterByKind(This, appWindowPresenterKind))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_Show(This) \
    ((This)->lpVtbl->Show(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_ShowWithActivation(This, activateWindow) \
    ((This)->lpVtbl->ShowWithActivation(This, activateWindow))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_add_Changed(This, handler, token) \
    ((This)->lpVtbl->add_Changed(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_remove_Changed(This, token) \
    ((This)->lpVtbl->remove_Changed(This, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_add_Closing(This, handler, token) \
    ((This)->lpVtbl->add_Closing(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_remove_Closing(This, token) \
    ((This)->lpVtbl->remove_Closing(This, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_add_Destroying(This, handler, token) \
    ((This)->lpVtbl->add_Destroying(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_remove_Destroying(This, token) \
    ((This)->lpVtbl->remove_Destroying(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow2[] = L"Microsoft.UI.Windowing.IAppWindow2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ClientSize)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32* value);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderAtBottom)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderAtTop)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderBelow)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId);
    HRESULT (STDMETHODCALLTYPE* ResizeClient)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32 size);
    HRESULT (STDMETHODCALLTYPE* ShowOnceWithRequestedStartupState)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_get_ClientSize(This, value) \
    ((This)->lpVtbl->get_ClientSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_MoveInZOrderAtBottom(This) \
    ((This)->lpVtbl->MoveInZOrderAtBottom(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_MoveInZOrderAtTop(This) \
    ((This)->lpVtbl->MoveInZOrderAtTop(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_MoveInZOrderBelow(This, windowId) \
    ((This)->lpVtbl->MoveInZOrderBelow(This, windowId))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_ResizeClient(This, size) \
    ((This)->lpVtbl->ResizeClient(This, size))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_ShowOnceWithRequestedStartupState(This) \
    ((This)->lpVtbl->ShowOnceWithRequestedStartupState(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow3[] = L"Microsoft.UI.Windowing.IAppWindow3";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* AssociateWithDispatcherQueue)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* dispatcherQueue);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_AssociateWithDispatcherQueue(This, dispatcherQueue) \
    ((This)->lpVtbl->AssociateWithDispatcherQueue(This, dispatcherQueue))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindow4
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindow4[] = L"Microsoft.UI.Windowing.IAppWindow4";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SetTaskbarIcon)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        HSTRING iconPath);
    HRESULT (STDMETHODCALLTYPE* SetTaskbarIconWithIconId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        struct __x_ABI_CMicrosoft_CUI_CIconId iconId);
    HRESULT (STDMETHODCALLTYPE* SetTitleBarIcon)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        HSTRING iconPath);
    HRESULT (STDMETHODCALLTYPE* SetTitleBarIconWithIconId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4* This,
        struct __x_ABI_CMicrosoft_CUI_CIconId iconId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_SetTaskbarIcon(This, iconPath) \
    ((This)->lpVtbl->SetTaskbarIcon(This, iconPath))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_SetTaskbarIconWithIconId(This, iconId) \
    ((This)->lpVtbl->SetTaskbarIconWithIconId(This, iconId))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_SetTitleBarIcon(This, iconPath) \
    ((This)->lpVtbl->SetTitleBarIcon(This, iconPath))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_SetTitleBarIconWithIconId(This, iconId) \
    ((This)->lpVtbl->SetTitleBarIconWithIconId(This, iconId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow4_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowChangedEventArgs[] = L"Microsoft.UI.Windowing.IAppWindowChangedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidPositionChange)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidPresenterChange)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidSizeChange)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidVisibilityChange)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_get_DidPositionChange(This, value) \
    ((This)->lpVtbl->get_DidPositionChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_get_DidPresenterChange(This, value) \
    ((This)->lpVtbl->get_DidPresenterChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_get_DidSizeChange(This, value) \
    ((This)->lpVtbl->get_DidSizeChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_get_DidVisibilityChange(This, value) \
    ((This)->lpVtbl->get_DidVisibilityChange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowChangedEventArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowChangedEventArgs2[] = L"Microsoft.UI.Windowing.IAppWindowChangedEventArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidZOrderChange)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsZOrderAtBottom)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsZOrderAtTop)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ZOrderBelowWindowId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_get_DidZOrderChange(This, value) \
    ((This)->lpVtbl->get_DidZOrderChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_get_IsZOrderAtBottom(This, value) \
    ((This)->lpVtbl->get_IsZOrderAtBottom(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_get_IsZOrderAtTop(This, value) \
    ((This)->lpVtbl->get_IsZOrderAtTop(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_get_ZOrderBelowWindowId(This, value) \
    ((This)->lpVtbl->get_ZOrderBelowWindowId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowChangedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowClosingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowClosingEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowClosingEventArgs[] = L"Microsoft.UI.Windowing.IAppWindowClosingEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Cancel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Cancel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_get_Cancel(This, value) \
    ((This)->lpVtbl->get_Cancel(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_put_Cancel(This, value) \
    ((This)->lpVtbl->put_Cancel(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowClosingEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowPresenter[] = L"Microsoft.UI.Windowing.IAppWindowPresenter";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Kind)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CAppWindowPresenterKind* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_get_Kind(This, value) \
    ((This)->lpVtbl->get_Kind(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowPresenterFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowPresenterFactory[] = L"Microsoft.UI.Windowing.IAppWindowPresenterFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowStatics[] = L"Microsoft.UI.Windowing.IAppWindowStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow** result);
    HRESULT (STDMETHODCALLTYPE* CreateWithPresenter)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* appWindowPresenter,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow** result);
    HRESULT (STDMETHODCALLTYPE* CreateWithPresenterAndOwner)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* appWindowPresenter,
        struct __x_ABI_CMicrosoft_CUI_CWindowId ownerWindowId,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow** result);
    HRESULT (STDMETHODCALLTYPE* GetFromWindowId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_Create(This, result) \
    ((This)->lpVtbl->Create(This, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_CreateWithPresenter(This, appWindowPresenter, result) \
    ((This)->lpVtbl->CreateWithPresenter(This, appWindowPresenter, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_CreateWithPresenterAndOwner(This, appWindowPresenter, ownerWindowId, result) \
    ((This)->lpVtbl->CreateWithPresenterAndOwner(This, appWindowPresenter, ownerWindowId, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_GetFromWindowId(This, windowId, result) \
    ((This)->lpVtbl->GetFromWindowId(This, windowId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindow
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowStatics2[] = L"Microsoft.UI.Windowing.IAppWindowStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateWithDispatcherQueue)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowPresenter* appWindowPresenter,
        struct __x_ABI_CMicrosoft_CUI_CWindowId ownerWindowId,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* DispatcherQueue,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindow** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_CreateWithDispatcherQueue(This, appWindowPresenter, ownerWindowId, DispatcherQueue, result) \
    ((This)->lpVtbl->CreateWithDispatcherQueue(This, appWindowPresenter, ownerWindowId, DispatcherQueue, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBar
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBar[] = L"Microsoft.UI.Windowing.IAppWindowTitleBar";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_BackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_BackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonHoverBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonHoverBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonHoverForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonHoverForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonInactiveBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonInactiveBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonInactiveForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonInactiveForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonPressedBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonPressedBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ButtonPressedForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ButtonPressedForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendsContentIntoTitleBar)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ExtendsContentIntoTitleBar)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_ForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_Height)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_IconShowOptions)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CIconShowOptions* value);
    HRESULT (STDMETHODCALLTYPE* put_IconShowOptions)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CIconShowOptions value);
    HRESULT (STDMETHODCALLTYPE* get_InactiveBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_InactiveBackgroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_InactiveForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor** value);
    HRESULT (STDMETHODCALLTYPE* put_InactiveForegroundColor)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        __FIReference_1_Windows__CUI__CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_LeftInset)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_RightInset)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* ResetToDefault)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This);
    HRESULT (STDMETHODCALLTYPE* SetDragRectangles)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar* This,
        UINT32 valueLength,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_BackgroundColor(This, value) \
    ((This)->lpVtbl->get_BackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_BackgroundColor(This, value) \
    ((This)->lpVtbl->put_BackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonBackgroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonBackgroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonForegroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonForegroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonHoverBackgroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonHoverBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonHoverBackgroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonHoverBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonHoverForegroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonHoverForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonHoverForegroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonHoverForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonInactiveBackgroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonInactiveBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonInactiveBackgroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonInactiveBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonInactiveForegroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonInactiveForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonInactiveForegroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonInactiveForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonPressedBackgroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonPressedBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonPressedBackgroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonPressedBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ButtonPressedForegroundColor(This, value) \
    ((This)->lpVtbl->get_ButtonPressedForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ButtonPressedForegroundColor(This, value) \
    ((This)->lpVtbl->put_ButtonPressedForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ExtendsContentIntoTitleBar(This, value) \
    ((This)->lpVtbl->get_ExtendsContentIntoTitleBar(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ExtendsContentIntoTitleBar(This, value) \
    ((This)->lpVtbl->put_ExtendsContentIntoTitleBar(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_ForegroundColor(This, value) \
    ((This)->lpVtbl->get_ForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_ForegroundColor(This, value) \
    ((This)->lpVtbl->put_ForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_Height(This, value) \
    ((This)->lpVtbl->get_Height(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_IconShowOptions(This, value) \
    ((This)->lpVtbl->get_IconShowOptions(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_IconShowOptions(This, value) \
    ((This)->lpVtbl->put_IconShowOptions(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_InactiveBackgroundColor(This, value) \
    ((This)->lpVtbl->get_InactiveBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_InactiveBackgroundColor(This, value) \
    ((This)->lpVtbl->put_InactiveBackgroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_InactiveForegroundColor(This, value) \
    ((This)->lpVtbl->get_InactiveForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_put_InactiveForegroundColor(This, value) \
    ((This)->lpVtbl->put_InactiveForegroundColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_LeftInset(This, value) \
    ((This)->lpVtbl->get_LeftInset(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_get_RightInset(This, value) \
    ((This)->lpVtbl->get_RightInset(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_ResetToDefault(This) \
    ((This)->lpVtbl->ResetToDefault(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_SetDragRectangles(This, valueLength, value) \
    ((This)->lpVtbl->SetDragRectangles(This, valueLength, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBar2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBar2[] = L"Microsoft.UI.Windowing.IAppWindowTitleBar2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PreferredHeightOption)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarHeightOption* value);
    HRESULT (STDMETHODCALLTYPE* put_PreferredHeightOption)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarHeightOption value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_get_PreferredHeightOption(This, value) \
    ((This)->lpVtbl->get_PreferredHeightOption(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_put_PreferredHeightOption(This, value) \
    ((This)->lpVtbl->put_PreferredHeightOption(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBar3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBar3[] = L"Microsoft.UI.Windowing.IAppWindowTitleBar3";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PreferredTheme)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarTheme* value);
    HRESULT (STDMETHODCALLTYPE* put_PreferredTheme)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CTitleBarTheme value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_get_PreferredTheme(This, value) \
    ((This)->lpVtbl->get_PreferredTheme(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_put_PreferredTheme(This, value) \
    ((This)->lpVtbl->put_PreferredTheme(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBar3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IAppWindowTitleBarStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.AppWindowTitleBar
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IAppWindowTitleBarStatics[] = L"Microsoft.UI.Windowing.IAppWindowTitleBarStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsCustomizationSupported)(__x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_IsCustomizationSupported(This, result) \
    ((This)->lpVtbl->IsCustomizationSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIAppWindowTitleBarStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.ICompactOverlayPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.CompactOverlayPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_ICompactOverlayPresenter[] = L"Microsoft.UI.Windowing.ICompactOverlayPresenter";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_InitialSize)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CCompactOverlaySize* value);
    HRESULT (STDMETHODCALLTYPE* put_InitialSize)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CCompactOverlaySize value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_get_InitialSize(This, value) \
    ((This)->lpVtbl->get_InitialSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_put_InitialSize(This, value) \
    ((This)->lpVtbl->put_InitialSize(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.ICompactOverlayPresenterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.CompactOverlayPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_ICompactOverlayPresenterStatics[] = L"Microsoft.UI.Windowing.ICompactOverlayPresenterStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenter** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_Create(This, result) \
    ((This)->lpVtbl->Create(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CICompactOverlayPresenterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayArea
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayArea
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayArea[] = L"Microsoft.UI.Windowing.IDisplayArea";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DisplayId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId* value);
    HRESULT (STDMETHODCALLTYPE* get_IsPrimary)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_OuterBounds)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* value);
    HRESULT (STDMETHODCALLTYPE* get_WorkArea)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_get_DisplayId(This, value) \
    ((This)->lpVtbl->get_DisplayId(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_get_IsPrimary(This, value) \
    ((This)->lpVtbl->get_IsPrimary(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_get_OuterBounds(This, value) \
    ((This)->lpVtbl->get_OuterBounds(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_get_WorkArea(This, value) \
    ((This)->lpVtbl->get_WorkArea(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayAreaStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayArea
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayAreaStatics[] = L"Microsoft.UI.Windowing.IDisplayAreaStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Primary)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** value);
    HRESULT (STDMETHODCALLTYPE* CreateWatcher)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher** result);
    HRESULT (STDMETHODCALLTYPE* FindAll)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        __FIVectorView_1_Microsoft__CUI__CWindowing__CDisplayArea** result);
    HRESULT (STDMETHODCALLTYPE* GetFromWindowId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaFallback displayAreaFallback,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** result);
    HRESULT (STDMETHODCALLTYPE* GetFromPoint)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 point,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaFallback displayAreaFallback,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** result);
    HRESULT (STDMETHODCALLTYPE* GetFromRect)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 rect,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaFallback displayAreaFallback,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_get_Primary(This, value) \
    ((This)->lpVtbl->get_Primary(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_CreateWatcher(This, result) \
    ((This)->lpVtbl->CreateWatcher(This, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_FindAll(This, result) \
    ((This)->lpVtbl->FindAll(This, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_GetFromWindowId(This, windowId, displayAreaFallback, result) \
    ((This)->lpVtbl->GetFromWindowId(This, windowId, displayAreaFallback, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_GetFromPoint(This, point, displayAreaFallback, result) \
    ((This)->lpVtbl->GetFromPoint(This, point, displayAreaFallback, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_GetFromRect(This, rect, displayAreaFallback, result) \
    ((This)->lpVtbl->GetFromRect(This, rect, displayAreaFallback, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayAreaStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.2
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayArea
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayAreaStatics2[] = L"Microsoft.UI.Windowing.IDisplayAreaStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetFromDisplayId)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId displayId,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayArea** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_GetFromDisplayId(This, displayId, result) \
    ((This)->lpVtbl->GetFromDisplayId(This, displayId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10002

/*
 *
 * Interface Microsoft.UI.Windowing.IDisplayAreaWatcher
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.DisplayAreaWatcher
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IDisplayAreaWatcher[] = L"Microsoft.UI.Windowing.IDisplayAreaWatcher";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcherVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_CDisplayAreaWatcherStatus* value);
    HRESULT (STDMETHODCALLTYPE* Start)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This);
    HRESULT (STDMETHODCALLTYPE* Stop)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This);
    HRESULT (STDMETHODCALLTYPE* add_Added)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Added)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_EnumerationCompleted)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_EnumerationCompleted)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_Removed)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Removed)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_Stopped)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Stopped)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_Updated)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        __FITypedEventHandler_2_Microsoft__CUI__CWindowing__CDisplayAreaWatcher_Microsoft__CUI__CWindowing__CDisplayArea* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_Updated)(__x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcherVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcherVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_Start(This) \
    ((This)->lpVtbl->Start(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_Stop(This) \
    ((This)->lpVtbl->Stop(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_add_Added(This, handler, token) \
    ((This)->lpVtbl->add_Added(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_remove_Added(This, token) \
    ((This)->lpVtbl->remove_Added(This, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_add_EnumerationCompleted(This, handler, token) \
    ((This)->lpVtbl->add_EnumerationCompleted(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_remove_EnumerationCompleted(This, token) \
    ((This)->lpVtbl->remove_EnumerationCompleted(This, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_add_Removed(This, handler, token) \
    ((This)->lpVtbl->add_Removed(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_remove_Removed(This, token) \
    ((This)->lpVtbl->remove_Removed(This, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_add_Stopped(This, handler, token) \
    ((This)->lpVtbl->add_Stopped(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_remove_Stopped(This, token) \
    ((This)->lpVtbl->remove_Stopped(This, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_add_Updated(This, handler, token) \
    ((This)->lpVtbl->add_Updated(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_remove_Updated(This, token) \
    ((This)->lpVtbl->remove_Updated(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIDisplayAreaWatcher_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IFullScreenPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.FullScreenPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IFullScreenPresenter[] = L"Microsoft.UI.Windowing.IFullScreenPresenter";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IFullScreenPresenterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.FullScreenPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IFullScreenPresenterStatics[] = L"Microsoft.UI.Windowing.IFullScreenPresenterStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenter** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_Create(This, result) \
    ((This)->lpVtbl->Create(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIFullScreenPresenterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenter[] = L"Microsoft.UI.Windowing.IOverlappedPresenter";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_HasBorder)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_HasTitleBar)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsAlwaysOnTop)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsAlwaysOnTop)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsMaximizable)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsMaximizable)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsMinimizable)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsMinimizable)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsModal)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsModal)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsResizable)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsResizable)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_State)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_COverlappedPresenterState* value);
    HRESULT (STDMETHODCALLTYPE* Maximize)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This);
    HRESULT (STDMETHODCALLTYPE* Minimize)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This);
    HRESULT (STDMETHODCALLTYPE* Restore)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This);
    HRESULT (STDMETHODCALLTYPE* SetBorderAndTitleBar)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter* This,
        boolean hasBorder,
        boolean hasTitleBar);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_HasBorder(This, value) \
    ((This)->lpVtbl->get_HasBorder(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_HasTitleBar(This, value) \
    ((This)->lpVtbl->get_HasTitleBar(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_IsAlwaysOnTop(This, value) \
    ((This)->lpVtbl->get_IsAlwaysOnTop(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_put_IsAlwaysOnTop(This, value) \
    ((This)->lpVtbl->put_IsAlwaysOnTop(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_IsMaximizable(This, value) \
    ((This)->lpVtbl->get_IsMaximizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_put_IsMaximizable(This, value) \
    ((This)->lpVtbl->put_IsMaximizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_IsMinimizable(This, value) \
    ((This)->lpVtbl->get_IsMinimizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_put_IsMinimizable(This, value) \
    ((This)->lpVtbl->put_IsMinimizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_IsModal(This, value) \
    ((This)->lpVtbl->get_IsModal(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_put_IsModal(This, value) \
    ((This)->lpVtbl->put_IsModal(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_IsResizable(This, value) \
    ((This)->lpVtbl->get_IsResizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_put_IsResizable(This, value) \
    ((This)->lpVtbl->put_IsResizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_get_State(This, value) \
    ((This)->lpVtbl->get_State(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_Maximize(This) \
    ((This)->lpVtbl->Maximize(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_Minimize(This) \
    ((This)->lpVtbl->Minimize(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_Restore(This) \
    ((This)->lpVtbl->Restore(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_SetBorderAndTitleBar(This, hasBorder, hasTitleBar) \
    ((This)->lpVtbl->SetBorderAndTitleBar(This, hasBorder, hasTitleBar))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenter2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenter2[] = L"Microsoft.UI.Windowing.IOverlappedPresenter2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* MinimizeWithActivation)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This,
        boolean activateWindow);
    HRESULT (STDMETHODCALLTYPE* RestoreWithActivation)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2* This,
        boolean activateWindow);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_MinimizeWithActivation(This, activateWindow) \
    ((This)->lpVtbl->MinimizeWithActivation(This, activateWindow))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_RestoreWithActivation(This, activateWindow) \
    ((This)->lpVtbl->RestoreWithActivation(This, activateWindow))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenter3
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenter3[] = L"Microsoft.UI.Windowing.IOverlappedPresenter3";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_PreferredMinimumHeight)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int** value);
    HRESULT (STDMETHODCALLTYPE* put_PreferredMinimumHeight)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int* value);
    HRESULT (STDMETHODCALLTYPE* get_PreferredMinimumWidth)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int** value);
    HRESULT (STDMETHODCALLTYPE* put_PreferredMinimumWidth)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int* value);
    HRESULT (STDMETHODCALLTYPE* get_PreferredMaximumWidth)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int** value);
    HRESULT (STDMETHODCALLTYPE* put_PreferredMaximumWidth)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int* value);
    HRESULT (STDMETHODCALLTYPE* get_PreferredMaximumHeight)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int** value);
    HRESULT (STDMETHODCALLTYPE* put_PreferredMaximumHeight)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3* This,
        __FIReference_1_int* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_get_PreferredMinimumHeight(This, value) \
    ((This)->lpVtbl->get_PreferredMinimumHeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_put_PreferredMinimumHeight(This, value) \
    ((This)->lpVtbl->put_PreferredMinimumHeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_get_PreferredMinimumWidth(This, value) \
    ((This)->lpVtbl->get_PreferredMinimumWidth(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_put_PreferredMinimumWidth(This, value) \
    ((This)->lpVtbl->put_PreferredMinimumWidth(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_get_PreferredMaximumWidth(This, value) \
    ((This)->lpVtbl->get_PreferredMaximumWidth(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_put_PreferredMaximumWidth(This, value) \
    ((This)->lpVtbl->put_PreferredMaximumWidth(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_get_PreferredMaximumHeight(This, value) \
    ((This)->lpVtbl->get_PreferredMaximumHeight(This, value))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_put_PreferredMaximumHeight(This, value) \
    ((This)->lpVtbl->put_PreferredMaximumHeight(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenterStatics[] = L"Microsoft.UI.Windowing.IOverlappedPresenterStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter** result);
    HRESULT (STDMETHODCALLTYPE* CreateForContextMenu)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter** result);
    HRESULT (STDMETHODCALLTYPE* CreateForDialog)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter** result);
    HRESULT (STDMETHODCALLTYPE* CreateForToolWindow)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics* This,
        __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenter** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_Create(This, result) \
    ((This)->lpVtbl->Create(This, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_CreateForContextMenu(This, result) \
    ((This)->lpVtbl->CreateForContextMenu(This, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_CreateForDialog(This, result) \
    ((This)->lpVtbl->CreateForDialog(This, result))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_CreateForToolWindow(This, result) \
    ((This)->lpVtbl->CreateForToolWindow(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Windowing.IOverlappedPresenterStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.1
 *
 * Interface is a part of the implementation of type Microsoft.UI.Windowing.OverlappedPresenter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001
#if !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Windowing_IOverlappedPresenterStatics2[] = L"Microsoft.UI.Windowing.IOverlappedPresenterStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RequestedStartupState)(__x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2* This,
        enum __x_ABI_CMicrosoft_CUI_CWindowing_COverlappedPresenterState* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_get_RequestedStartupState(This, value) \
    ((This)->lpVtbl->get_RequestedStartupState(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CWindowing_CIOverlappedPresenterStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10001

/*
 *
 * Class Microsoft.UI.Windowing.AppWindow
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IAppWindowStatics2 interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Windowing.IAppWindowStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindow ** Default Interface **
 *    Microsoft.UI.Windowing.IAppWindow2
 *    Microsoft.UI.Windowing.IAppWindow3
 *    Microsoft.UI.Windowing.IAppWindow4
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindow_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindow_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindow[] = L"Microsoft.UI.Windowing.AppWindow";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowChangedEventArgs ** Default Interface **
 *    Microsoft.UI.Windowing.IAppWindowChangedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowChangedEventArgs[] = L"Microsoft.UI.Windowing.AppWindowChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowClosingEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowClosingEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowClosingEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowClosingEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowClosingEventArgs[] = L"Microsoft.UI.Windowing.AppWindowClosingEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowPresenter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowPresenter[] = L"Microsoft.UI.Windowing.AppWindowPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.AppWindowTitleBar
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IAppWindowTitleBarStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IAppWindowTitleBar ** Default Interface **
 *    Microsoft.UI.Windowing.IAppWindowTitleBar2
 *    Microsoft.UI.Windowing.IAppWindowTitleBar3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowTitleBar_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_AppWindowTitleBar_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_AppWindowTitleBar[] = L"Microsoft.UI.Windowing.AppWindowTitleBar";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.CompactOverlayPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.ICompactOverlayPresenterStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.ICompactOverlayPresenter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_CompactOverlayPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_CompactOverlayPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_CompactOverlayPresenter[] = L"Microsoft.UI.Windowing.CompactOverlayPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.DisplayArea
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IDisplayAreaStatics2 interface starting with version 1.2 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Windowing.IDisplayAreaStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IDisplayArea ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_DisplayArea_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_DisplayArea_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_DisplayArea[] = L"Microsoft.UI.Windowing.DisplayArea";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.DisplayAreaWatcher
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IDisplayAreaWatcher ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_DisplayAreaWatcher_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_DisplayAreaWatcher_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_DisplayAreaWatcher[] = L"Microsoft.UI.Windowing.DisplayAreaWatcher";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.FullScreenPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IFullScreenPresenterStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IFullScreenPresenter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_FullScreenPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_FullScreenPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_FullScreenPresenter[] = L"Microsoft.UI.Windowing.FullScreenPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Windowing.OverlappedPresenter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Windowing.IOverlappedPresenterStatics interface starting with version 1.0 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Windowing.IOverlappedPresenterStatics2 interface starting with version 1.1 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Windowing.IOverlappedPresenter ** Default Interface **
 *    Microsoft.UI.Windowing.IOverlappedPresenter2
 *    Microsoft.UI.Windowing.IOverlappedPresenter3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Windowing_OverlappedPresenter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Windowing_OverlappedPresenter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Windowing_OverlappedPresenter[] = L"Microsoft.UI.Windowing.OverlappedPresenter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Ewindowing_p_h__

#endif // __microsoft2Eui2Ewindowing_h__
