
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
#ifndef __microsoft2Ewindows2Ewidgets2Efeeds2Eproviders_h__
#define __microsoft2Ewindows2Ewidgets2Efeeds2Eproviders_h__
#ifndef __microsoft2Ewindows2Ewidgets2Efeeds2Eproviders_p_h__
#define __microsoft2Ewindows2Ewidgets2Efeeds2Eproviders_p_h__


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
#include "Microsoft.Windows.Widgets.Notifications.h"
#include "Windows.Storage.Streams.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface ICustomQueryParametersRequestedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::ICustomQueryParametersRequestedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface ICustomQueryParametersUpdateOptions;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions ABI::Microsoft::Windows::Widgets::Feeds::Providers::ICustomQueryParametersUpdateOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface ICustomQueryParametersUpdateOptionsFactory;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory ABI::Microsoft::Windows::Widgets::Feeds::Providers::ICustomQueryParametersUpdateOptionsFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedAnalyticsInfoReportedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedAnalyticsInfoReportedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedAnnouncementInvokedTarget;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedAnnouncementInvokedTarget

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedDisabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedDisabledArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedEnabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedEnabledArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedErrorInfoReportedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedErrorInfoReportedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedManager;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedManager

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedManager2;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2 ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedManager2

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedManager3;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3 ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedManager3

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedManagerStatics;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedManagerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedMessageReceivedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedMessageReceivedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProvider;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProvider

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProviderAnalytics;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderAnalytics

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProviderDisabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderDisabledArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProviderEnabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderEnabledArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProviderErrors;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderErrors

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProviderInfo;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderInfo

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedProviderMessage;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderMessage

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedResourceProvider;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceProvider

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedResourceRequest;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceRequest

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedResourceRequestedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceRequestedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedResourceResponse;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceResponse

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        interface IFeedResourceResponseFactory;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceResponseFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_FWD_DEFINED__

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
            namespace Widgets {
                namespace Notifications {
                    class FeedAnnouncement;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    interface IFeedAnnouncement;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncement

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    class FeedAnnouncementInvokedArgs;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Notifications {
                    interface IFeedAnnouncementInvokedArgs;
                } /* Notifications */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncementInvokedArgs

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace Foundation {
            namespace Collections {
                class StringMap;
            } /* Collections */
        } /* Foundation */
    } /* Windows */
} /* ABI */


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
                namespace Feeds {
                    namespace Providers {
                        class CustomQueryParametersRequestedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class CustomQueryParametersUpdateOptions;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedAnalyticsInfoReportedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedDisabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedEnabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedErrorInfoReportedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedManager;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedMessageReceivedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedProviderDisabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedProviderEnabledArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedProviderInfo;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedResourceRequest;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedResourceRequestedArgs;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        class FeedResourceResponse;
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_ICustomQueryParametersRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersRequestedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("dc2b0cd8-7936-5346-9371-b21484c7d859")
                        ICustomQueryParametersRequestedArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ICustomQueryParametersRequestedArgs = _uuidof(ICustomQueryParametersRequestedArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_ICustomQueryParametersUpdateOptions[] = L"Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("753f1177-4909-568a-b070-98a3139205ec")
                        ICustomQueryParametersUpdateOptions : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_CustomQueryParameters(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ICustomQueryParametersUpdateOptions = _uuidof(ICustomQueryParametersUpdateOptions);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptionsFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_ICustomQueryParametersUpdateOptionsFactory[] = L"Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptionsFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("34e318cd-3884-53c0-911c-225f32228fae")
                        ICustomQueryParametersUpdateOptionsFactory : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                                HSTRING feedProviderDefinitionId,
                                HSTRING customQueryParameters,
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::ICustomQueryParametersUpdateOptions** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_ICustomQueryParametersUpdateOptionsFactory = _uuidof(ICustomQueryParametersUpdateOptionsFactory);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedAnalyticsInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnalyticsInfoReportedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("3c0e3d65-ed47-5b8a-b650-39a7edf18942")
                        IFeedAnalyticsInfoReportedArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_AnalyticsJson(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedAnalyticsInfoReportedArgs = _uuidof(IFeedAnalyticsInfoReportedArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnnouncementInvokedTarget
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedAnnouncementInvokedTarget[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnnouncementInvokedTarget";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("5d44ae2a-072c-4df9-9fe5-34d5d2e9ff63")
                        IFeedAnnouncementInvokedTarget : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE OnAnnouncementInvoked(
                                ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncementInvokedArgs* args
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedAnnouncementInvokedTarget = _uuidof(IFeedAnnouncementInvokedTarget);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedDisabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedDisabledArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("95300612-aca7-53c0-9cf6-d803689132c1")
                        IFeedDisabledArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedDisabledArgs = _uuidof(IFeedDisabledArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedEnabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedEnabledArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("eff4b2d7-7347-5969-a77d-cac433f0fdae")
                        IFeedEnabledArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedEnabledArgs = _uuidof(IFeedEnabledArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedErrorInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedErrorInfoReportedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("62de018c-161e-52d0-9dbe-aec106fb6600")
                        IFeedErrorInfoReportedArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ErrorJson(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedErrorInfoReportedArgs = _uuidof(IFeedErrorInfoReportedArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManager[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("87df6a84-15aa-45cb-8911-5cafab57f723")
                        IFeedManager : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE GetEnabledFeedProviders(
                                UINT32* resultLength,
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderInfo*** result
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE SetCustomQueryParameters(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::ICustomQueryParametersUpdateOptions* options
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedManager = _uuidof(IFeedManager);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManager2[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager2";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("5838300a-a069-455d-9943-ba078ada00d8")
                        IFeedManager2 : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE SendMessageToContent(
                                HSTRING feedProviderDefinitionId,
                                HSTRING feedDefinitionId,
                                HSTRING message
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE TryShowAnnouncement(
                                HSTRING feedProviderDefinitionId,
                                HSTRING feedDefinitionId,
                                ABI::Microsoft::Windows::Widgets::Notifications::IFeedAnnouncement* announcement
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedManager2 = _uuidof(IFeedManager2);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager3
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 12.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xc0000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManager3[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager3";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("a6af915b-0cdc-46f1-a4d6-10d8c644984a")
                        IFeedManager3 : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE TryRemoveAnnouncementById(
                                HSTRING feedProviderDefinitionId,
                                HSTRING feedDefinitionId,
                                HSTRING announcementId
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedManager3 = _uuidof(IFeedManager3);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xc0000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManagerStatics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedManager
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManagerStatics[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManagerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("4baf5174-77d6-5e2a-94ea-4f14ccdb1f2c")
                        IFeedManagerStatics : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE GetDefault(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedManager** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedManagerStatics = _uuidof(IFeedManagerStatics);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedMessageReceivedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedMessageReceivedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("4ed6ecf9-4c74-5a0b-ae04-bef6dd776f8a")
                        IFeedMessageReceivedArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Message(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedMessageReceivedArgs = _uuidof(IFeedMessageReceivedArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProvider[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProvider";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("7293a12b-0329-458d-ac25-5332be478fde")
                        IFeedProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE OnFeedProviderEnabled(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderEnabledArgs* args
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE OnFeedProviderDisabled(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedProviderDisabledArgs* args
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE OnFeedEnabled(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedEnabledArgs* args
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE OnFeedDisabled(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedDisabledArgs* args
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE OnCustomQueryParametersRequested(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::ICustomQueryParametersRequestedArgs* args
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProvider = _uuidof(IFeedProvider);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderAnalytics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderAnalytics[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderAnalytics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("f6885791-3085-4bd7-9cb1-4f1354c3a687")
                        IFeedProviderAnalytics : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE OnAnalyticsInfoReported(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedAnalyticsInfoReportedArgs* args
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProviderAnalytics = _uuidof(IFeedProviderAnalytics);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderDisabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderDisabledArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("19b65aec-e01d-5e8c-ab5f-324212e7cd30")
                        IFeedProviderDisabledArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProviderDisabledArgs = _uuidof(IFeedProviderDisabledArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderEnabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderEnabledArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("821fc9af-0de6-5a9b-9ae6-e179117b40e4")
                        IFeedProviderEnabledArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProviderEnabledArgs = _uuidof(IFeedProviderEnabledArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderErrors
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderErrors[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderErrors";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("6611e00a-d86c-49a3-9381-b7da67ee62dc")
                        IFeedProviderErrors : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE OnErrorInfoReported(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedErrorInfoReportedArgs* args
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProviderErrors = _uuidof(IFeedProviderErrors);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderInfo[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderInfo";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("73c37049-3c03-5896-8532-f9dfdaeb723f")
                        IFeedProviderInfo : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_EnabledFeedDefinitionIds(
                                UINT32* valueLength,
                                HSTRING** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProviderInfo = _uuidof(IFeedProviderInfo);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderMessage
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderMessage[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderMessage";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("60c2442a-4c9d-4880-ba26-caca9e567dd4")
                        IFeedProviderMessage : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE OnMessageReceived(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedMessageReceivedArgs* args
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedProviderMessage = _uuidof(IFeedProviderMessage);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceProvider[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceProvider";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("e1b6266d-88a0-416c-9440-e341cb047cd3")
                        IFeedResourceProvider : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE OnResourceRequested(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceRequestedArgs* args
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedResourceProvider = _uuidof(IFeedResourceProvider);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequest
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceRequest[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequest";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("e62e479c-e21f-5863-b4c9-df1be2227981")
                        IFeedResourceRequest : public IInspectable
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
                            virtual HRESULT STDMETHODCALLTYPE put_Headers(
                                __FIMap_2_HSTRING_HSTRING* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedResourceRequest = _uuidof(IFeedResourceRequest);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequestedArgs";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("360eb709-0bc9-52c1-9c70-3c7d413173d8")
                        IFeedResourceRequestedArgs : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_FeedProviderDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_FeedDefinitionId(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Request(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceRequest** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Response(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceResponse** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_Response(
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceResponse* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE GetDeferral(
                                ABI::Windows::Foundation::IDeferral** result
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedResourceRequestedArgs = _uuidof(IFeedResourceRequestedArgs);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceResponse[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponse";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("f831824e-7aef-53fc-b7ee-32ade675a3ad")
                        IFeedResourceResponse : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE get_Content(
                                ABI::Windows::Storage::Streams::IRandomAccessStreamReference** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_Headers(
                                __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING** value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE put_Headers(
                                __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_ReasonPhrase(
                                HSTRING* value
                                ) = 0;
                            virtual HRESULT STDMETHODCALLTYPE get_StatusCode(
                                INT32* value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedResourceResponse = _uuidof(IFeedResourceResponse);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponseFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceResponseFactory[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponseFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Widgets {
                namespace Feeds {
                    namespace Providers {
                        MIDL_INTERFACE("db01690d-2547-5d7a-b625-d1629f443c5c")
                        IFeedResourceResponseFactory : public IInspectable
                        {
                        public:
                            virtual HRESULT STDMETHODCALLTYPE CreateInstance(
                                ABI::Windows::Storage::Streams::IRandomAccessStreamReference* content,
                                HSTRING reasonPhrase,
                                INT32 statusCode,
                                ABI::Microsoft::Windows::Widgets::Feeds::Providers::IFeedResourceResponse** value
                                ) = 0;
                        };

                        MIDL_CONST_ID IID& IID_IFeedResourceResponseFactory = _uuidof(IFeedResourceResponseFactory);
                    } /* Providers */
                } /* Feeds */
            } /* Widgets */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptionsFactory interface starting with version 4.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersUpdateOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersUpdateOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersUpdateOptions[] = L"Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnalyticsInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedAnalyticsInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedAnalyticsInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedAnalyticsInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedDisabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedDisabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedDisabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedDisabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedEnabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedEnabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedEnabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedEnabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedErrorInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedErrorInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedErrorInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedErrorInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Widgets.Feeds.Providers.IFeedManagerStatics interface starting with version 4.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager ** Default Interface **
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager2
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedManager[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedManager";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedMessageReceivedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedMessageReceivedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedMessageReceivedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedMessageReceivedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderDisabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderDisabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderDisabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderDisabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderEnabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderEnabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderEnabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderEnabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderInfo ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderInfo[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderInfo";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequest ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequest_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequest_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequest[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequest";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponseFactory interface starting with version 5.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponse ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceResponse[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2 __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3 __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_FWD_DEFINED__

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

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs;

#endif // ____x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs_FWD_DEFINED__

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

#ifndef ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIDeferral __x_ABI_CWindows_CFoundation_CIDeferral;

#endif // ____x_ABI_CWindows_CFoundation_CIDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_FWD_DEFINED__

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_ICustomQueryParametersRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersRequestedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_ICustomQueryParametersUpdateOptions[] = L"Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_CustomQueryParameters)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_get_CustomQueryParameters(This, value) \
    ((This)->lpVtbl->get_CustomQueryParameters(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptionsFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_ICustomQueryParametersUpdateOptionsFactory[] = L"Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptionsFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory* This,
        HSTRING feedProviderDefinitionId,
        HSTRING customQueryParameters,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_CreateInstance(This, feedProviderDefinitionId, customQueryParameters, value) \
    ((This)->lpVtbl->CreateInstance(This, feedProviderDefinitionId, customQueryParameters, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptionsFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedAnalyticsInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnalyticsInfoReportedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_AnalyticsJson)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_get_AnalyticsJson(This, value) \
    ((This)->lpVtbl->get_AnalyticsJson(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnnouncementInvokedTarget
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedAnnouncementInvokedTarget[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnnouncementInvokedTarget";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTargetVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnAnnouncementInvoked)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncementInvokedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTargetVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTargetVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_OnAnnouncementInvoked(This, args) \
    ((This)->lpVtbl->OnAnnouncementInvoked(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnnouncementInvokedTarget_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedDisabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedDisabledArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedEnabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedEnabledArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedErrorInfoReportedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedErrorInfoReportedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorJson)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_get_ErrorJson(This, value) \
    ((This)->lpVtbl->get_ErrorJson(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManager[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetEnabledFeedProviders)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo*** result);
    HRESULT (STDMETHODCALLTYPE* SetCustomQueryParameters)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersUpdateOptions* options);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_GetEnabledFeedProviders(This, resultLength, result) \
    ((This)->lpVtbl->GetEnabledFeedProviders(This, resultLength, result))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_SetCustomQueryParameters(This, options) \
    ((This)->lpVtbl->SetCustomQueryParameters(This, options))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager2
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManager2[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager2";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* SendMessageToContent)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This,
        HSTRING feedProviderDefinitionId,
        HSTRING feedDefinitionId,
        HSTRING message);
    HRESULT (STDMETHODCALLTYPE* TryShowAnnouncement)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2* This,
        HSTRING feedProviderDefinitionId,
        HSTRING feedDefinitionId,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CNotifications_CIFeedAnnouncement* announcement);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_SendMessageToContent(This, feedProviderDefinitionId, feedDefinitionId, message) \
    ((This)->lpVtbl->SendMessageToContent(This, feedProviderDefinitionId, feedDefinitionId, message))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_TryShowAnnouncement(This, feedProviderDefinitionId, feedDefinitionId, announcement) \
    ((This)->lpVtbl->TryShowAnnouncement(This, feedProviderDefinitionId, feedDefinitionId, announcement))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager3
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 12.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xc0000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManager3[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager3";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* TryRemoveAnnouncementById)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3* This,
        HSTRING feedProviderDefinitionId,
        HSTRING feedDefinitionId,
        HSTRING announcementId);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3Vtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_TryRemoveAnnouncementById(This, feedProviderDefinitionId, feedDefinitionId, announcementId) \
    ((This)->lpVtbl->TryRemoveAnnouncementById(This, feedProviderDefinitionId, feedDefinitionId, announcementId))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager3_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0xc0000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedManagerStatics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedManager
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedManagerStatics[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedManagerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetDefault)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManager** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_GetDefault(This, result) \
    ((This)->lpVtbl->GetDefault(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedManagerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedMessageReceivedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedMessageReceivedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Message)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_get_Message(This, value) \
    ((This)->lpVtbl->get_Message(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProvider[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProvider";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnFeedProviderEnabled)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* args);
    HRESULT (STDMETHODCALLTYPE* OnFeedProviderDisabled)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* args);
    HRESULT (STDMETHODCALLTYPE* OnFeedEnabled)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedEnabledArgs* args);
    HRESULT (STDMETHODCALLTYPE* OnFeedDisabled)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedDisabledArgs* args);
    HRESULT (STDMETHODCALLTYPE* OnCustomQueryParametersRequested)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CICustomQueryParametersRequestedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_OnFeedProviderEnabled(This, args) \
    ((This)->lpVtbl->OnFeedProviderEnabled(This, args))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_OnFeedProviderDisabled(This, args) \
    ((This)->lpVtbl->OnFeedProviderDisabled(This, args))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_OnFeedEnabled(This, args) \
    ((This)->lpVtbl->OnFeedEnabled(This, args))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_OnFeedDisabled(This, args) \
    ((This)->lpVtbl->OnFeedDisabled(This, args))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_OnCustomQueryParametersRequested(This, args) \
    ((This)->lpVtbl->OnCustomQueryParametersRequested(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderAnalytics
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderAnalytics[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderAnalytics";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalyticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnAnalyticsInfoReported)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedAnalyticsInfoReportedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalyticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalyticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_OnAnalyticsInfoReported(This, args) \
    ((This)->lpVtbl->OnAnalyticsInfoReported(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderAnalytics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderDisabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderDisabledArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderDisabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderEnabledArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderEnabledArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderEnabledArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderErrors
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderErrors[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderErrors";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrorsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnErrorInfoReported)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedErrorInfoReportedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrorsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrorsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_OnErrorInfoReported(This, args) \
    ((This)->lpVtbl->OnErrorInfoReported(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderErrors_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderInfo
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderInfo[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderInfo";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfoVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_EnabledFeedDefinitionIds)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo* This,
        UINT32* valueLength,
        HSTRING** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfoVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfoVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_get_EnabledFeedDefinitionIds(This, valueLength, value) \
    ((This)->lpVtbl->get_EnabledFeedDefinitionIds(This, valueLength, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderInfo_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderMessage
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedProviderMessage[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderMessage";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessageVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnMessageReceived)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedMessageReceivedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessageVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessageVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_OnMessageReceived(This, args) \
    ((This)->lpVtbl->OnMessageReceived(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedProviderMessage_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceProvider
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceProvider[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceProvider";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProviderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* OnResourceRequested)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* args);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProviderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProviderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_OnResourceRequested(This, args) \
    ((This)->lpVtbl->OnResourceRequested(This, args))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceProvider_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequest
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceRequest[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequest";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Uri)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Method)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Method)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference** value);
    HRESULT (STDMETHODCALLTYPE* put_Content)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference* value);
    HRESULT (STDMETHODCALLTYPE* get_Headers)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        __FIMap_2_HSTRING_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* put_Headers)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest* This,
        __FIMap_2_HSTRING_HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_get_Uri(This, value) \
    ((This)->lpVtbl->get_Uri(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_get_Method(This, value) \
    ((This)->lpVtbl->get_Method(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_put_Method(This, value) \
    ((This)->lpVtbl->put_Method(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_put_Content(This, value) \
    ((This)->lpVtbl->put_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_get_Headers(This, value) \
    ((This)->lpVtbl->get_Headers(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_put_Headers(This, value) \
    ((This)->lpVtbl->put_Headers(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequestedArgs
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequestedArgs";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_FeedProviderDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_FeedDefinitionId)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Request)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequest** value);
    HRESULT (STDMETHODCALLTYPE* get_Response)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse** value);
    HRESULT (STDMETHODCALLTYPE* put_Response)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* value);
    HRESULT (STDMETHODCALLTYPE* GetDeferral)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs* This,
        __x_ABI_CWindows_CFoundation_CIDeferral** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_get_FeedProviderDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedProviderDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_get_FeedDefinitionId(This, value) \
    ((This)->lpVtbl->get_FeedDefinitionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_get_Request(This, value) \
    ((This)->lpVtbl->get_Request(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_get_Response(This, value) \
    ((This)->lpVtbl->get_Response(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_put_Response(This, value) \
    ((This)->lpVtbl->put_Response(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_GetDeferral(This, result) \
    ((This)->lpVtbl->GetDeferral(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceRequestedArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceResponse[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponse";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Content)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference** value);
    HRESULT (STDMETHODCALLTYPE* get_Headers)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING** value);
    HRESULT (STDMETHODCALLTYPE* put_Headers)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        __FIIterable_1___FIKeyValuePair_2_HSTRING_HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ReasonPhrase)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_StatusCode)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_get_Content(This, value) \
    ((This)->lpVtbl->get_Content(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_get_Headers(This, value) \
    ((This)->lpVtbl->get_Headers(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_put_Headers(This, value) \
    ((This)->lpVtbl->put_Headers(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_get_ReasonPhrase(This, value) \
    ((This)->lpVtbl->get_ReasonPhrase(This, value))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_get_StatusCode(This, value) \
    ((This)->lpVtbl->get_StatusCode(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Interface Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponseFactory
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#if !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Widgets_Feeds_Providers_IFeedResourceResponseFactory[] = L"Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponseFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateInstance)(__x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory* This,
        __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference* content,
        HSTRING reasonPhrase,
        INT32 statusCode,
        __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponse** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_CreateInstance(This, content, reasonPhrase, statusCode, value) \
    ((This)->lpVtbl->CreateInstance(This, content, reasonPhrase, statusCode, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CWidgets_CFeeds_CProviders_CIFeedResourceResponseFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptionsFactory interface starting with version 4.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.ICustomQueryParametersUpdateOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersUpdateOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersUpdateOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_CustomQueryParametersUpdateOptions[] = L"Microsoft.Windows.Widgets.Feeds.Providers.CustomQueryParametersUpdateOptions";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedAnalyticsInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedAnalyticsInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedAnalyticsInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedAnalyticsInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedAnalyticsInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedAnalyticsInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedDisabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedDisabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedDisabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedDisabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedEnabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedEnabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedEnabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedEnabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedErrorInfoReportedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedErrorInfoReportedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedErrorInfoReportedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedErrorInfoReportedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedErrorInfoReportedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedErrorInfoReportedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedManager
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Widgets.Feeds.Providers.IFeedManagerStatics interface starting with version 4.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager ** Default Interface **
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager2
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedManager3
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedManager_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedManager_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedManager[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedManager";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedMessageReceivedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedMessageReceivedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedMessageReceivedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedMessageReceivedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedMessageReceivedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedMessageReceivedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderDisabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderDisabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderDisabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderDisabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderDisabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderDisabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderEnabledArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderEnabledArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderEnabledArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderEnabledArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderEnabledArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderEnabledArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderInfo
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 4.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedProviderInfo ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderInfo_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderInfo_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedProviderInfo[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedProviderInfo";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x40000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequest
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequest ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequest_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequest_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequest[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequest";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequestedArgs
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceRequestedArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequestedArgs_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequestedArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceRequestedArgs[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceRequestedArgs";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

/*
 *
 * Class Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse
 *
 * Introduced to Microsoft.Windows.Widgets.WidgetContract in version 5.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via the Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponseFactory interface starting with version 5.0 of the Microsoft.Windows.Widgets.WidgetContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Widgets.Feeds.Providers.IFeedResourceResponse ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000
#ifndef RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceResponse_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceResponse_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Widgets_Feeds_Providers_FeedResourceResponse[] = L"Microsoft.Windows.Widgets.Feeds.Providers.FeedResourceResponse";
#endif
#endif // MICROSOFT_WINDOWS_WIDGETS_WIDGETCONTRACT_VERSION >= 0x50000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Ewidgets2Efeeds2Eproviders_p_h__

#endif // __microsoft2Ewindows2Ewidgets2Efeeds2Eproviders_h__
