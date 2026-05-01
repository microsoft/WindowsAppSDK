
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
#ifndef __microsoft2Ewindows2Ewidgets2Eproviders_h__
#define __microsoft2Ewindows2Ewidgets2Eproviders_h__
#ifndef __microsoft2Ewindows2Ewidgets2Eproviders_p_h__
#define __microsoft2Ewindows2Ewidgets2Eproviders_p_h__


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
#if !defined(MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION 0xc0000
#endif // defined(MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION)

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
#include "Microsoft.Windows.Widgets.h"
#include "Windows.Storage.Streams.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetActionInvokedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetActionInvokedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetAnalyticsInfoReportedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetAnalyticsInfoReportedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetContext;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetContextChangedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetContextChangedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetCustomizationRequestedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetCustomizationRequestedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetErrorInfoReportedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetErrorInfoReportedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetInfo;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo ABI::Microsoft::Windows::Widgets::Providers::IWidgetInfo

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetInfo2;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2 ABI::Microsoft::Windows::Widgets::Providers::IWidgetInfo2

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetInfo3;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3 ABI::Microsoft::Windows::Widgets::Providers::IWidgetInfo3

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetManager;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager ABI::Microsoft::Windows::Widgets::Providers::IWidgetManager

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetManager2;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2 ABI::Microsoft::Windows::Widgets::Providers::IWidgetManager2

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetManagerStatics;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics ABI::Microsoft::Windows::Widgets::Providers::IWidgetManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetMessageReceivedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetMessageReceivedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetProvider;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider ABI::Microsoft::Windows::Widgets::Providers::IWidgetProvider

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetProvider2;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2 ABI::Microsoft::Windows::Widgets::Providers::IWidgetProvider2

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetProviderAnalytics;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics ABI::Microsoft::Windows::Widgets::Providers::IWidgetProviderAnalytics

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetProviderErrors;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors ABI::Microsoft::Windows::Widgets::Providers::IWidgetProviderErrors

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetProviderMessage;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage ABI::Microsoft::Windows::Widgets::Providers::IWidgetProviderMessage

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetResourceProvider;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceProvider

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetResourceRequest;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceRequest

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetResourceRequestedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceRequestedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetResourceResponse;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceResponse

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetResourceResponseFactory;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceResponseFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetUpdateRequestOptions;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetUpdateRequestOptions2;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2 ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptions2

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetUpdateRequestOptions3;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3 ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptions3

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetUpdateRequestOptionsFactory;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptionsFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    interface IWidgetUpdateRequestOptionsStatics;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptionsStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_FWD_DEFINED__

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



