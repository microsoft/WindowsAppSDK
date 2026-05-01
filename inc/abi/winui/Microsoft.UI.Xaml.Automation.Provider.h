
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
#ifndef __microsoft2Eui2Examl2Eautomation2Eprovider_h__
#define __microsoft2Eui2Examl2Eautomation2Eprovider_h__
#ifndef __microsoft2Eui2Examl2Eautomation2Eprovider_p_h__
#define __microsoft2Eui2Examl2Eautomation2Eprovider_p_h__


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
#include "Microsoft.UI.Xaml.Automation.h"
#include "Microsoft.UI.Xaml.Automation.Peers.h"
#include "Microsoft.UI.Xaml.Automation.Text.h"
#include "Windows.UI.h"

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IAnnotationProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IAnnotationProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ICustomNavigationProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ICustomNavigationProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IDockProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IDockProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IDragProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IDragProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IDropTargetProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IDropTargetProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IExpandCollapseProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IExpandCollapseProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IGridItemProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IGridItemProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IGridProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IGridProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IIRawElementProviderSimple;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IInvokeProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IInvokeProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IItemContainerProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IItemContainerProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IMultipleViewProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IMultipleViewProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IObjectModelProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IObjectModelProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IRangeValueProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IRangeValueProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IScrollItemProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IScrollItemProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IScrollProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IScrollProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ISelectionItemProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ISelectionItemProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ISelectionProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ISelectionProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ISpreadsheetItemProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ISpreadsheetItemProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ISpreadsheetProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ISpreadsheetProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IStylesProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IStylesProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ISynchronizedInputProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ISynchronizedInputProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITableItemProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITableItemProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITableProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITableProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITextChildProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITextChildProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITextEditProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITextEditProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITextProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITextProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITextProvider2;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2 ABI::Microsoft::UI::Xaml::Automation::Provider::ITextProvider2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITextRangeProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITextRangeProvider2;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2 ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IToggleProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IToggleProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITransformProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider ABI::Microsoft::UI::Xaml::Automation::Provider::ITransformProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface ITransformProvider2;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2 ABI::Microsoft::UI::Xaml::Automation::Provider::ITransformProvider2

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IValueProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IValueProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IVirtualizedItemProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IVirtualizedItemProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        interface IWindowProvider;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider ABI::Microsoft::UI::Xaml::Automation::Provider::IWindowProvider

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum AnnotationType : int AnnotationType;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    class AutomationProperty;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    interface IAutomationProperty;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty ABI::Microsoft::UI::Xaml::Automation::IAutomationProperty

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum DockPosition : int DockPosition;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum ExpandCollapseState : int ExpandCollapseState;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Peers {
                        typedef enum AutomationNavigationDirection : int AutomationNavigationDirection;
                    } /* Peers */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum RowOrColumnMajor : int RowOrColumnMajor;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum ScrollAmount : int ScrollAmount;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum SupportedTextSelection : int SupportedTextSelection;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum SynchronizedInputType : int SynchronizedInputType;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Text {
                        typedef enum TextPatternRangeEndpoint : int TextPatternRangeEndpoint;
                    } /* Text */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Text {
                        typedef enum TextUnit : int TextUnit;
                    } /* Text */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum ToggleState : int ToggleState;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum WindowInteractionState : int WindowInteractionState;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum WindowVisualState : int WindowVisualState;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    typedef enum ZoomUnit : int ZoomUnit;
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
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
        namespace UI {
            typedef struct Color Color;
        } /* UI */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        class IRawElementProviderSimple;
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IAnnotationProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IAnnotationProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IAnnotationProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("546ab18e-986d-5deb-8f2a-2d9303a43006")
                        IAnnotationProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_AnnotationTypeId(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_AnnotationTypeName(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Author(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_DateTime(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Target(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IAnnotationProvider = _uuidof(IAnnotationProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ICustomNavigationProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ICustomNavigationProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ICustomNavigationProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("cad51322-faa9-5a2b-90f0-b762c46178b3")
                        ICustomNavigationProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE NavigateCustom(
                                ABI::Microsoft::UI::Xaml::Automation::Peers::AutomationNavigationDirection direction,
                                IInspectable** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ICustomNavigationProvider = _uuidof(ICustomNavigationProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IDockProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IDockProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IDockProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("9882b971-70ea-5c6d-a818-7a7ab68c6f3b")
                        IDockProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_DockPosition(
                                ABI::Microsoft::UI::Xaml::Automation::DockPosition* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetDockPosition(
                                ABI::Microsoft::UI::Xaml::Automation::DockPosition dockPosition
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IDockProvider = _uuidof(IDockProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IDragProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IDragProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IDragProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("c60bb643-a356-5132-a258-ffba6c7480f2")
                        IDragProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_IsGrabbed(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_DropEffect(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_DropEffects(
                                UINT32* valueLength,
                                HSTRING** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetGrabbedItems(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IDragProvider = _uuidof(IDragProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IDropTargetProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IDropTargetProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IDropTargetProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("9b2a9f3d-bbb1-510d-99e8-0e0ae14a6e3b")
                        IDropTargetProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_DropEffect(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_DropEffects(
                                UINT32* valueLength,
                                HSTRING** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IDropTargetProvider = _uuidof(IDropTargetProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IExpandCollapseProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IExpandCollapseProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IExpandCollapseProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("6cef349c-b181-5d0b-b297-c3b0166120c3")
                        IExpandCollapseProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_ExpandCollapseState(
                                ABI::Microsoft::UI::Xaml::Automation::ExpandCollapseState* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Collapse(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Expand(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IExpandCollapseProvider = _uuidof(IExpandCollapseProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IGridItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IGridItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IGridItemProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("d2557a0e-6909-5170-a680-60728df339b4")
                        IGridItemProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_Column(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ColumnSpan(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ContainingGrid(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Row(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RowSpan(
                                INT32* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IGridItemProvider = _uuidof(IGridItemProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IGridProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IGridProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IGridProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("50992d5e-d225-56e9-a25a-78c372e81955")
                        IGridProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_ColumnCount(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_RowCount(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetItem(
                                INT32 row,
                                INT32 column,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IGridProvider = _uuidof(IGridProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IIRawElementProviderSimple
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Automation.Provider.IRawElementProviderSimple
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IIRawElementProviderSimple[] = L"Microsoft.UI.Xaml.Automation.Provider.IIRawElementProviderSimple";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("f90bc239-ade2-55c9-a838-a3b0579763c5")
                        IIRawElementProviderSimple : public IInspectable
                        {
                        public:
                        };

                        MIDL_CONST_ID IID& IID_IIRawElementProviderSimple = _uuidof(IIRawElementProviderSimple);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IInvokeProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IInvokeProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IInvokeProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("02481105-3378-544d-b4e1-a1b368afbc02")
                        IInvokeProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE Invoke(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IInvokeProvider = _uuidof(IInvokeProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IItemContainerProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IItemContainerProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IItemContainerProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("ad297363-694e-5885-997d-a2d6dff415a7")
                        IItemContainerProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE FindItemByProperty(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple* startAfter,
                                ABI::Microsoft::UI::Xaml::Automation::IAutomationProperty* automationProperty,
                                IInspectable* value,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IItemContainerProvider = _uuidof(IItemContainerProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IMultipleViewProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IMultipleViewProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IMultipleViewProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("60be5484-3d8f-51fd-beab-423422ee1e03")
                        IMultipleViewProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_CurrentView(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetSupportedViews(
                                UINT32* resultLength,
                                INT32** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetViewName(
                                INT32 viewId,
                                HSTRING* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetCurrentView(
                                INT32 viewId
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IMultipleViewProvider = _uuidof(IMultipleViewProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IObjectModelProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IObjectModelProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IObjectModelProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("92953ed0-4bd8-5624-8e3d-78d45fde9cf2")
                        IObjectModelProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE GetUnderlyingObjectModel(
                                IInspectable** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IObjectModelProvider = _uuidof(IObjectModelProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IRangeValueProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IRangeValueProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IRangeValueProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("729ae414-1e8f-5020-82bb-bb574d145fd8")
                        IRangeValueProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_IsReadOnly(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_LargeChange(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Maximum(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Minimum(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_SmallChange(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Value(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetValue(
                                DOUBLE value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IRangeValueProvider = _uuidof(IRangeValueProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IScrollItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IScrollItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IScrollItemProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("8a6fb8eb-e5f1-58eb-8e72-8b95f236fc47")
                        IScrollItemProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE ScrollIntoView(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IScrollItemProvider = _uuidof(IScrollItemProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IScrollProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IScrollProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IScrollProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("7e2e5af3-ff50-5365-bcfe-ef424b2fd590")
                        IScrollProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_HorizontallyScrollable(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_HorizontalScrollPercent(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_HorizontalViewSize(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_VerticallyScrollable(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_VerticalScrollPercent(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_VerticalViewSize(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Scroll(
                                ABI::Microsoft::UI::Xaml::Automation::ScrollAmount horizontalAmount,
                                ABI::Microsoft::UI::Xaml::Automation::ScrollAmount verticalAmount
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetScrollPercent(
                                DOUBLE horizontalPercent,
                                DOUBLE verticalPercent
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IScrollProvider = _uuidof(IScrollProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISelectionItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISelectionItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISelectionItemProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("c9dfdd81-d4ac-5d31-be7f-24fab16060e4")
                        ISelectionItemProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_IsSelected(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_SelectionContainer(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE AddToSelection(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE RemoveFromSelection(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Select(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ISelectionItemProvider = _uuidof(ISelectionItemProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISelectionProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISelectionProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISelectionProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("80d56d4e-0052-541f-9411-9d1778b3bfca")
                        ISelectionProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_CanSelectMultiple(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_IsSelectionRequired(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetSelection(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ISelectionProvider = _uuidof(ISelectionProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISpreadsheetItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetItemProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("51c1ce89-b21f-592c-8768-0accdefd5738")
                        ISpreadsheetItemProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_Formula(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetAnnotationObjects(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetAnnotationTypes(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::AnnotationType** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ISpreadsheetItemProvider = _uuidof(ISpreadsheetItemProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISpreadsheetProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("1ff41bac-d9e3-5e48-b5f8-9eab0fb2d9d8")
                        ISpreadsheetProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE GetItemByName(
                                HSTRING name,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ISpreadsheetProvider = _uuidof(ISpreadsheetProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IStylesProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IStylesProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IStylesProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("d8895839-0048-54de-9c1f-152de6665e80")
                        IStylesProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_ExtendedProperties(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FillColor(
                                ABI::Windows::UI::Color* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FillPatternColor(
                                ABI::Windows::UI::Color* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FillPatternStyle(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Shape(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_StyleId(
                                INT32* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_StyleName(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IStylesProvider = _uuidof(IStylesProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISynchronizedInputProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISynchronizedInputProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISynchronizedInputProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("c5615613-936d-5289-a190-e82057e0ff5a")
                        ISynchronizedInputProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE Cancel(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE StartListening(
                                ABI::Microsoft::UI::Xaml::Automation::SynchronizedInputType inputType
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ISynchronizedInputProvider = _uuidof(ISynchronizedInputProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITableItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITableItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITableItemProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("6ce6f038-54d4-5553-a4ad-03cbcf358197")
                        ITableItemProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE GetColumnHeaderItems(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetRowHeaderItems(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITableItemProvider = _uuidof(ITableItemProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITableProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITableProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITableProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("9aba6724-b22d-5db8-8abb-81f911f18af2")
                        ITableProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_RowOrColumnMajor(
                                ABI::Microsoft::UI::Xaml::Automation::RowOrColumnMajor* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetColumnHeaders(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetRowHeaders(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITableProvider = _uuidof(ITableProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextChildProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextChildProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextChildProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("7c72e55f-f75d-5522-aeb5-c1f82c32933b")
                        ITextChildProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_TextContainer(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_TextRange(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITextChildProvider = _uuidof(ITextChildProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextEditProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITextProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextEditProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextEditProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("7f09bbe8-bea7-5dd3-ba6b-28dbb402fad4")
                        ITextEditProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE GetActiveComposition(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetConversionTarget(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITextEditProvider = _uuidof(ITextEditProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("37e7dce6-fe7a-56a7-a47a-9462872c67ef")
                        ITextProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_DocumentRange(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_SupportedTextSelection(
                                ABI::Microsoft::UI::Xaml::Automation::SupportedTextSelection* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetSelection(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider*** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetVisibleRanges(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider*** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE RangeFromChild(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple* childElement,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE RangeFromPoint(
                                ABI::Windows::Foundation::Point screenLocation,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITextProvider = _uuidof(ITextProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextProvider2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITextProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextProvider2[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextProvider2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("6844f012-c7e6-5763-ba04-5b6db910cd34")
                        ITextProvider2 : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE RangeFromAnnotation(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple* annotationElement,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetCaretRange(
                                boolean* isActive,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** returnValue
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITextProvider2 = _uuidof(ITextProvider2);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextRangeProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("84210361-6ce2-5084-bf3b-28afa6e9851f")
                        ITextRangeProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE Clone(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Compare(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider* textRangeProvider,
                                boolean* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE CompareEndpoints(
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextPatternRangeEndpoint endpoint,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider* textRangeProvider,
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextPatternRangeEndpoint targetEndpoint,
                                INT32* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE ExpandToEnclosingUnit(
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextUnit unit
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE FindAttribute(
                                INT32 attributeId,
                                IInspectable* value,
                                boolean backward,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE FindText(
                                HSTRING text,
                                boolean backward,
                                boolean ignoreCase,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetAttributeValue(
                                INT32 attributeId,
                                IInspectable** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetBoundingRectangles(
                                UINT32* returnValueLength,
                                DOUBLE** returnValue
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetEnclosingElement(
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetText(
                                INT32 maxLength,
                                HSTRING* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Move(
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextUnit unit,
                                INT32 count,
                                INT32* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE MoveEndpointByUnit(
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextPatternRangeEndpoint endpoint,
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextUnit unit,
                                INT32 count,
                                INT32* result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE MoveEndpointByRange(
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextPatternRangeEndpoint endpoint,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::ITextRangeProvider* textRangeProvider,
                                ABI::Microsoft::UI::Xaml::Automation::Text::TextPatternRangeEndpoint targetEndpoint
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Select(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE AddToSelection(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE RemoveFromSelection(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE ScrollIntoView(
                                boolean alignToTop
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetChildren(
                                UINT32* resultLength,
                                ABI::Microsoft::UI::Xaml::Automation::Provider::IIRawElementProviderSimple*** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITextRangeProvider = _uuidof(ITextRangeProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextRangeProvider2[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("34d4a80e-36bb-5362-a53b-490428a8b367")
                        ITextRangeProvider2 : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITextRangeProvider2 = _uuidof(ITextRangeProvider2);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IToggleProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IToggleProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IToggleProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("021080c2-30a9-52ef-bc32-2b79847b6ba7")
                        IToggleProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_ToggleState(
                                ABI::Microsoft::UI::Xaml::Automation::ToggleState* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Toggle(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IToggleProvider = _uuidof(IToggleProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITransformProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITransformProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITransformProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("6fd76988-8f52-5ef2-a826-9c8c4951c911")
                        ITransformProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_CanMove(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CanResize(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CanRotate(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Move(
                                DOUBLE x,
                                DOUBLE y
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Resize(
                                DOUBLE width,
                                DOUBLE height
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Rotate(
                                DOUBLE degrees
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITransformProvider = _uuidof(ITransformProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITransformProvider2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITransformProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITransformProvider2[] = L"Microsoft.UI.Xaml.Automation.Provider.ITransformProvider2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("7d91d02d-8401-5cf8-bbc4-47391a524215")
                        ITransformProvider2 : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_CanZoom(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ZoomLevel(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_MaxZoom(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_MinZoom(
                                DOUBLE* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Zoom(
                                DOUBLE zoom
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE ZoomByUnit(
                                ABI::Microsoft::UI::Xaml::Automation::ZoomUnit zoomUnit
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ITransformProvider2 = _uuidof(ITransformProvider2);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IValueProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IValueProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IValueProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("984f11cf-4611-588e-b52e-b96a12322c71")
                        IValueProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_IsReadOnly(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Value(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetValue(
                                HSTRING value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IValueProvider = _uuidof(IValueProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IVirtualizedItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IVirtualizedItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IVirtualizedItemProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("098f858a-2e63-5985-ab87-f8ebdb1c5740")
                        IVirtualizedItemProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE Realize(void) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IVirtualizedItemProvider = _uuidof(IVirtualizedItemProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IWindowProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IWindowProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IWindowProvider";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Xaml {
                namespace Automation {
                    namespace Provider {
                        MIDL_INTERFACE("83f1df99-9ddf-575e-a651-2ee657fd16e0")
                        IWindowProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_IsModal(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_IsTopmost(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Maximizable(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Minimizable(
                                boolean* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_InteractionState(
                                ABI::Microsoft::UI::Xaml::Automation::WindowInteractionState* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_VisualState(
                                ABI::Microsoft::UI::Xaml::Automation::WindowVisualState* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE Close(void) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetVisualState(
                                ABI::Microsoft::UI::Xaml::Automation::WindowVisualState state
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE WaitForInputIdle(
                                INT32 milliseconds,
                                boolean* result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IWindowProvider = _uuidof(IWindowProvider);
                    } /* Provider */
                } /* Automation */
            } /* Xaml */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Automation.Provider.IRawElementProviderSimple
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Automation.Provider.IIRawElementProviderSimple ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Automation_Provider_IRawElementProviderSimple_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Automation_Provider_IRawElementProviderSimple_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Automation_Provider_IRawElementProviderSimple[] = L"Microsoft.UI.Xaml.Automation.Provider.IRawElementProviderSimple";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2 __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2 __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2 __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CAnnotationType __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CAnnotationType;

#ifndef ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty;

#endif // ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CDockPosition __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CDockPosition;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CExpandCollapseState __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CExpandCollapseState;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CPeers_CAutomationNavigationDirection __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CPeers_CAutomationNavigationDirection;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CRowOrColumnMajor __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CRowOrColumnMajor;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CScrollAmount __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CScrollAmount;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CSupportedTextSelection __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CSupportedTextSelection;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CSynchronizedInputType __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CSynchronizedInputType;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextUnit __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextUnit;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CToggleState __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CToggleState;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowInteractionState __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowInteractionState;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowVisualState __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowVisualState;

typedef enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CZoomUnit __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CZoomUnit;

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

typedef struct __x_ABI_CWindows_CUI_CColor __x_ABI_CWindows_CUI_CColor;

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IAnnotationProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IAnnotationProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IAnnotationProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AnnotationTypeId)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_AnnotationTypeName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Author)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_DateTime)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Target)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_get_AnnotationTypeId(This, value) \
    ((This)->lpVtbl->get_AnnotationTypeId(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_get_AnnotationTypeName(This, value) \
    ((This)->lpVtbl->get_AnnotationTypeName(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_get_Author(This, value) \
    ((This)->lpVtbl->get_Author(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_get_DateTime(This, value) \
    ((This)->lpVtbl->get_DateTime(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_get_Target(This, value) \
    ((This)->lpVtbl->get_Target(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIAnnotationProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ICustomNavigationProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ICustomNavigationProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ICustomNavigationProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* NavigateCustom)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CPeers_CAutomationNavigationDirection direction,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_NavigateCustom(This, direction, result) \
    ((This)->lpVtbl->NavigateCustom(This, direction, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CICustomNavigationProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IDockProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IDockProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IDockProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DockPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CDockPosition* value);
    HRESULT (STDMETHODCALLTYPE* SetDockPosition)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CDockPosition dockPosition);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_get_DockPosition(This, value) \
    ((This)->lpVtbl->get_DockPosition(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_SetDockPosition(This, dockPosition) \
    ((This)->lpVtbl->SetDockPosition(This, dockPosition))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDockProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IDragProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IDragProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IDragProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsGrabbed)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DropEffect)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_DropEffects)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        UINT32* valueLength,
        HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* GetGrabbedItems)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_get_IsGrabbed(This, value) \
    ((This)->lpVtbl->get_IsGrabbed(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_get_DropEffect(This, value) \
    ((This)->lpVtbl->get_DropEffect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_get_DropEffects(This, valueLength, value) \
    ((This)->lpVtbl->get_DropEffects(This, valueLength, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_GetGrabbedItems(This, resultLength, result) \
    ((This)->lpVtbl->GetGrabbedItems(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDragProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IDropTargetProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IDropTargetProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IDropTargetProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DropEffect)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_DropEffects)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider* This,
        UINT32* valueLength,
        HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_get_DropEffect(This, value) \
    ((This)->lpVtbl->get_DropEffect(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_get_DropEffects(This, valueLength, value) \
    ((This)->lpVtbl->get_DropEffects(This, valueLength, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIDropTargetProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IExpandCollapseProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IExpandCollapseProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IExpandCollapseProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ExpandCollapseState)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CExpandCollapseState* value);
    HRESULT (STDMETHODCALLTYPE* Collapse)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This);
    HRESULT (STDMETHODCALLTYPE* Expand)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_get_ExpandCollapseState(This, value) \
    ((This)->lpVtbl->get_ExpandCollapseState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_Collapse(This) \
    ((This)->lpVtbl->Collapse(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_Expand(This) \
    ((This)->lpVtbl->Expand(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIExpandCollapseProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IGridItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IGridItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IGridItemProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Column)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_ColumnSpan)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_ContainingGrid)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** value);
    HRESULT (STDMETHODCALLTYPE* get_Row)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_RowSpan)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_get_Column(This, value) \
    ((This)->lpVtbl->get_Column(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_get_ColumnSpan(This, value) \
    ((This)->lpVtbl->get_ColumnSpan(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_get_ContainingGrid(This, value) \
    ((This)->lpVtbl->get_ContainingGrid(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_get_Row(This, value) \
    ((This)->lpVtbl->get_Row(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_get_RowSpan(This, value) \
    ((This)->lpVtbl->get_RowSpan(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IGridProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IGridProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IGridProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ColumnCount)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_RowCount)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* GetItem)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider* This,
        INT32 row,
        INT32 column,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_get_ColumnCount(This, value) \
    ((This)->lpVtbl->get_ColumnCount(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_get_RowCount(This, value) \
    ((This)->lpVtbl->get_RowCount(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_GetItem(This, row, column, result) \
    ((This)->lpVtbl->GetItem(This, row, column, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIGridProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IIRawElementProviderSimple
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.UI.Xaml.Automation.Provider.IRawElementProviderSimple
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IIRawElementProviderSimple[] = L"Microsoft.UI.Xaml.Automation.Provider.IIRawElementProviderSimple";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimpleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimpleVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimpleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IInvokeProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IInvokeProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IInvokeProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_Invoke(This) \
    ((This)->lpVtbl->Invoke(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIInvokeProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IItemContainerProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IItemContainerProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IItemContainerProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* FindItemByProperty)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* startAfter,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CIAutomationProperty* automationProperty,
        IInspectable* value,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_FindItemByProperty(This, startAfter, automationProperty, value, result) \
    ((This)->lpVtbl->FindItemByProperty(This, startAfter, automationProperty, value, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIItemContainerProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IMultipleViewProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IMultipleViewProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IMultipleViewProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CurrentView)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* GetSupportedViews)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        UINT32* resultLength,
        INT32** result);
    HRESULT (STDMETHODCALLTYPE* GetViewName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        INT32 viewId,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* SetCurrentView)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider* This,
        INT32 viewId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_get_CurrentView(This, value) \
    ((This)->lpVtbl->get_CurrentView(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_GetSupportedViews(This, resultLength, result) \
    ((This)->lpVtbl->GetSupportedViews(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_GetViewName(This, viewId, result) \
    ((This)->lpVtbl->GetViewName(This, viewId, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_SetCurrentView(This, viewId) \
    ((This)->lpVtbl->SetCurrentView(This, viewId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIMultipleViewProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IObjectModelProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IObjectModelProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IObjectModelProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetUnderlyingObjectModel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider* This,
        IInspectable** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_GetUnderlyingObjectModel(This, result) \
    ((This)->lpVtbl->GetUnderlyingObjectModel(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIObjectModelProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IRangeValueProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IRangeValueProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IRangeValueProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsReadOnly)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_LargeChange)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_Maximum)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_Minimum)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_SmallChange)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* SetValue)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider* This,
        DOUBLE value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_get_IsReadOnly(This, value) \
    ((This)->lpVtbl->get_IsReadOnly(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_get_LargeChange(This, value) \
    ((This)->lpVtbl->get_LargeChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_get_Maximum(This, value) \
    ((This)->lpVtbl->get_Maximum(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_get_Minimum(This, value) \
    ((This)->lpVtbl->get_Minimum(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_get_SmallChange(This, value) \
    ((This)->lpVtbl->get_SmallChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_get_Value(This, value) \
    ((This)->lpVtbl->get_Value(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_SetValue(This, value) \
    ((This)->lpVtbl->SetValue(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIRangeValueProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IScrollItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IScrollItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IScrollItemProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ScrollIntoView)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_ScrollIntoView(This) \
    ((This)->lpVtbl->ScrollIntoView(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IScrollProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IScrollProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IScrollProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_HorizontallyScrollable)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_HorizontalScrollPercent)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_HorizontalViewSize)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_VerticallyScrollable)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_VerticalScrollPercent)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_VerticalViewSize)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* Scroll)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CScrollAmount horizontalAmount,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CScrollAmount verticalAmount);
    HRESULT (STDMETHODCALLTYPE* SetScrollPercent)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider* This,
        DOUBLE horizontalPercent,
        DOUBLE verticalPercent);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_get_HorizontallyScrollable(This, value) \
    ((This)->lpVtbl->get_HorizontallyScrollable(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_get_HorizontalScrollPercent(This, value) \
    ((This)->lpVtbl->get_HorizontalScrollPercent(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_get_HorizontalViewSize(This, value) \
    ((This)->lpVtbl->get_HorizontalViewSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_get_VerticallyScrollable(This, value) \
    ((This)->lpVtbl->get_VerticallyScrollable(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_get_VerticalScrollPercent(This, value) \
    ((This)->lpVtbl->get_VerticalScrollPercent(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_get_VerticalViewSize(This, value) \
    ((This)->lpVtbl->get_VerticalViewSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_Scroll(This, horizontalAmount, verticalAmount) \
    ((This)->lpVtbl->Scroll(This, horizontalAmount, verticalAmount))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_SetScrollPercent(This, horizontalPercent, verticalPercent) \
    ((This)->lpVtbl->SetScrollPercent(This, horizontalPercent, verticalPercent))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIScrollProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISelectionItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISelectionItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISelectionItemProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsSelected)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_SelectionContainer)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** value);
    HRESULT (STDMETHODCALLTYPE* AddToSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* RemoveFromSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* Select)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_get_IsSelected(This, value) \
    ((This)->lpVtbl->get_IsSelected(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_get_SelectionContainer(This, value) \
    ((This)->lpVtbl->get_SelectionContainer(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_AddToSelection(This) \
    ((This)->lpVtbl->AddToSelection(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_RemoveFromSelection(This) \
    ((This)->lpVtbl->RemoveFromSelection(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_Select(This) \
    ((This)->lpVtbl->Select(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISelectionProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISelectionProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISelectionProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CanSelectMultiple)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsSelectionRequired)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* GetSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_get_CanSelectMultiple(This, value) \
    ((This)->lpVtbl->get_CanSelectMultiple(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_get_IsSelectionRequired(This, value) \
    ((This)->lpVtbl->get_IsSelectionRequired(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_GetSelection(This, resultLength, result) \
    ((This)->lpVtbl->GetSelection(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISelectionProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISpreadsheetItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetItemProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Formula)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* GetAnnotationObjects)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);
    HRESULT (STDMETHODCALLTYPE* GetAnnotationTypes)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider* This,
        UINT32* resultLength,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CAnnotationType** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_get_Formula(This, value) \
    ((This)->lpVtbl->get_Formula(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_GetAnnotationObjects(This, resultLength, result) \
    ((This)->lpVtbl->GetAnnotationObjects(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_GetAnnotationTypes(This, resultLength, result) \
    ((This)->lpVtbl->GetAnnotationTypes(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISpreadsheetProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISpreadsheetProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetItemByName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider* This,
        HSTRING name,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_GetItemByName(This, name, result) \
    ((This)->lpVtbl->GetItemByName(This, name, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISpreadsheetProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IStylesProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IStylesProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IStylesProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedProperties)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FillColor)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_FillPatternColor)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        struct __x_ABI_CWindows_CUI_CColor* value);
    HRESULT (STDMETHODCALLTYPE* get_FillPatternStyle)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Shape)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_StyleId)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_StyleName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_ExtendedProperties(This, value) \
    ((This)->lpVtbl->get_ExtendedProperties(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_FillColor(This, value) \
    ((This)->lpVtbl->get_FillColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_FillPatternColor(This, value) \
    ((This)->lpVtbl->get_FillPatternColor(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_FillPatternStyle(This, value) \
    ((This)->lpVtbl->get_FillPatternStyle(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_Shape(This, value) \
    ((This)->lpVtbl->get_Shape(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_StyleId(This, value) \
    ((This)->lpVtbl->get_StyleId(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_get_StyleName(This, value) \
    ((This)->lpVtbl->get_StyleName(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIStylesProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ISynchronizedInputProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ISynchronizedInputProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ISynchronizedInputProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Cancel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This);
    HRESULT (STDMETHODCALLTYPE* StartListening)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CSynchronizedInputType inputType);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_Cancel(This) \
    ((This)->lpVtbl->Cancel(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_StartListening(This, inputType) \
    ((This)->lpVtbl->StartListening(This, inputType))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CISynchronizedInputProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITableItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITableItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITableItemProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetColumnHeaderItems)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);
    HRESULT (STDMETHODCALLTYPE* GetRowHeaderItems)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_GetColumnHeaderItems(This, resultLength, result) \
    ((This)->lpVtbl->GetColumnHeaderItems(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_GetRowHeaderItems(This, resultLength, result) \
    ((This)->lpVtbl->GetRowHeaderItems(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITableProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITableProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITableProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RowOrColumnMajor)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CRowOrColumnMajor* value);
    HRESULT (STDMETHODCALLTYPE* GetColumnHeaders)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);
    HRESULT (STDMETHODCALLTYPE* GetRowHeaders)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_get_RowOrColumnMajor(This, value) \
    ((This)->lpVtbl->get_RowOrColumnMajor(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_GetColumnHeaders(This, resultLength, result) \
    ((This)->lpVtbl->GetColumnHeaders(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_GetRowHeaders(This, resultLength, result) \
    ((This)->lpVtbl->GetRowHeaders(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITableProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextChildProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextChildProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextChildProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TextContainer)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** value);
    HRESULT (STDMETHODCALLTYPE* get_TextRange)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_get_TextContainer(This, value) \
    ((This)->lpVtbl->get_TextContainer(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_get_TextRange(This, value) \
    ((This)->lpVtbl->get_TextRange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextChildProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextEditProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITextProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextEditProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextEditProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetActiveComposition)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);
    HRESULT (STDMETHODCALLTYPE* GetConversionTarget)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_GetActiveComposition(This, result) \
    ((This)->lpVtbl->GetActiveComposition(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_GetConversionTarget(This, result) \
    ((This)->lpVtbl->GetConversionTarget(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextEditProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DocumentRange)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** value);
    HRESULT (STDMETHODCALLTYPE* get_SupportedTextSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CSupportedTextSelection* value);
    HRESULT (STDMETHODCALLTYPE* GetSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider*** result);
    HRESULT (STDMETHODCALLTYPE* GetVisibleRanges)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider*** result);
    HRESULT (STDMETHODCALLTYPE* RangeFromChild)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* childElement,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);
    HRESULT (STDMETHODCALLTYPE* RangeFromPoint)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider* This,
        struct __x_ABI_CWindows_CFoundation_CPoint screenLocation,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_get_DocumentRange(This, value) \
    ((This)->lpVtbl->get_DocumentRange(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_get_SupportedTextSelection(This, value) \
    ((This)->lpVtbl->get_SupportedTextSelection(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_GetSelection(This, resultLength, result) \
    ((This)->lpVtbl->GetSelection(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_GetVisibleRanges(This, resultLength, result) \
    ((This)->lpVtbl->GetVisibleRanges(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_RangeFromChild(This, childElement, result) \
    ((This)->lpVtbl->RangeFromChild(This, childElement, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_RangeFromPoint(This, screenLocation, result) \
    ((This)->lpVtbl->RangeFromPoint(This, screenLocation, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextProvider2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITextProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextProvider2[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextProvider2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* RangeFromAnnotation)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple* annotationElement,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);
    HRESULT (STDMETHODCALLTYPE* GetCaretRange)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2* This,
        boolean* isActive,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** returnValue);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_RangeFromAnnotation(This, annotationElement, result) \
    ((This)->lpVtbl->RangeFromAnnotation(This, annotationElement, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_GetCaretRange(This, isActive, returnValue) \
    ((This)->lpVtbl->GetCaretRange(This, isActive, returnValue))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextRangeProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Clone)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);
    HRESULT (STDMETHODCALLTYPE* Compare)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* textRangeProvider,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* CompareEndpoints)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint endpoint,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* textRangeProvider,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint targetEndpoint,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* ExpandToEnclosingUnit)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextUnit unit);
    HRESULT (STDMETHODCALLTYPE* FindAttribute)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        INT32 attributeId,
        IInspectable* value,
        boolean backward,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);
    HRESULT (STDMETHODCALLTYPE* FindText)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        HSTRING text,
        boolean backward,
        boolean ignoreCase,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider** result);
    HRESULT (STDMETHODCALLTYPE* GetAttributeValue)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        INT32 attributeId,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* GetBoundingRectangles)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        UINT32* returnValueLength,
        DOUBLE** returnValue);
    HRESULT (STDMETHODCALLTYPE* GetEnclosingElement)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple** result);
    HRESULT (STDMETHODCALLTYPE* GetText)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        INT32 maxLength,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* Move)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextUnit unit,
        INT32 count,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveEndpointByUnit)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint endpoint,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextUnit unit,
        INT32 count,
        INT32* result);
    HRESULT (STDMETHODCALLTYPE* MoveEndpointByRange)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint endpoint,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* textRangeProvider,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CText_CTextPatternRangeEndpoint targetEndpoint);
    HRESULT (STDMETHODCALLTYPE* Select)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This);
    HRESULT (STDMETHODCALLTYPE* AddToSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This);
    HRESULT (STDMETHODCALLTYPE* RemoveFromSelection)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This);
    HRESULT (STDMETHODCALLTYPE* ScrollIntoView)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        boolean alignToTop);
    HRESULT (STDMETHODCALLTYPE* GetChildren)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIIRawElementProviderSimple*** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_Clone(This, result) \
    ((This)->lpVtbl->Clone(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_Compare(This, textRangeProvider, result) \
    ((This)->lpVtbl->Compare(This, textRangeProvider, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_CompareEndpoints(This, endpoint, textRangeProvider, targetEndpoint, result) \
    ((This)->lpVtbl->CompareEndpoints(This, endpoint, textRangeProvider, targetEndpoint, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_ExpandToEnclosingUnit(This, unit) \
    ((This)->lpVtbl->ExpandToEnclosingUnit(This, unit))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FindAttribute(This, attributeId, value, backward, result) \
    ((This)->lpVtbl->FindAttribute(This, attributeId, value, backward, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_FindText(This, text, backward, ignoreCase, result) \
    ((This)->lpVtbl->FindText(This, text, backward, ignoreCase, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetAttributeValue(This, attributeId, result) \
    ((This)->lpVtbl->GetAttributeValue(This, attributeId, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetBoundingRectangles(This, returnValueLength, returnValue) \
    ((This)->lpVtbl->GetBoundingRectangles(This, returnValueLength, returnValue))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetEnclosingElement(This, result) \
    ((This)->lpVtbl->GetEnclosingElement(This, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetText(This, maxLength, result) \
    ((This)->lpVtbl->GetText(This, maxLength, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_Move(This, unit, count, result) \
    ((This)->lpVtbl->Move(This, unit, count, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_MoveEndpointByUnit(This, endpoint, unit, count, result) \
    ((This)->lpVtbl->MoveEndpointByUnit(This, endpoint, unit, count, result))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_MoveEndpointByRange(This, endpoint, textRangeProvider, targetEndpoint) \
    ((This)->lpVtbl->MoveEndpointByRange(This, endpoint, textRangeProvider, targetEndpoint))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_Select(This) \
    ((This)->lpVtbl->Select(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_AddToSelection(This) \
    ((This)->lpVtbl->AddToSelection(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_RemoveFromSelection(This) \
    ((This)->lpVtbl->RemoveFromSelection(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_ScrollIntoView(This, alignToTop) \
    ((This)->lpVtbl->ScrollIntoView(This, alignToTop))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_GetChildren(This, resultLength, result) \
    ((This)->lpVtbl->GetChildren(This, resultLength, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITextRangeProvider2[] = L"Microsoft.UI.Xaml.Automation.Provider.ITextRangeProvider2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ShowContextMenu)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_ShowContextMenu(This) \
    ((This)->lpVtbl->ShowContextMenu(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITextRangeProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IToggleProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IToggleProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IToggleProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ToggleState)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CToggleState* value);
    HRESULT (STDMETHODCALLTYPE* Toggle)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_get_ToggleState(This, value) \
    ((This)->lpVtbl->get_ToggleState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_Toggle(This) \
    ((This)->lpVtbl->Toggle(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIToggleProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITransformProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITransformProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.ITransformProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CanMove)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_CanResize)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_CanRotate)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* Move)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        DOUBLE x,
        DOUBLE y);
    HRESULT (STDMETHODCALLTYPE* Resize)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        DOUBLE width,
        DOUBLE height);
    HRESULT (STDMETHODCALLTYPE* Rotate)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider* This,
        DOUBLE degrees);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_get_CanMove(This, value) \
    ((This)->lpVtbl->get_CanMove(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_get_CanResize(This, value) \
    ((This)->lpVtbl->get_CanResize(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_get_CanRotate(This, value) \
    ((This)->lpVtbl->get_CanRotate(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_Move(This, x, y) \
    ((This)->lpVtbl->Move(This, x, y))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_Resize(This, width, height) \
    ((This)->lpVtbl->Resize(This, width, height))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_Rotate(This, degrees) \
    ((This)->lpVtbl->Rotate(This, degrees))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.ITransformProvider2
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Microsoft.UI.Xaml.Automation.Provider.ITransformProvider
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_ITransformProvider2[] = L"Microsoft.UI.Xaml.Automation.Provider.ITransformProvider2";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CanZoom)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ZoomLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_MaxZoom)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* get_MinZoom)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        DOUBLE* value);
    HRESULT (STDMETHODCALLTYPE* Zoom)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        DOUBLE zoom);
    HRESULT (STDMETHODCALLTYPE* ZoomByUnit)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CZoomUnit zoomUnit);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_get_CanZoom(This, value) \
    ((This)->lpVtbl->get_CanZoom(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_get_ZoomLevel(This, value) \
    ((This)->lpVtbl->get_ZoomLevel(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_get_MaxZoom(This, value) \
    ((This)->lpVtbl->get_MaxZoom(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_get_MinZoom(This, value) \
    ((This)->lpVtbl->get_MinZoom(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_Zoom(This, zoom) \
    ((This)->lpVtbl->Zoom(This, zoom))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_ZoomByUnit(This, zoomUnit) \
    ((This)->lpVtbl->ZoomByUnit(This, zoomUnit))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CITransformProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IValueProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IValueProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IValueProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsReadOnly)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* SetValue)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_get_IsReadOnly(This, value) \
    ((This)->lpVtbl->get_IsReadOnly(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_get_Value(This, value) \
    ((This)->lpVtbl->get_Value(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_SetValue(This, value) \
    ((This)->lpVtbl->SetValue(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIValueProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IVirtualizedItemProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IVirtualizedItemProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IVirtualizedItemProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Realize)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_Realize(This) \
    ((This)->lpVtbl->Realize(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIVirtualizedItemProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.UI.Xaml.Automation.Provider.IWindowProvider
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Xaml_Automation_Provider_IWindowProvider[] = L"Microsoft.UI.Xaml.Automation.Provider.IWindowProvider";
typedef struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsModal)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsTopmost)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Maximizable)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Minimizable)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_InteractionState)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowInteractionState* value);
    HRESULT (STDMETHODCALLTYPE* get_VisualState)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowVisualState* value);
    HRESULT (STDMETHODCALLTYPE* Close)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This);
    HRESULT (STDMETHODCALLTYPE* SetVisualState)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        enum __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CWindowVisualState state);
    HRESULT (STDMETHODCALLTYPE* WaitForInputIdle)(__x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider* This,
        INT32 milliseconds,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProviderVtbl;

interface __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_get_IsModal(This, value) \
    ((This)->lpVtbl->get_IsModal(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_get_IsTopmost(This, value) \
    ((This)->lpVtbl->get_IsTopmost(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_get_Maximizable(This, value) \
    ((This)->lpVtbl->get_Maximizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_get_Minimizable(This, value) \
    ((This)->lpVtbl->get_Minimizable(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_get_InteractionState(This, value) \
    ((This)->lpVtbl->get_InteractionState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_get_VisualState(This, value) \
    ((This)->lpVtbl->get_VisualState(This, value))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_Close(This) \
    ((This)->lpVtbl->Close(This))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_SetVisualState(This, state) \
    ((This)->lpVtbl->SetVisualState(This, state))

#define __x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_WaitForInputIdle(This, milliseconds, result) \
    ((This)->lpVtbl->WaitForInputIdle(This, milliseconds, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CXaml_CAutomation_CProvider_CIWindowProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.UI.Xaml.Automation.Provider.IRawElementProviderSimple
 *
 * Introduced to Microsoft.UI.Xaml.WinUIContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Xaml.Automation.Provider.IIRawElementProviderSimple ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_UI_Xaml_Automation_Provider_IRawElementProviderSimple_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Xaml_Automation_Provider_IRawElementProviderSimple_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Xaml_Automation_Provider_IRawElementProviderSimple[] = L"Microsoft.UI.Xaml.Automation.Provider.IRawElementProviderSimple";
#endif
#endif // MICROSOFT_UI_XAML_WINUICONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Examl2Eautomation2Eprovider_p_h__

#endif // __microsoft2Eui2Examl2Eautomation2Eprovider_h__