#ifndef DEF___FIReference_1_boolean_USE
#define DEF___FIReference_1_boolean_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("3c00fd60-2950-5939-a21a-2d12c5a01b8a"))
IReference<bool> : IReference_impl<ABI::Windows::Foundation::Internal::AggregateType<bool, boolean>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Boolean>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<bool> __FIReference_1_boolean_t;
#define __FIReference_1_boolean ABI::Windows::Foundation::__FIReference_1_boolean_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_boolean_USE */



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
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                typedef enum WidgetSize : int WidgetSize;
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

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

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            namespace Streams {
                interface IRandomAccessStreamReference;
            } /* Streams */
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference ABI::Windows::Storage::Streams::IRandomAccessStreamReference

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetActionInvokedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetAnalyticsInfoReportedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetContext;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetContextChangedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetCustomizationRequestedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetErrorInfoReportedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetInfo;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetManager;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetMessageReceivedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetResourceRequest;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetResourceRequestedArgs;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetResourceResponse;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    class WidgetUpdateRequestOptions;
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetActionInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetActionInvokedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetActionInvokedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetActionInvokedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("c593cc57-04b9-52ca-88ad-46fea21ea340")
                    IWidgetActionInvokedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Verb(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Data(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CustomState(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetActionInvokedArgs = _uuidof(IWidgetActionInvokedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetAnalyticsInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetAnalyticsInfoReportedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("1d9e5fb5-2bce-5350-87b1-d63199526639")
                    IWidgetAnalyticsInfoReportedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_AnalyticsJson(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetAnalyticsInfoReportedArgs = _uuidof(IWidgetAnalyticsInfoReportedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetContext
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetContext
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetContext[] = L"Microsoft.Windows.Widgets.Providers.IWidgetContext";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("903c518b-40bc-5bc6-88f7-af9d81c0cdc1")
                    IWidgetContext : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Id(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DefinitionId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Size(
                            ABI::Microsoft::Windows::Widgets::WidgetSize* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IsActive(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetContext = _uuidof(IWidgetContext);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetContextChangedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetContextChangedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetContextChangedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetContextChangedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("2c226d54-2252-576b-a197-370b28d25c2f")
                    IWidgetContextChangedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetContextChangedArgs = _uuidof(IWidgetContextChangedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetCustomizationRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetCustomizationRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetCustomizationRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetCustomizationRequestedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("41dea311-dd9b-5b8b-b493-3a30552116b8")
                    IWidgetCustomizationRequestedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CustomState(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetCustomizationRequestedArgs = _uuidof(IWidgetCustomizationRequestedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetErrorInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetErrorInfoReportedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("30efa627-b21f-55d5-b91a-b23b4aa13645")
                    IWidgetErrorInfoReportedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorJson(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetErrorInfoReportedArgs = _uuidof(IWidgetErrorInfoReportedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetInfo[] = L"Microsoft.Windows.Widgets.Providers.IWidgetInfo";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("cea11f42-a020-5db5-89e2-b7dece4ae5cb")
                    IWidgetInfo : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Template(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Data(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CustomState(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_LastUpdateTime(
                            ABI::Windows::Foundation::DateTime* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetInfo = _uuidof(IWidgetInfo);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetInfo2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 9.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetInfo2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetInfo2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("081b0a6f-d784-5408-bb29-252fef2926d4")
                    IWidgetInfo2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsPlaceholderContent(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetInfo2 = _uuidof(IWidgetInfo2);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetInfo3
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetInfo3[] = L"Microsoft.Windows.Widgets.Providers.IWidgetInfo3";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("965538cd-289d-54ab-916e-9315ebf97ea4")
                    IWidgetInfo3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Rank(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetInfo3 = _uuidof(IWidgetInfo3);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetManager[] = L"Microsoft.Windows.Widgets.Providers.IWidgetManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("71cb10c0-671e-48e3-b995-207940397123")
                    IWidgetManager : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE UpdateWidget(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptions* widgetUpdateRequestOptions
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetWidgetIds(
                            UINT32* resultLength,
                            HSTRING** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetWidgetInfo(
                            HSTRING widgetId,
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetInfo** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetWidgetInfos(
                            UINT32* resultLength,
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetInfo*** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DeleteWidget(
                            HSTRING widgetId
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetManager = _uuidof(IWidgetManager);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetManager2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetManager2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetManager2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("55c65a27-8845-406c-9ee1-1e79f0556bef")
                    IWidgetManager2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE SendMessageToContent(
                            HSTRING widgetId,
                            HSTRING message
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetManager2 = _uuidof(IWidgetManager2);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetManagerStatics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetManager
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetManagerStatics[] = L"Microsoft.Windows.Widgets.Providers.IWidgetManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("7f233b06-28e5-5e2b-8c04-a4fa747c28c7")
                    IWidgetManagerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetDefault(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetManager** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetManagerStatics = _uuidof(IWidgetManagerStatics);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetMessageReceivedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetMessageReceivedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("2261cb2b-c741-5f96-9adb-fb3a7667bcb6")
                    IWidgetMessageReceivedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Message(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetMessageReceivedArgs = _uuidof(IWidgetMessageReceivedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProvider[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProvider";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("5c5774cc-72a0-452d-b9ed-075c0dd25eed")
                    IWidgetProvider : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateWidget(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext* widgetContext
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DeleteWidget(
                            HSTRING widgetId,
                            HSTRING customState
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE OnActionInvoked(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetActionInvokedArgs* actionInvokedArgs
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE OnWidgetContextChanged(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContextChangedArgs* contextChangedArgs
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Activate(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext* widgetContext
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Deactivate(
                            HSTRING widgetId
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetProvider = _uuidof(IWidgetProvider);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProvider2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProvider2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProvider2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("38c3a963-dd93-479d-9276-04bf84ee1816")
                    IWidgetProvider2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE OnCustomizationRequested(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetCustomizationRequestedArgs* customizationRequestedArgs
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetProvider2 = _uuidof(IWidgetProvider2);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProviderAnalytics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProviderAnalytics[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProviderAnalytics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("661985a5-d187-482d-9eef-6fda05d21845")
                    IWidgetProviderAnalytics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE OnAnalyticsInfoReported(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetAnalyticsInfoReportedArgs* args
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetProviderAnalytics = _uuidof(IWidgetProviderAnalytics);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProviderErrors
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProviderErrors[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProviderErrors";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("90c1b5f0-0d3a-4ac6-abb7-c97b367b8fcc")
                    IWidgetProviderErrors : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE OnErrorInfoReported(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetErrorInfoReportedArgs* args
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetProviderErrors = _uuidof(IWidgetProviderErrors);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProviderMessage
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProviderMessage[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProviderMessage";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("ea4dc186-9e24-4b35-a5ef-a9f5df72d6ac")
                    IWidgetProviderMessage : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE OnMessageReceived(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetMessageReceivedArgs* args
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetProviderMessage = _uuidof(IWidgetProviderMessage);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceProvider[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceProvider";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("dcf328c0-012c-40f5-bb28-3a1c714d027d")
                    IWidgetResourceProvider : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE OnResourceRequested(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceRequestedArgs* args
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetResourceProvider = _uuidof(IWidgetResourceProvider);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceRequest
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceRequest[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceRequest";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("113d249f-82d9-57cb-8cea-9a5291f2fe22")
                    IWidgetResourceRequest : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Uri(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Method(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Method(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Content(
                            ABI::Windows::Storage::Streams::IRandomAccessStreamReference** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Content(
                            ABI::Windows::Storage::Streams::IRandomAccessStreamReference* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Headers(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetResourceRequest = _uuidof(IWidgetResourceRequest);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceRequestedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("2bb30f4d-0166-58e3-aaf6-31b2ae970bcd")
                    IWidgetResourceRequestedArgs : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetContext(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetContext** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Request(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceRequest** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Response(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceResponse** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Response(
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceResponse* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetDeferral(
                            ABI::Windows::Foundation::IDeferral** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetResourceRequestedArgs = _uuidof(IWidgetResourceRequestedArgs);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceResponse[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceResponse";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("03a2d32c-2e9e-54a3-b084-1479d5060f80")
                    IWidgetResourceResponse : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Content(
                            ABI::Windows::Storage::Streams::IRandomAccessStreamReference** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Headers(
                            __FIMap_2_HSTRING_HSTRING** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ReasonPhrase(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_StatusCode(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetResourceResponse = _uuidof(IWidgetResourceResponse);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceResponseFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceResponseFactory[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceResponseFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("08881ef1-a78a-5804-b070-9153a8657f85")
                    IWidgetResourceResponseFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            ABI::Windows::Storage::Streams::IRandomAccessStreamReference* content,
                            HSTRING reasonPhrase,
                            INT32 statusCode,
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetResourceResponse** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetResourceResponseFactory = _uuidof(IWidgetResourceResponseFactory);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptions[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("b09ca8f7-7424-5687-baaf-7dd6fa639672")
                    IWidgetUpdateRequestOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_WidgetId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Template(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Template(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Data(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Data(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CustomState(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CustomState(
                            HSTRING value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetUpdateRequestOptions = _uuidof(IWidgetUpdateRequestOptions);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 9.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptions2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("77c4efc4-38f3-57a5-aba1-f83f257b899e")
                    IWidgetUpdateRequestOptions2 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsPlaceholderContent(
                            __FIReference_1_boolean** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_IsPlaceholderContent(
                            __FIReference_1_boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetUpdateRequestOptions2 = _uuidof(IWidgetUpdateRequestOptions2);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions3
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptions3[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions3";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("a78e2a8b-a26c-596a-ade3-db8f4c72fe02")
                    IWidgetUpdateRequestOptions3 : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Rank(
                            __FIReference_1_int** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Rank(
                            __FIReference_1_int* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetUpdateRequestOptions3 = _uuidof(IWidgetUpdateRequestOptions3);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptionsFactory[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("e0e00af8-1d10-57a8-9419-3f568e854daa")
                    IWidgetUpdateRequestOptionsFactory : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                            HSTRING widgetId,
                            ABI::Microsoft::Windows::Widgets::Providers::IWidgetUpdateRequestOptions** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetUpdateRequestOptionsFactory = _uuidof(IWidgetUpdateRequestOptionsFactory);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsStatics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptionsStatics[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Providers {
                    MIDL_INTERFACE("4645b5e3-d332-5d11-82f0-3607e5df6018")
                    IWidgetUpdateRequestOptionsStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_UnsetValue(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IWidgetUpdateRequestOptionsStatics = _uuidof(IWidgetUpdateRequestOptionsStatics);
                } /* Providers */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetActionInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetActionInvokedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetActionInvokedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetActionInvokedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetActionInvokedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetActionInvokedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetAnalyticsInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetAnalyticsInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetAnalyticsInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetAnalyticsInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetContext
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetContext ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetContext[] = L"Microsoft.Windows.Widgets.Providers.WidgetContext";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetContextChangedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetContextChangedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContextChangedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContextChangedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetContextChangedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetContextChangedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetCustomizationRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetCustomizationRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetCustomizationRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetCustomizationRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetCustomizationRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetCustomizationRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetErrorInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetErrorInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetErrorInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetErrorInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetInfo ** Default Interface **
 *    Microsoft.Windows.Widgets.Providers.IWidgetInfo2
 *    Microsoft.Windows.Widgets.Providers.IWidgetInfo3
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetInfo[] = L"Microsoft.Windows.Widgets.Providers.WidgetInfo";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Widgets.Providers.IWidgetManagerStatics interface starting with version 1.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetManager ** Default Interface **
 *    Microsoft.Windows.Widgets.Providers.IWidgetManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetManager[] = L"Microsoft.Windows.Widgets.Providers.WidgetManager";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetMessageReceivedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetMessageReceivedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetMessageReceivedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetMessageReceivedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetResourceRequest ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequest_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequest_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetResourceRequest[] = L"Microsoft.Windows.Widgets.Providers.WidgetResourceRequest";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetResourceRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetResourceRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Providers.IWidgetResourceResponseFactory interface starting with version 6.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetResourceResponse ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetResourceResponse[] = L"Microsoft.Windows.Widgets.Providers.WidgetResourceResponse";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsFactory interface starting with version 1.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsStatics interface starting with version 1.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions ** Default Interface **
 *    Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions2
 *    Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetUpdateRequestOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetUpdateRequestOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetUpdateRequestOptions[] = L"Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2 __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3 __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2 __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2 __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2 __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3 __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_FWD_DEFINED__

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

#if !defined(____FIReference_1_boolean_INTERFACE_DEFINED__)
#define ____FIReference_1_boolean_INTERFACE_DEFINED__

typedef interface __FIReference_1_boolean __FIReference_1_boolean;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_boolean;

typedef struct __FIReference_1_booleanVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_boolean* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_boolean* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_boolean* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_boolean* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_boolean* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_boolean* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_boolean* This,
        boolean* result);

    END_INTERFACE
} __FIReference_1_booleanVtbl;

interface __FIReference_1_boolean
{
    CONST_VTBL struct __FIReference_1_booleanVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_boolean_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_boolean_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_boolean_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_boolean_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_boolean_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_boolean_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_boolean_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_boolean_INTERFACE_DEFINED__

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

typedef enum __x_ABI_CMicrosoft_CWindows_CWidgets_CWidgetSize __x_ABI_CMicrosoft_CWindows_CWidgets_CWidgetSize;

typedef struct __x_ABI_CWindows_CFoundation_CDateTime __x_ABI_CWindows_CFoundation_CDateTime;

#ifndef ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIDeferral __x_ABI_CWindows_CFoundation_CIDeferral;

#endif // ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIPropertyValue __x_ABI_CWindows_CFoundation_CIPropertyValue;

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetActionInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetActionInvokedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetActionInvokedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetActionInvokedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_Verb)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Data)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_CustomState)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_get_Verb(This, value) \
    ((This)->lpVtbl->get_Verb(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_get_Data(This, value) \
    ((This)->lpVtbl->get_Data(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_get_CustomState(This, value) \
    ((This)->lpVtbl->get_CustomState(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetAnalyticsInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetAnalyticsInfoReportedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_AnalyticsJson)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_get_AnalyticsJson(This, value) \
    ((This)->lpVtbl->get_AnalyticsJson(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetContext
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetContext
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetContext[] = L"Microsoft.Windows.Widgets.Providers.IWidgetContext";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_DefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        enum __x_ABI_CMicrosoft_CWindows_CWidgets_CWidgetSize* value);
    HRESULT (STDMETHODCALLTYPE* get_IsActive)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_get_DefinitionId(This, value) \
    ((This)->lpVtbl->get_DefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_get_Size(This, value) \
    ((This)->lpVtbl->get_Size(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_get_IsActive(This, value) \
    ((This)->lpVtbl->get_IsActive(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetContextChangedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetContextChangedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetContextChangedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetContextChangedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetCustomizationRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetCustomizationRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetCustomizationRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetCustomizationRequestedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_CustomState)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_get_CustomState(This, value) \
    ((This)->lpVtbl->get_CustomState(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetErrorInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetErrorInfoReportedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorJson)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_get_ErrorJson(This, value) \
    ((This)->lpVtbl->get_ErrorJson(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetInfo[] = L"Microsoft.Windows.Widgets.Providers.IWidgetInfo";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfoVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_Template)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Data)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_CustomState)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_LastUpdateTime)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo* This,
        struct __x_ABI_CWindows_CFoundation_CDateTime* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfoVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfoVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_get_Template(This, value) \
    ((This)->lpVtbl->get_Template(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_get_Data(This, value) \
    ((This)->lpVtbl->get_Data(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_get_CustomState(This, value) \
    ((This)->lpVtbl->get_CustomState(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_get_LastUpdateTime(This, value) \
    ((This)->lpVtbl->get_LastUpdateTime(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetInfo2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 9.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetInfo2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetInfo2";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsPlaceholderContent)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_get_IsPlaceholderContent(This, value) \
    ((This)->lpVtbl->get_IsPlaceholderContent(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetInfo3
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetInfo3[] = L"Microsoft.Windows.Widgets.Providers.IWidgetInfo3";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Rank)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_get_Rank(This, value) \
    ((This)->lpVtbl->get_Rank(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetManager[] = L"Microsoft.Windows.Widgets.Providers.IWidgetManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* UpdateWidget)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* widgetUpdateRequestOptions);
    HRESULT (STDMETHODCALLTYPE* GetWidgetIds)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        UINT32* resultLength,
        HSTRING** result);
    HRESULT (STDMETHODCALLTYPE* GetWidgetInfo)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        HSTRING widgetId,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo** result);
    HRESULT (STDMETHODCALLTYPE* GetWidgetInfos)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetInfo*** result);
    HRESULT (STDMETHODCALLTYPE* DeleteWidget)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager* This,
        HSTRING widgetId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_UpdateWidget(This, widgetUpdateRequestOptions) \
    ((This)->lpVtbl->UpdateWidget(This, widgetUpdateRequestOptions))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_GetWidgetIds(This, resultLength, result) \
    ((This)->lpVtbl->GetWidgetIds(This, resultLength, result))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_GetWidgetInfo(This, widgetId, result) \
    ((This)->lpVtbl->GetWidgetInfo(This, widgetId, result))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_GetWidgetInfos(This, resultLength, result) \
    ((This)->lpVtbl->GetWidgetInfos(This, resultLength, result))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_DeleteWidget(This, widgetId) \
    ((This)->lpVtbl->DeleteWidget(This, widgetId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetManager2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetManager2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetManager2";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SendMessageToContent)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2* This,
        HSTRING widgetId,
        HSTRING message);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_SendMessageToContent(This, widgetId, message) \
    ((This)->lpVtbl->SendMessageToContent(This, widgetId, message))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetManagerStatics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetManager
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetManagerStatics[] = L"Microsoft.Windows.Widgets.Providers.IWidgetManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDefault)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_GetDefault(This, result) \
    ((This)->lpVtbl->GetDefault(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetMessageReceivedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetMessageReceivedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_Message)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_get_Message(This, value) \
    ((This)->lpVtbl->get_Message(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProvider[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProvider";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateWidget)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* widgetContext);
    HRESULT (STDMETHODCALLTYPE* DeleteWidget)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        HSTRING widgetId,
        HSTRING customState);
    HRESULT (STDMETHODCALLTYPE* OnActionInvoked)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetActionInvokedArgs* actionInvokedArgs);
    HRESULT (STDMETHODCALLTYPE* OnWidgetContextChanged)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContextChangedArgs* contextChangedArgs);
    HRESULT (STDMETHODCALLTYPE* Activate)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext* widgetContext);
    HRESULT (STDMETHODCALLTYPE* Deactivate)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider* This,
        HSTRING widgetId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_CreateWidget(This, widgetContext) \
    ((This)->lpVtbl->CreateWidget(This, widgetContext))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_DeleteWidget(This, widgetId, customState) \
    ((This)->lpVtbl->DeleteWidget(This, widgetId, customState))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_OnActionInvoked(This, actionInvokedArgs) \
    ((This)->lpVtbl->OnActionInvoked(This, actionInvokedArgs))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_OnWidgetContextChanged(This, contextChangedArgs) \
    ((This)->lpVtbl->OnWidgetContextChanged(This, contextChangedArgs))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_Activate(This, widgetContext) \
    ((This)->lpVtbl->Activate(This, widgetContext))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_Deactivate(This, widgetId) \
    ((This)->lpVtbl->Deactivate(This, widgetId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProvider2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProvider2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProvider2";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnCustomizationRequested)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetCustomizationRequestedArgs* customizationRequestedArgs);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_OnCustomizationRequested(This, customizationRequestedArgs) \
    ((This)->lpVtbl->OnCustomizationRequested(This, customizationRequestedArgs))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProvider2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProviderAnalytics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProviderAnalytics[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProviderAnalytics";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalyticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnAnalyticsInfoReported)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetAnalyticsInfoReportedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalyticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalyticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_OnAnalyticsInfoReported(This, args) \
    ((This)->lpVtbl->OnAnalyticsInfoReported(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderAnalytics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProviderErrors
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProviderErrors[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProviderErrors";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrorsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnErrorInfoReported)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetErrorInfoReportedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrorsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrorsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_OnErrorInfoReported(This, args) \
    ((This)->lpVtbl->OnErrorInfoReported(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderErrors_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetProviderMessage
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetProviderMessage[] = L"Microsoft.Windows.Widgets.Providers.IWidgetProviderMessage";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessageVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnMessageReceived)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetMessageReceivedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessageVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessageVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_OnMessageReceived(This, args) \
    ((This)->lpVtbl->OnMessageReceived(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetProviderMessage_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceProvider[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceProvider";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnResourceRequested)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProviderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_OnResourceRequested(This, args) \
    ((This)->lpVtbl->OnResourceRequested(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceRequest
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceRequest[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceRequest";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Uri)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Method)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Method)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference** value);
    HRESULT (STDMETHODCALLTYPE* put_Content)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference* value);
    HRESULT (STDMETHODCALLTYPE* get_Headers)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest* This,
        __FIMap_2_HSTRING_HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_get_Uri(This, value) \
    ((This)->lpVtbl->get_Uri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_get_Method(This, value) \
    ((This)->lpVtbl->get_Method(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_put_Method(This, value) \
    ((This)->lpVtbl->put_Method(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_put_Content(This, value) \
    ((This)->lpVtbl->put_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_get_Headers(This, value) \
    ((This)->lpVtbl->get_Headers(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceRequestedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetContext)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetContext** value);
    HRESULT (STDMETHODCALLTYPE* get_Request)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequest** value);
    HRESULT (STDMETHODCALLTYPE* get_Response)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse** value);
    HRESULT (STDMETHODCALLTYPE* put_Response)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* value);
    HRESULT (STDMETHODCALLTYPE* GetDeferral)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs* This,
        __x_ABI_CWindows_CFoundation_CIDeferral** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_get_WidgetContext(This, value) \
    ((This)->lpVtbl->get_WidgetContext(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_get_Request(This, value) \
    ((This)->lpVtbl->get_Request(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_get_Response(This, value) \
    ((This)->lpVtbl->get_Response(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_put_Response(This, value) \
    ((This)->lpVtbl->put_Response(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_GetDeferral(This, result) \
    ((This)->lpVtbl->GetDeferral(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceResponse[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceResponse";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference** value);
    HRESULT (STDMETHODCALLTYPE* get_Headers)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        __FIMap_2_HSTRING_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* get_ReasonPhrase)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_StatusCode)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_get_Headers(This, value) \
    ((This)->lpVtbl->get_Headers(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_get_ReasonPhrase(This, value) \
    ((This)->lpVtbl->get_ReasonPhrase(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_get_StatusCode(This, value) \
    ((This)->lpVtbl->get_StatusCode(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetResourceResponseFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetResourceResponseFactory[] = L"Microsoft.Windows.Widgets.Providers.IWidgetResourceResponseFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference* content,
        HSTRING reasonPhrase,
        INT32 statusCode,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponse** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_CreateInstance(This, content, reasonPhrase, statusCode, value) \
    ((This)->lpVtbl->CreateInstance(This, content, reasonPhrase, statusCode, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetResourceResponseFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptions[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_WidgetId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Template)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Template)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Data)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Data)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_CustomState)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_CustomState)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_get_WidgetId(This, value) \
    ((This)->lpVtbl->get_WidgetId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_get_Template(This, value) \
    ((This)->lpVtbl->get_Template(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_put_Template(This, value) \
    ((This)->lpVtbl->put_Template(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_get_Data(This, value) \
    ((This)->lpVtbl->get_Data(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_put_Data(This, value) \
    ((This)->lpVtbl->put_Data(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_get_CustomState(This, value) \
    ((This)->lpVtbl->get_CustomState(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_put_CustomState(This, value) \
    ((This)->lpVtbl->put_CustomState(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 9.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptions2[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions2";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsPlaceholderContent)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This,
        __FIReference_1_boolean** value);
    HRESULT (STDMETHODCALLTYPE* put_IsPlaceholderContent)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2* This,
        __FIReference_1_boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_get_IsPlaceholderContent(This, value) \
    ((This)->lpVtbl->get_IsPlaceholderContent(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_put_IsPlaceholderContent(This, value) \
    ((This)->lpVtbl->put_IsPlaceholderContent(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x90000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions3
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 11.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptions3[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions3";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Rank)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This,
        __FIReference_1_int** value);
    HRESULT (STDMETHODCALLTYPE* put_Rank)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3* This,
        __FIReference_1_int* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_get_Rank(This, value) \
    ((This)->lpVtbl->get_Rank(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_put_Rank(This, value) \
    ((This)->lpVtbl->put_Rank(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xb0000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptionsFactory[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory* This,
        HSTRING widgetId,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptions** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_CreateInstance(This, widgetId, value) \
    ((This)->lpVtbl->CreateInstance(This, widgetId, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsStatics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Providers_IWidgetUpdateRequestOptionsStatics[] = L"Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_UnsetValue)(__x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_get_UnsetValue(This, value) \
    ((This)->lpVtbl->get_UnsetValue(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CProviders_CIWidgetUpdateRequestOptionsStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetActionInvokedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetActionInvokedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetActionInvokedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetActionInvokedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetActionInvokedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetActionInvokedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetAnalyticsInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetAnalyticsInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetAnalyticsInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetAnalyticsInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetContext
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetContext ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContext_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContext_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetContext[] = L"Microsoft.Windows.Widgets.Providers.WidgetContext";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetContextChangedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetContextChangedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContextChangedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetContextChangedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetContextChangedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetContextChangedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetCustomizationRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetCustomizationRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetCustomizationRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetCustomizationRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetCustomizationRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetCustomizationRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 2.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetErrorInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetErrorInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetErrorInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetErrorInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x20000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetInfo ** Default Interface **
 *    Microsoft.Windows.Widgets.Providers.IWidgetInfo2
 *    Microsoft.Windows.Widgets.Providers.IWidgetInfo3
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetInfo[] = L"Microsoft.Windows.Widgets.Providers.WidgetInfo";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Widgets.Providers.IWidgetManagerStatics interface starting with version 1.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetManager ** Default Interface **
 *    Microsoft.Windows.Widgets.Providers.IWidgetManager2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetManager[] = L"Microsoft.Windows.Widgets.Providers.WidgetManager";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetMessageReceivedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetMessageReceivedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetMessageReceivedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetMessageReceivedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetResourceRequest ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequest_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequest_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetResourceRequest[] = L"Microsoft.Windows.Widgets.Providers.WidgetResourceRequest";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetResourceRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Providers.WidgetResourceRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 6.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Providers.IWidgetResourceResponseFactory interface starting with version 6.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetResourceResponse ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetResourceResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetResourceResponse[] = L"Microsoft.Windows.Widgets.Providers.WidgetResourceResponse";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x60000

/*
 *
 * Class Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsFactory interface starting with version 1.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptionsStatics interface starting with version 1.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions ** Default Interface **
 *    Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions2
 *    Microsoft.Windows.Widgets.Providers.IWidgetUpdateRequestOptions3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetUpdateRequestOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Providers_WidgetUpdateRequestOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Providers_WidgetUpdateRequestOptions[] = L"Microsoft.Windows.Widgets.Providers.WidgetUpdateRequestOptions";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Ewidgets2Eproviders_p_h__

#endif // __microsoft2Ewindows2Ewidgets2Eproviders_h__
