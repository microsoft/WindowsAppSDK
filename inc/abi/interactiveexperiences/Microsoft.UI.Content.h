
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
#ifndef __microsoft2Eui2Econtent_h__
#define __microsoft2Eui2Econtent_h__
#ifndef __microsoft2Eui2Econtent_p_h__
#define __microsoft2Eui2Econtent_p_h__


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
#include "Microsoft.UI.Composition.h"
#include "Microsoft.UI.Dispatching.h"
#include "Windows.Foundation.Numerics.h"
#include "Windows.Graphics.h"
#include "Windows.UI.Composition.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IChildSiteLink;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink ABI::Microsoft::UI::Content::IChildSiteLink

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IChildSiteLinkStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics ABI::Microsoft::UI::Content::IChildSiteLinkStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentCoordinateConverter;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter ABI::Microsoft::UI::Content::IContentCoordinateConverter

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentCoordinateConverterFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory ABI::Microsoft::UI::Content::IContentCoordinateConverterFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentCoordinateConverterStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics ABI::Microsoft::UI::Content::IContentCoordinateConverterStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentDeferral;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral ABI::Microsoft::UI::Content::IContentDeferral

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentEnvironmentSettingChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs ABI::Microsoft::UI::Content::IContentEnvironmentSettingChangedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentEnvironmentStateChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs ABI::Microsoft::UI::Content::IContentEnvironmentStateChangedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentEnvironmentStateChangedEventArgs2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2 ABI::Microsoft::UI::Content::IContentEnvironmentStateChangedEventArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIsland;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland ABI::Microsoft::UI::Content::IContentIsland

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIsland2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2 ABI::Microsoft::UI::Content::IContentIsland2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandAutomation;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation ABI::Microsoft::UI::Content::IContentIslandAutomation

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandAutomationProviderRequestedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs ABI::Microsoft::UI::Content::IContentIslandAutomationProviderRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandEnvironment;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment ABI::Microsoft::UI::Content::IContentIslandEnvironment

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandEnvironment2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2 ABI::Microsoft::UI::Content::IContentIslandEnvironment2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandEnvironmentFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory ABI::Microsoft::UI::Content::IContentIslandEnvironmentFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory ABI::Microsoft::UI::Content::IContentIslandFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandStateChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs ABI::Microsoft::UI::Content::IContentIslandStateChangedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandStateChangedEventArgs2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2 ABI::Microsoft::UI::Content::IContentIslandStateChangedEventArgs2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics ABI::Microsoft::UI::Content::IContentIslandStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentIslandStatics2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2 ABI::Microsoft::UI::Content::IContentIslandStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSite;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite ABI::Microsoft::UI::Content::IContentSite

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSite2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2 ABI::Microsoft::UI::Content::IContentSite2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteAutomation;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation ABI::Microsoft::UI::Content::IContentSiteAutomation

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteAutomationProviderRequestedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs ABI::Microsoft::UI::Content::IContentSiteAutomationProviderRequestedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge ABI::Microsoft::UI::Content::IContentSiteBridge

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteEnvironment;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment ABI::Microsoft::UI::Content::IContentSiteEnvironment

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteEnvironment2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2 ABI::Microsoft::UI::Content::IContentSiteEnvironment2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteEnvironmentFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory ABI::Microsoft::UI::Content::IContentSiteEnvironmentFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteEnvironmentView;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView ABI::Microsoft::UI::Content::IContentSiteEnvironmentView

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteEnvironmentView2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2 ABI::Microsoft::UI::Content::IContentSiteEnvironmentView2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteEnvironmentViewFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory ABI::Microsoft::UI::Content::IContentSiteEnvironmentViewFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory ABI::Microsoft::UI::Content::IContentSiteFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteInput;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput ABI::Microsoft::UI::Content::IContentSiteInput

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteLink;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink ABI::Microsoft::UI::Content::IContentSiteLink

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteRequestedStateChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs ABI::Microsoft::UI::Content::IContentSiteRequestedStateChangedEventArgs

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteView;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView ABI::Microsoft::UI::Content::IContentSiteView

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteView2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2 ABI::Microsoft::UI::Content::IContentSiteView2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteViewAutomation;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation ABI::Microsoft::UI::Content::IContentSiteViewAutomation

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IContentSiteViewFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory ABI::Microsoft::UI::Content::IContentSiteViewFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopAttachedSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge ABI::Microsoft::UI::Content::IDesktopAttachedSiteBridge

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopAttachedSiteBridgeStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics ABI::Microsoft::UI::Content::IDesktopAttachedSiteBridgeStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_FWD_DEFINED__

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

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopChildSiteBridgeStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics ABI::Microsoft::UI::Content::IDesktopChildSiteBridgeStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopChildSiteBridgeStatics2;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2 ABI::Microsoft::UI::Content::IDesktopChildSiteBridgeStatics2

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopPopupSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge ABI::Microsoft::UI::Content::IDesktopPopupSiteBridge

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopPopupSiteBridgeStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics ABI::Microsoft::UI::Content::IDesktopPopupSiteBridgeStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge ABI::Microsoft::UI::Content::IDesktopSiteBridge

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopSiteBridgeFactory;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory ABI::Microsoft::UI::Content::IDesktopSiteBridgeFactory

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                interface IDesktopSiteBridgeStatics;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics ABI::Microsoft::UI::Content::IDesktopSiteBridgeStatics

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ChildSiteLink;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#ifndef DEF___FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_USE
#define DEF___FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("95e02266-15a8-59ae-8a00-06d24fa34e40"))
IIterator<ABI::Microsoft::UI::Content::ChildSiteLink*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ChildSiteLink*, ABI::Microsoft::UI::Content::IChildSiteLink*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Content.ChildSiteLink>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Content::ChildSiteLink*> __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_t;
#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#ifndef DEF___FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_USE
#define DEF___FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("20eed339-c583-5027-91cc-a3eee3919004"))
IIterable<ABI::Microsoft::UI::Content::ChildSiteLink*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ChildSiteLink*, ABI::Microsoft::UI::Content::IChildSiteLink*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Content.ChildSiteLink>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Content::ChildSiteLink*> __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_t;
#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class DesktopPopupSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#ifndef DEF___FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_USE
#define DEF___FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("cc9ed456-5402-5d3e-86b9-d3f25708e44d"))
IIterator<ABI::Microsoft::UI::Content::DesktopPopupSiteBridge*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::DesktopPopupSiteBridge*, ABI::Microsoft::UI::Content::IDesktopPopupSiteBridge*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.UI.Content.DesktopPopupSiteBridge>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::UI::Content::DesktopPopupSiteBridge*> __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_t;
#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#ifndef DEF___FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_USE
#define DEF___FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("63e787bb-0f05-5896-84ce-a63268343fd8"))
IIterable<ABI::Microsoft::UI::Content::DesktopPopupSiteBridge*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::DesktopPopupSiteBridge*, ABI::Microsoft::UI::Content::IDesktopPopupSiteBridge*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.UI.Content.DesktopPopupSiteBridge>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::UI::Content::DesktopPopupSiteBridge*> __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_t;
#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                typedef enum ContentLayoutDirection : int ContentLayoutDirection;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_USE
#define DEF___FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("76e53eed-3539-540b-8d51-4206bca63f5f"))
IReference<enum ABI::Microsoft::UI::Content::ContentLayoutDirection> : IReference_impl<enum ABI::Microsoft::UI::Content::ContentLayoutDirection>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Microsoft.UI.Content.ContentLayoutDirection>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<enum ABI::Microsoft::UI::Content::ContentLayoutDirection> __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_t;
#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection ABI::Windows::Foundation::__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentIsland;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentIslandAutomationProviderRequestedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("3b44f287-f0ef-5d10-ab5f-1b324f45f7da"))
ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIsland*, ABI::Microsoft::UI::Content::ContentIslandAutomationProviderRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentIsland*, ABI::Microsoft::UI::Content::IContentIsland*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentIslandAutomationProviderRequestedEventArgs*, ABI::Microsoft::UI::Content::IContentIslandAutomationProviderRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Content.ContentIsland, Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIsland*, ABI::Microsoft::UI::Content::ContentIslandAutomationProviderRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentIslandStateChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ceb771a4-bf66-529d-883a-602d592f390c"))
ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIsland*, ABI::Microsoft::UI::Content::ContentIslandStateChangedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentIsland*, ABI::Microsoft::UI::Content::IContentIsland*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentIslandStateChangedEventArgs*, ABI::Microsoft::UI::Content::IContentIslandStateChangedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Content.ContentIsland, Microsoft.UI.Content.ContentIslandStateChangedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIsland*, ABI::Microsoft::UI::Content::ContentIslandStateChangedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentIslandEnvironment;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentEnvironmentSettingChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("1ad20c79-1495-5501-ac8a-a38845e8f218"))
ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIslandEnvironment*, ABI::Microsoft::UI::Content::ContentEnvironmentSettingChangedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentIslandEnvironment*, ABI::Microsoft::UI::Content::IContentIslandEnvironment*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentEnvironmentSettingChangedEventArgs*, ABI::Microsoft::UI::Content::IContentEnvironmentSettingChangedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Content.ContentIslandEnvironment, Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIslandEnvironment*, ABI::Microsoft::UI::Content::ContentEnvironmentSettingChangedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentEnvironmentStateChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("c7742341-cfd5-5ef6-ab2a-d38c65b780b5"))
ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIslandEnvironment*, ABI::Microsoft::UI::Content::ContentEnvironmentStateChangedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentIslandEnvironment*, ABI::Microsoft::UI::Content::IContentIslandEnvironment*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentEnvironmentStateChangedEventArgs*, ABI::Microsoft::UI::Content::IContentEnvironmentStateChangedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Content.ContentIslandEnvironment, Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Content::ContentIslandEnvironment*, ABI::Microsoft::UI::Content::ContentEnvironmentStateChangedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentSite;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentSiteRequestedStateChangedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("b34e5337-73e6-5227-8921-6321eea32a9b"))
ITypedEventHandler<ABI::Microsoft::UI::Content::ContentSite*, ABI::Microsoft::UI::Content::ContentSiteRequestedStateChangedEventArgs*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentSite*, ABI::Microsoft::UI::Content::IContentSite*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentSiteRequestedStateChangedEventArgs*, ABI::Microsoft::UI::Content::IContentSiteRequestedStateChangedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Content.ContentSite, Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Content::ContentSite*, ABI::Microsoft::UI::Content::ContentSiteRequestedStateChangedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentSiteAutomationProviderRequestedEventArgs;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#ifndef DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_USE
#define DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("ee3f9952-86b4-5871-b8f2-b5826fe3d123"))
ITypedEventHandler<ABI::Microsoft::UI::Content::IContentSiteAutomation*, ABI::Microsoft::UI::Content::ContentSiteAutomationProviderRequestedEventArgs*> : ITypedEventHandler_impl<ABI::Microsoft::UI::Content::IContentSiteAutomation*, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::UI::Content::ContentSiteAutomationProviderRequestedEventArgs*, ABI::Microsoft::UI::Content::IContentSiteAutomationProviderRequestedEventArgs*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.UI.Content.IContentSiteAutomation, Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::UI::Content::IContentSiteAutomation*, ABI::Microsoft::UI::Content::ContentSiteAutomationProviderRequestedEventArgs*> __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_t;
#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_USE */

#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class Compositor;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositor;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositor ABI::Microsoft::UI::Composition::ICompositor

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                class ContainerVisual;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface IContainerVisual;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual ABI::Microsoft::UI::Composition::IContainerVisual

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Composition {
                interface ICompositionSupportsSystemBackdrop;
            } /* Composition */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop ABI::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__

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

#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace UI {
            interface IClosableNotifier;
        } /* UI */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CUI_CIClosableNotifier ABI::Microsoft::UI::IClosableNotifier

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            typedef struct WindowId WindowId;
        } /* UI */
    } /* Microsoft */
} /* ABI */

#ifndef ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Foundation {
            namespace Collections {
                interface IPropertySet;
            } /* Collections */
        } /* Foundation */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet ABI::Windows::Foundation::Collections::IPropertySet

#endif // ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__

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
        namespace Foundation {
            namespace Numerics {
                typedef struct Matrix4x4 Matrix4x4;
            } /* Numerics */
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Foundation {
            namespace Numerics {
                typedef struct Vector2 Vector2;
            } /* Numerics */
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
    namespace Windows {
        namespace UI {
            namespace Composition {
                class Compositor;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CICompositor_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                interface ICompositor;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CUI_CComposition_CICompositor ABI::Windows::UI::Composition::ICompositor

#endif // ____x_ABI_CWindows_CUI_CComposition_CICompositor_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                class ContainerVisual;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                interface IContainerVisual;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CUI_CComposition_CIContainerVisual ABI::Windows::UI::Composition::IContainerVisual

#endif // ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_FWD_DEFINED__

namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                class Visual;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CIVisual_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace UI {
            namespace Composition {
                interface IVisual;
            } /* Composition */
        } /* UI */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CUI_CComposition_CIVisual ABI::Windows::UI::Composition::IVisual

#endif // ____x_ABI_CWindows_CUI_CComposition_CIVisual_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                typedef enum ContentAutomationOptions : int ContentAutomationOptions;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                typedef enum ContentCoordinateRoundingMode : int ContentCoordinateRoundingMode;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                typedef enum ContentSizePolicy : int ContentSizePolicy;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentCoordinateConverter;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentDeferral;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentSiteEnvironment;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentSiteEnvironmentView;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class ContentSiteView;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class DesktopAttachedSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                class DesktopChildSiteBridge;
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.UI.Content.ContentAutomationOptions
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                enum ContentAutomationOptions : int
                {
                    ContentAutomationOptions_None = 0,
                    ContentAutomationOptions_FrameworkBased = 1,
                    ContentAutomationOptions_FragmentBased = 2,
                };
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Struct Microsoft.UI.Content.ContentCoordinateRoundingMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                enum ContentCoordinateRoundingMode : int
                {
                    ContentCoordinateRoundingMode_Auto = 0,
                    ContentCoordinateRoundingMode_Floor = 1,
                    ContentCoordinateRoundingMode_Round = 2,
                    ContentCoordinateRoundingMode_Ceiling = 3,
                };
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Content.ContentLayoutDirection
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                enum ContentLayoutDirection : int
                {
                    ContentLayoutDirection_LeftToRight = 0,
                    ContentLayoutDirection_RightToLeft = 1,
                };
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Content.ContentSizePolicy
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                enum ContentSizePolicy : int
                {
                    ContentSizePolicy_None = 0,
                    ContentSizePolicy_ResizeContentToParentWindow = 1,
                    ContentSizePolicy_ResizeParentWindowToContent = 2,
                };
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IChildSiteLink
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ChildSiteLink
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IChildSiteLink[] = L"Microsoft.UI.Content.IChildSiteLink";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("b5a64814-608b-5fb7-a7cb-eb628fd588cd")
                IChildSiteLink : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ActualSize(
                        ABI::Windows::Foundation::Numerics::Vector2* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ActualSize(
                        ABI::Windows::Foundation::Numerics::Vector2 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToParentTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_LocalToParentTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SiteView(
                        ABI::Microsoft::UI::Content::IContentSiteView** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Connect(
                        ABI::Microsoft::UI::Content::IContentIsland* content
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IChildSiteLink = _uuidof(IChildSiteLink);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IChildSiteLinkStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ChildSiteLink
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IChildSiteLinkStatics[] = L"Microsoft.UI.Content.IChildSiteLinkStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("28edc98a-4f94-50b1-8a87-9e7169ebf4b7")
                IChildSiteLinkStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Content::IContentIsland* parent,
                        ABI::Microsoft::UI::Composition::IContainerVisual* placementVisual,
                        ABI::Microsoft::UI::Content::IChildSiteLink** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE CreateForSystemVisual(
                        ABI::Microsoft::UI::Content::IContentIsland* parent,
                        ABI::Windows::UI::Composition::IContainerVisual* placementVisual,
                        ABI::Microsoft::UI::Content::IChildSiteLink** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IChildSiteLinkStatics = _uuidof(IChildSiteLinkStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentCoordinateConverter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentCoordinateConverter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentCoordinateConverter[] = L"Microsoft.UI.Content.IContentCoordinateConverter";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("10a11230-5eb4-5840-a346-570f4a49040f")
                IContentCoordinateConverter : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE ConvertLocalToScreenWithPoint(
                        ABI::Windows::Foundation::Point localPoint,
                        ABI::Windows::Graphics::PointInt32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ConvertLocalToScreenWithPoints(
                        UINT32 localPointsLength,
                        ABI::Windows::Foundation::Point* localPoints,
                        UINT32* resultLength,
                        ABI::Windows::Graphics::PointInt32** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ConvertLocalToScreenWithPointsAndRoundingMode(
                        UINT32 localPointsLength,
                        ABI::Windows::Foundation::Point* localPoints,
                        ABI::Microsoft::UI::Content::ContentCoordinateRoundingMode roundingMode,
                        UINT32* resultLength,
                        ABI::Windows::Graphics::PointInt32** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ConvertLocalToScreenWithRect(
                        ABI::Windows::Foundation::Rect localRect,
                        ABI::Windows::Graphics::RectInt32* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ConvertScreenToLocalWithPoint(
                        ABI::Windows::Graphics::PointInt32 screenPoint,
                        ABI::Windows::Foundation::Point* result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ConvertScreenToLocalWithPoints(
                        UINT32 screenPointsLength,
                        ABI::Windows::Graphics::PointInt32* screenPoints,
                        UINT32* resultLength,
                        ABI::Windows::Foundation::Point** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE ConvertScreenToLocalWithRect(
                        ABI::Windows::Graphics::RectInt32 screenRect,
                        ABI::Windows::Foundation::Rect* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentCoordinateConverter = _uuidof(IContentCoordinateConverter);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentCoordinateConverterFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentCoordinateConverter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentCoordinateConverterFactory[] = L"Microsoft.UI.Content.IContentCoordinateConverterFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("a4b216ee-0e26-56bd-9209-a75cf9d80f27")
                IContentCoordinateConverterFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentCoordinateConverterFactory = _uuidof(IContentCoordinateConverterFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentCoordinateConverterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentCoordinateConverter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentCoordinateConverterStatics[] = L"Microsoft.UI.Content.IContentCoordinateConverterStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("f56374ce-b6df-5b42-a58f-4e3bb039e3a9")
                IContentCoordinateConverterStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateForWindowId(
                        ABI::Microsoft::UI::WindowId windowId,
                        ABI::Microsoft::UI::Content::IContentCoordinateConverter** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentCoordinateConverterStatics = _uuidof(IContentCoordinateConverterStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentDeferral
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentDeferral[] = L"Microsoft.UI.Content.IContentDeferral";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("470529f5-cd93-599b-968e-f8a689bc3a07")
                IContentDeferral : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Complete(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentDeferral = _uuidof(IContentDeferral);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentEnvironmentSettingChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentEnvironmentSettingChangedEventArgs[] = L"Microsoft.UI.Content.IContentEnvironmentSettingChangedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("76478051-fc80-5eec-a3f3-62606abe06b7")
                IContentEnvironmentSettingChangedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_SettingName(
                        HSTRING* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentEnvironmentSettingChangedEventArgs = _uuidof(IContentEnvironmentSettingChangedEventArgs);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentEnvironmentStateChangedEventArgs[] = L"Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("8970fa4f-10ba-5f67-970b-8c72bc009b67")
                IContentEnvironmentStateChangedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidAppWindowIdChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidDisplayIdChange(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentEnvironmentStateChangedEventArgs = _uuidof(IContentEnvironmentStateChangedEventArgs);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentEnvironmentStateChangedEventArgs2[] = L"Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("cec0497d-76c7-544b-bf6e-816c9b16c99f")
                IContentEnvironmentStateChangedEventArgs2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidDisplayScaleChange(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentEnvironmentStateChangedEventArgs2 = _uuidof(IContentEnvironmentStateChangedEventArgs2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIsland
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIsland[] = L"Microsoft.UI.Content.IContentIsland";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("5b2504ba-361c-50aa-bd6e-4122c6d93889")
                IContentIsland : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ActualSize(
                        ABI::Windows::Foundation::Numerics::Vector2* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_AppData(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AppData(
                        IInspectable* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_CoordinateConverter(
                        ABI::Microsoft::UI::Content::IContentCoordinateConverter** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_CustomProperties(
                        ABI::Windows::Foundation::Collections::IPropertySet** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Environment(
                        ABI::Microsoft::UI::Content::IContentIslandEnvironment** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Id(
                        UINT64* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsConnected(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsHitTestVisibleWhenTransparent(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsHitTestVisibleWhenTransparent(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsIslandEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsIslandEnabled(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsIslandVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsIslandVisible(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSiteEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSiteVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LayoutDirection(
                        ABI::Microsoft::UI::Content::ContentLayoutDirection* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RasterizationScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetAutomationHostProvider(
                        IInspectable** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetStateChangeDeferral(
                        ABI::Microsoft::UI::Content::IContentDeferral** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE RequestSize(
                        ABI::Windows::Foundation::Numerics::Vector2 size
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_AutomationProviderRequested(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_AutomationProviderRequested(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_StateChanged(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_StateChanged(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIsland = _uuidof(IContentIsland);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIsland;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIsland2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIsland2[] = L"Microsoft.UI.Content.IContentIsland2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("9f891825-4f83-5ada-9ebd-9d329460aede")
                IContentIsland2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Children(
                        __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToClientTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToParentTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Popups(
                        __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesKeyboardInput(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesPointerInput(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIsland2 = _uuidof(IContentIsland2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandAutomation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandAutomation[] = L"Microsoft.UI.Content.IContentIslandAutomation";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("8752c11e-1896-565a-bfb0-2b0770030e97")
                IContentIslandAutomation : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AutomationOption(
                        ABI::Microsoft::UI::Content::ContentAutomationOptions* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_FragmentRootAutomationProvider(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_NextSiblingAutomationProvider(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ParentAutomationProvider(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_PreviousSiblingAutomationProvider(
                        IInspectable** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandAutomation = _uuidof(IContentIslandAutomation);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.IContentIslandAutomationProviderRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("9fe24bed-2b9c-5137-887f-403c94841824")
                IContentIslandAutomationProviderRequestedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AutomationProvider(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AutomationProvider(
                        IInspectable* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Handled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Handled(
                        boolean value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandAutomationProviderRequestedEventArgs = _uuidof(IContentIslandAutomationProviderRequestedEventArgs);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandEnvironment[] = L"Microsoft.UI.Content.IContentIslandEnvironment";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("c334236d-da88-566d-811d-74aef2eba978")
                IContentIslandEnvironment : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AppWindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayId(
                        ABI::Microsoft::UI::DisplayId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_SettingChanged(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_SettingChanged(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_StateChanged(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_StateChanged(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandEnvironment = _uuidof(IContentIslandEnvironment);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandEnvironment2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandEnvironment2[] = L"Microsoft.UI.Content.IContentIslandEnvironment2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("6bf81a71-c1e4-54d6-ac0d-02bcff5297e7")
                IContentIslandEnvironment2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayScale(
                        FLOAT* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandEnvironment2 = _uuidof(IContentIslandEnvironment2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandEnvironmentFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandEnvironmentFactory[] = L"Microsoft.UI.Content.IContentIslandEnvironmentFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("47a782d6-b177-5c1e-bf87-90437dd809d0")
                IContentIslandEnvironmentFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentIslandEnvironmentFactory = _uuidof(IContentIslandEnvironmentFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandFactory[] = L"Microsoft.UI.Content.IContentIslandFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("82383f52-e81a-5ec9-a954-bac8a931ba7d")
                IContentIslandFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentIslandFactory = _uuidof(IContentIslandFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStateChangedEventArgs[] = L"Microsoft.UI.Content.IContentIslandStateChangedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("c828eeb2-0c62-5b40-9d48-77c06083c278")
                IContentIslandStateChangedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidActualSizeChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidSiteEnabledChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidSiteVisibleChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidLayoutDirectionChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidRasterizationScaleChange(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandStateChangedEventArgs = _uuidof(IContentIslandStateChangedEventArgs);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStateChangedEventArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStateChangedEventArgs2[] = L"Microsoft.UI.Content.IContentIslandStateChangedEventArgs2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("8ad25be1-a89a-5872-896e-8298dd20eb0d")
                IContentIslandStateChangedEventArgs2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidLocalToClientTransformMatrixChange(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DidLocalToParentTransformMatrixChange(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandStateChangedEventArgs2 = _uuidof(IContentIslandStateChangedEventArgs2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStatics[] = L"Microsoft.UI.Content.IContentIslandStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("7b9eb7cc-8c43-5e0a-ab23-ab48628fd223")
                IContentIslandStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Composition::IVisual* Root,
                        ABI::Microsoft::UI::Content::IContentIsland** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FindAllForCompositor(
                        ABI::Microsoft::UI::Composition::ICompositor* compositor,
                        UINT32* resultLength,
                        ABI::Microsoft::UI::Content::IContentIsland*** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FindAllForCurrentThread(
                        UINT32* resultLength,
                        ABI::Microsoft::UI::Content::IContentIsland*** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetByVisual(
                        ABI::Microsoft::UI::Composition::IVisual* child,
                        ABI::Microsoft::UI::Content::IContentIsland** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetFromId(
                        UINT64 id,
                        ABI::Microsoft::UI::Content::IContentIsland** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandStatics = _uuidof(IContentIslandStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStatics2[] = L"Microsoft.UI.Content.IContentIslandStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("b2c6fa77-13c9-5064-bb1d-f878d86acc65")
                IContentIslandStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateForSystemVisual(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue* queue,
                        ABI::Windows::UI::Composition::IVisual* root,
                        ABI::Microsoft::UI::Content::IContentIsland** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE FindAllForSystemCompositor(
                        ABI::Windows::UI::Composition::ICompositor* compositor,
                        UINT32* resultLength,
                        ABI::Microsoft::UI::Content::IContentIsland*** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetBySystemVisual(
                        ABI::Windows::UI::Composition::IVisual* child,
                        ABI::Microsoft::UI::Content::IContentIsland** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentIslandStatics2 = _uuidof(IContentIslandStatics2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSite
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSite
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSite[] = L"Microsoft.UI.Content.IContentSite";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("996c60c4-02b2-5eef-93b0-dd6b1ec2fd7b")
                IContentSite : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ActualSize(
                        ABI::Windows::Foundation::Numerics::Vector2* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ActualSize(
                        ABI::Windows::Foundation::Numerics::Vector2 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ClientSize(
                        ABI::Windows::Graphics::SizeInt32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ClientSize(
                        ABI::Windows::Graphics::SizeInt32 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_CoordinateConverter(
                        ABI::Microsoft::UI::Content::IContentCoordinateConverter** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Environment(
                        ABI::Microsoft::UI::Content::IContentSiteEnvironment** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsConnected(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSiteEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsSiteEnabled(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSiteVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_IsSiteVisible(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LayoutDirection(
                        ABI::Microsoft::UI::Content::ContentLayoutDirection* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_LayoutDirection(
                        ABI::Microsoft::UI::Content::ContentLayoutDirection value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_OverrideScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_OverrideScale(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ParentScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ParentScale(
                        FLOAT value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RasterizationScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RequestedSize(
                        ABI::Windows::Foundation::Numerics::Vector2* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ShouldApplyRasterizationScale(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ShouldApplyRasterizationScale(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_View(
                        ABI::Microsoft::UI::Content::IContentSiteView** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE GetIslandStateChangeDeferral(
                        ABI::Microsoft::UI::Content::IContentDeferral** result
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_RequestedStateChanged(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_RequestedStateChanged(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSite = _uuidof(IContentSite);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSite;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSite2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSite
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSite2[] = L"Microsoft.UI.Content.IContentSite2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("c3f0149e-3f8c-5961-9d04-cd6c8a7f6026")
                IContentSite2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToClientTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToParentTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_LocalToParentTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4 value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesKeyboardInput(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ProcessesKeyboardInput(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesPointerInput(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ProcessesPointerInput(
                        boolean value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSite2 = _uuidof(IContentSite2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSite2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteAutomation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteAutomation[] = L"Microsoft.UI.Content.IContentSiteAutomation";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("db4f4683-cd76-50d0-9ae1-044ceb3d3c7a")
                IContentSiteAutomation : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AutomationOption(
                        ABI::Microsoft::UI::Content::ContentAutomationOptions* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AutomationOption(
                        ABI::Microsoft::UI::Content::ContentAutomationOptions value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_AutomationProvider(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_FragmentRootAutomationProviderRequested(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_FragmentRootAutomationProviderRequested(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_NextSiblingAutomationProviderRequested(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_NextSiblingAutomationProviderRequested(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_ParentAutomationProviderRequested(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_ParentAutomationProviderRequested(
                        EventRegistrationToken token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE add_PreviousSiblingAutomationProviderRequested(
                        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
                        EventRegistrationToken* token
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE remove_PreviousSiblingAutomationProviderRequested(
                        EventRegistrationToken token
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteAutomation = _uuidof(IContentSiteAutomation);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.IContentSiteAutomationProviderRequestedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("73a093b9-55d4-5598-b70e-6250b732f821")
                IContentSiteAutomationProviderRequestedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AutomationProvider(
                        IInspectable** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AutomationProvider(
                        IInspectable* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_Handled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_Handled(
                        boolean value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteAutomationProviderRequestedEventArgs = _uuidof(IContentSiteAutomationProviderRequestedEventArgs);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Windows.Foundation.IClosable
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteBridge[] = L"Microsoft.UI.Content.IContentSiteBridge";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("faaab99e-a42b-549c-92df-3b6d6e1e368b")
                IContentSiteBridge : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LayoutDirectionOverride(
                        __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_LayoutDirectionOverride(
                        __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_OverrideScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_OverrideScale(
                        FLOAT value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteBridge = _uuidof(IContentSiteBridge);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironment[] = L"Microsoft.UI.Content.IContentSiteEnvironment";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("685d085d-be53-55d1-aec4-ba2273d5468b")
                IContentSiteEnvironment : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AppWindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_AppWindowId(
                        ABI::Microsoft::UI::WindowId value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayId(
                        ABI::Microsoft::UI::DisplayId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_DisplayId(
                        ABI::Microsoft::UI::DisplayId value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_View(
                        ABI::Microsoft::UI::Content::IContentSiteEnvironmentView** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE NotifySettingChanged(
                        HSTRING setting
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteEnvironment = _uuidof(IContentSiteEnvironment);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironment2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironment2[] = L"Microsoft.UI.Content.IContentSiteEnvironment2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("381ae3cd-c780-5a69-ba6a-0ead8560a31f")
                IContentSiteEnvironment2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_DisplayScale(
                        FLOAT value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteEnvironment2 = _uuidof(IContentSiteEnvironment2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentFactory[] = L"Microsoft.UI.Content.IContentSiteEnvironmentFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("0befa998-cb15-5f16-a4a5-c0ed1674e186")
                IContentSiteEnvironmentFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentSiteEnvironmentFactory = _uuidof(IContentSiteEnvironmentFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentView[] = L"Microsoft.UI.Content.IContentSiteEnvironmentView";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("5b6fe420-0bb3-54dd-8589-786cf02e38f1")
                IContentSiteEnvironmentView : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AppWindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayId(
                        ABI::Microsoft::UI::DisplayId* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteEnvironmentView = _uuidof(IContentSiteEnvironmentView);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentView2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentView2[] = L"Microsoft.UI.Content.IContentSiteEnvironmentView2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("0b43c89a-9196-5a64-a078-eb150acae527")
                IContentSiteEnvironmentView2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DisplayScale(
                        FLOAT* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteEnvironmentView2 = _uuidof(IContentSiteEnvironmentView2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentViewFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentViewFactory[] = L"Microsoft.UI.Content.IContentSiteEnvironmentViewFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("c901edf2-f184-5a64-8d58-8cf8efa8b678")
                IContentSiteEnvironmentViewFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentSiteEnvironmentViewFactory = _uuidof(IContentSiteEnvironmentViewFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSite
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteFactory[] = L"Microsoft.UI.Content.IContentSiteFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("72fb98d5-b28a-57f1-91fa-24c014a342c1")
                IContentSiteFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentSiteFactory = _uuidof(IContentSiteFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteInput
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteInput[] = L"Microsoft.UI.Content.IContentSiteInput";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("0ead8189-10d3-550d-b747-8847bd7c9d21")
                IContentSiteInput : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesKeyboardInput(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ProcessesKeyboardInput(
                        boolean value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesPointerInput(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ProcessesPointerInput(
                        boolean value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteInput = _uuidof(IContentSiteInput);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteLink
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteLink[] = L"Microsoft.UI.Content.IContentSiteLink";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("d9247341-f5d0-5084-af66-f5df5f314fc0")
                IContentSiteLink : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_Parent(
                        ABI::Microsoft::UI::Content::IContentIsland** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteLink = _uuidof(IContentSiteLink);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteRequestedStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteRequestedStateChangedEventArgs[] = L"Microsoft.UI.Content.IContentSiteRequestedStateChangedEventArgs";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("1b55fd1d-7292-562b-b4a1-d4de7972e684")
                IContentSiteRequestedStateChangedEventArgs : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_DidRequestedSizeChange(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteRequestedStateChangedEventArgs = _uuidof(IContentSiteRequestedStateChangedEventArgs);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteView[] = L"Microsoft.UI.Content.IContentSiteView";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("2d5d8dd5-358e-5b05-993b-b2666d1786b3")
                IContentSiteView : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ActualSize(
                        ABI::Windows::Foundation::Numerics::Vector2* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ClientSize(
                        ABI::Windows::Graphics::SizeInt32* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_CoordinateConverter(
                        ABI::Microsoft::UI::Content::IContentCoordinateConverter** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_DispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_EnvironmentView(
                        ABI::Microsoft::UI::Content::IContentSiteEnvironmentView** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsConnected(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSiteEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsSiteVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LayoutDirection(
                        ABI::Microsoft::UI::Content::ContentLayoutDirection* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_OverrideScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ParentScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RasterizationScale(
                        FLOAT* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_RequestedSize(
                        ABI::Windows::Foundation::Numerics::Vector2* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ShouldApplyRasterizationScale(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteView = _uuidof(IContentSiteView);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteView2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteView2[] = L"Microsoft.UI.Content.IContentSiteView2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("628adce3-820f-57de-bdc8-3720ff73014b")
                IContentSiteView2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToClientTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_LocalToParentTransformMatrix(
                        ABI::Windows::Foundation::Numerics::Matrix4x4* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesKeyboardInput(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_ProcessesPointerInput(
                        boolean* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteView2 = _uuidof(IContentSiteView2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteViewAutomation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteViewAutomation[] = L"Microsoft.UI.Content.IContentSiteViewAutomation";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("f9d1d5ff-9669-5553-a875-aee03e11edd8")
                IContentSiteViewAutomation : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_AutomationOption(
                        ABI::Microsoft::UI::Content::ContentAutomationOptions* value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IContentSiteViewAutomation = _uuidof(IContentSiteViewAutomation);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteViewFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteViewFactory[] = L"Microsoft.UI.Content.IContentSiteViewFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("9efd72f0-63ef-5b6a-a50c-5685bd8100f1")
                IContentSiteViewFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IContentSiteViewFactory = _uuidof(IContentSiteViewFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopAttachedSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopAttachedSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopAttachedSiteBridge[] = L"Microsoft.UI.Content.IDesktopAttachedSiteBridge";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("c8ad3758-c8d3-5ea5-a274-ce12d9cf6845")
                IDesktopAttachedSiteBridge : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_SiteView(
                        ABI::Microsoft::UI::Content::IContentSiteView** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_WindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Connect(
                        ABI::Microsoft::UI::Content::IContentIsland* content
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopAttachedSiteBridge = _uuidof(IDesktopAttachedSiteBridge);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopAttachedSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopAttachedSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopAttachedSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopAttachedSiteBridgeStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("41f6930f-310e-5680-812c-6dac16dfff44")
                IDesktopAttachedSiteBridgeStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateFromWindowId(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue* queue,
                        ABI::Microsoft::UI::WindowId windowId,
                        ABI::Microsoft::UI::Content::IDesktopAttachedSiteBridge** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopAttachedSiteBridgeStatics = _uuidof(IDesktopAttachedSiteBridgeStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopChildSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopChildSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopChildSiteBridge[] = L"Microsoft.UI.Content.IDesktopChildSiteBridge";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("b2f2ff7b-1825-51b0-b80b-7599889c569f")
                IDesktopChildSiteBridge : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_ResizePolicy(
                        ABI::Microsoft::UI::Content::ContentSizePolicy* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE put_ResizePolicy(
                        ABI::Microsoft::UI::Content::ContentSizePolicy value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SiteView(
                        ABI::Microsoft::UI::Content::IContentSiteView** value
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopChildSiteBridge = _uuidof(IDesktopChildSiteBridge);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopChildSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopChildSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopChildSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopChildSiteBridgeStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("ab6b82de-6a47-5de3-a860-613c8db679ab")
                IDesktopChildSiteBridgeStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Composition::ICompositor* compositor,
                        ABI::Microsoft::UI::WindowId parentWindowId,
                        ABI::Microsoft::UI::Content::IDesktopChildSiteBridge** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopChildSiteBridgeStatics = _uuidof(IDesktopChildSiteBridgeStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopChildSiteBridgeStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopChildSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopChildSiteBridgeStatics2[] = L"Microsoft.UI.Content.IDesktopChildSiteBridgeStatics2";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("aae99407-e378-5c53-9aff-5a3b53e194a8")
                IDesktopChildSiteBridgeStatics2 : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE CreateWithDispatcherQueue(
                        ABI::Microsoft::UI::Dispatching::IDispatcherQueue* queue,
                        ABI::Microsoft::UI::WindowId parentWindowId,
                        ABI::Microsoft::UI::Content::IDesktopChildSiteBridge** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopChildSiteBridgeStatics2 = _uuidof(IDesktopChildSiteBridgeStatics2);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopPopupSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopPopupSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopPopupSiteBridge[] = L"Microsoft.UI.Content.IDesktopPopupSiteBridge";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("84eaab23-f716-5ad8-ac00-3d77c01d42cc")
                IDesktopPopupSiteBridge : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_IsEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_SiteView(
                        ABI::Microsoft::UI::Content::IContentSiteView** value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_WindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Connect(
                        ABI::Microsoft::UI::Content::IContentIsland* content
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Disable(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Enable(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Hide(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveAndResize(
                        ABI::Windows::Graphics::RectInt32 rect
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderAtBottom(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderAtTop(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderBelow(
                        ABI::Microsoft::UI::WindowId windowId
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Show(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopPopupSiteBridge = _uuidof(IDesktopPopupSiteBridge);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopPopupSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopPopupSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopPopupSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopPopupSiteBridgeStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("4ea2b77b-3177-5e5b-8d0d-a76e15c6d080")
                IDesktopPopupSiteBridgeStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE Create(
                        ABI::Microsoft::UI::Content::IContentIsland* parent,
                        ABI::Microsoft::UI::Content::IDesktopPopupSiteBridge** result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopPopupSiteBridgeStatics = _uuidof(IDesktopPopupSiteBridgeStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopSiteBridge[] = L"Microsoft.UI.Content.IDesktopSiteBridge";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("f0ae8750-905c-50a2-8a12-4545c6245bb4")
                IDesktopSiteBridge : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE get_IsEnabled(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_IsVisible(
                        boolean* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE get_WindowId(
                        ABI::Microsoft::UI::WindowId* value
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Connect(
                        ABI::Microsoft::UI::Content::IContentIsland* content
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Disable(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Enable(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Hide(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveAndResize(
                        ABI::Windows::Graphics::RectInt32 rect
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderAtBottom(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderAtTop(void) = 0;
                    virtual HRESULT STDMETHODCALLTYPE MoveInZOrderBelow(
                        ABI::Microsoft::UI::WindowId windowId
                        ) = 0;
                    virtual HRESULT STDMETHODCALLTYPE Show(void) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopSiteBridge = _uuidof(IDesktopSiteBridge);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopSiteBridgeFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopSiteBridgeFactory[] = L"Microsoft.UI.Content.IDesktopSiteBridgeFactory";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("d94ee1ff-3af1-54d0-9311-652b29c57c5b")
                IDesktopSiteBridgeFactory : public IInspectable
                {
                public:
                };

                MIDL_CONST_ID IID& IID_IDesktopSiteBridgeFactory = _uuidof(IDesktopSiteBridgeFactory);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopSiteBridgeStatics";
namespace ABI {
    namespace Microsoft {
        namespace UI {
            namespace Content {
                MIDL_INTERFACE("e0b38daf-9cd4-50c5-83ee-c76e3cf34eba")
                IDesktopSiteBridgeStatics : public IInspectable
                {
                public:
                    virtual HRESULT STDMETHODCALLTYPE IsSupported(
                        boolean* result
                        ) = 0;
                };

                MIDL_CONST_ID IID& IID_IDesktopSiteBridgeStatics = _uuidof(IDesktopSiteBridgeStatics);
            } /* Content */
        } /* UI */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ChildSiteLink
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IChildSiteLinkStatics interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IChildSiteLink ** Default Interface **
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteAutomation
 *    Microsoft.UI.Content.IContentSiteInput
 *    Microsoft.UI.Content.IContentSiteLink
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ChildSiteLink_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ChildSiteLink_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ChildSiteLink[] = L"Microsoft.UI.Content.ChildSiteLink";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.ContentCoordinateConverter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IContentCoordinateConverterStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentCoordinateConverter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentCoordinateConverter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentCoordinateConverter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentCoordinateConverter[] = L"Microsoft.UI.Content.ContentCoordinateConverter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentDeferral ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentDeferral_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentDeferral_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentDeferral[] = L"Microsoft.UI.Content.ContentDeferral";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentEnvironmentSettingChangedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentSettingChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentSettingChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentEnvironmentSettingChangedEventArgs[] = L"Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs ** Default Interface **
 *    Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentStateChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentStateChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentEnvironmentStateChangedEventArgs[] = L"Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIsland
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IContentIslandStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Content.IContentIslandStatics2 interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIsland ** Default Interface **
 *    Microsoft.UI.Content.IContentIsland2
 *    Microsoft.UI.Content.IContentIslandAutomation
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Composition.ICompositionSupportsSystemBackdrop
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIsland_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIsland_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIsland[] = L"Microsoft.UI.Content.ContentIsland";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIslandAutomationProviderRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIslandAutomationProviderRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIslandAutomationProviderRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIslandAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIslandEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIslandEnvironment ** Default Interface **
 *    Microsoft.UI.Content.IContentIslandEnvironment2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIslandEnvironment_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIslandEnvironment_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIslandEnvironment[] = L"Microsoft.UI.Content.ContentIslandEnvironment";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIslandStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIslandStateChangedEventArgs ** Default Interface **
 *    Microsoft.UI.Content.IContentIslandStateChangedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIslandStateChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIslandStateChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIslandStateChangedEventArgs[] = L"Microsoft.UI.Content.ContentIslandStateChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSite
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSite ** Default Interface **
 *    Microsoft.UI.Content.IContentSite2
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSite_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSite_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSite[] = L"Microsoft.UI.Content.ContentSite";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteAutomationProviderRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteAutomationProviderRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteAutomationProviderRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.ContentSiteEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteEnvironment ** Default Interface **
 *    Microsoft.UI.Content.IContentSiteEnvironment2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironment_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironment_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteEnvironment[] = L"Microsoft.UI.Content.ContentSiteEnvironment";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteEnvironmentView ** Default Interface **
 *    Microsoft.UI.Content.IContentSiteEnvironmentView2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironmentView_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironmentView_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteEnvironmentView[] = L"Microsoft.UI.Content.ContentSiteEnvironmentView";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteRequestedStateChangedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteRequestedStateChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteRequestedStateChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteRequestedStateChangedEventArgs[] = L"Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteView ** Default Interface **
 *    Microsoft.UI.Content.IContentSiteView2
 *    Microsoft.UI.Content.IContentSiteViewAutomation
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteView_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteView_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteView[] = L"Microsoft.UI.Content.ContentSiteView";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.DesktopAttachedSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopAttachedSiteBridgeStatics interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopAttachedSiteBridge ** Default Interface **
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteBridge
 *    Microsoft.UI.Content.IContentSiteInput
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopAttachedSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopAttachedSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopAttachedSiteBridge[] = L"Microsoft.UI.Content.DesktopAttachedSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.DesktopChildSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopChildSiteBridgeStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopChildSiteBridgeStatics2 interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopChildSiteBridge ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopChildSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopChildSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopChildSiteBridge[] = L"Microsoft.UI.Content.DesktopChildSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.DesktopPopupSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopPopupSiteBridgeStatics interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopPopupSiteBridge ** Default Interface **
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteAutomation
 *    Microsoft.UI.Content.IContentSiteBridge
 *    Microsoft.UI.Content.IContentSiteLink
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopPopupSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopPopupSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopPopupSiteBridge[] = L"Microsoft.UI.Content.DesktopPopupSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.DesktopSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopSiteBridgeStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopSiteBridge ** Default Interface **
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteBridge
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopSiteBridge[] = L"Microsoft.UI.Content.DesktopSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2 __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2 __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2 __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2 __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2 __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSite __x_ABI_CMicrosoft_CUI_CContent_CIContentSite;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2 __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2 __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2 __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2 __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2 __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics;

#endif // ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink;

typedef struct __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLinkVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLinkVtbl;

interface __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLinkVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink;

typedef struct __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLinkVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink* This,
        __FIIterator_1_Microsoft__CUI__CContent__CChildSiteLink** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLinkVtbl;

interface __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLinkVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge;

typedef struct __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridgeVtbl;

interface __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge;

typedef struct __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge* This,
        __FIIterator_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridgeVtbl;

interface __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

typedef enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection;

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_INTERFACE_DEFINED__)
#define ____FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_INTERFACE_DEFINED__

typedef interface __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection;

typedef struct __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirectionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection* result);

    END_INTERFACE
} __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirectionVtbl;

interface __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection
{
    CONST_VTBL struct __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirectionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* sender,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* sender,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* sender,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* sender,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSite* sender,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs;

typedef struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* sender,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgsVtbl;

interface __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositor __x_ABI_CMicrosoft_CUI_CComposition_CICompositor;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositor_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual __x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop __x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CICompositionSupportsSystemBackdrop_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CComposition_CIVisual __x_ABI_CMicrosoft_CUI_CComposition_CIVisual;

#endif // ____x_ABI_CMicrosoft_CUI_CComposition_CIVisual_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue;

#endif // ____x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CDisplayId __x_ABI_CMicrosoft_CUI_CDisplayId;

#ifndef ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CUI_CIClosableNotifier __x_ABI_CMicrosoft_CUI_CIClosableNotifier;

#endif // ____x_ABI_CMicrosoft_CUI_CIClosableNotifier_FWD_DEFINED__

typedef struct __x_ABI_CMicrosoft_CUI_CWindowId __x_ABI_CMicrosoft_CUI_CWindowId;

#ifndef ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet;

#endif // ____x_ABI_CWindows_CFoundation_CCollections_CIPropertySet_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIPropertyValue __x_ABI_CWindows_CFoundation_CIPropertyValue;

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4 __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4;

typedef struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2 __x_ABI_CWindows_CFoundation_CNumerics_CVector2;

typedef struct __x_ABI_CWindows_CFoundation_CPoint __x_ABI_CWindows_CFoundation_CPoint;

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

typedef struct __x_ABI_CWindows_CGraphics_CPointInt32 __x_ABI_CWindows_CGraphics_CPointInt32;

typedef struct __x_ABI_CWindows_CGraphics_CRectInt32 __x_ABI_CWindows_CGraphics_CRectInt32;

typedef struct __x_ABI_CWindows_CGraphics_CSizeInt32 __x_ABI_CWindows_CGraphics_CSizeInt32;

#ifndef ____x_ABI_CWindows_CUI_CComposition_CICompositor_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CICompositor_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CUI_CComposition_CICompositor __x_ABI_CWindows_CUI_CComposition_CICompositor;

#endif // ____x_ABI_CWindows_CUI_CComposition_CICompositor_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CUI_CComposition_CIContainerVisual __x_ABI_CWindows_CUI_CComposition_CIContainerVisual;

#endif // ____x_ABI_CWindows_CUI_CComposition_CIContainerVisual_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CUI_CComposition_CIVisual_FWD_DEFINED__
#define ____x_ABI_CWindows_CUI_CComposition_CIVisual_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CUI_CComposition_CIVisual __x_ABI_CWindows_CUI_CComposition_CIVisual;

#endif // ____x_ABI_CWindows_CUI_CComposition_CIVisual_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions;

typedef enum __x_ABI_CMicrosoft_CUI_CContent_CContentCoordinateRoundingMode __x_ABI_CMicrosoft_CUI_CContent_CContentCoordinateRoundingMode;

typedef enum __x_ABI_CMicrosoft_CUI_CContent_CContentSizePolicy __x_ABI_CMicrosoft_CUI_CContent_CContentSizePolicy;

/*
 *
 * Struct Microsoft.UI.Content.ContentAutomationOptions
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
enum __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions
{
    ContentAutomationOptions_None = 0,
    ContentAutomationOptions_FrameworkBased = 1,
    ContentAutomationOptions_FragmentBased = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Struct Microsoft.UI.Content.ContentCoordinateRoundingMode
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CContent_CContentCoordinateRoundingMode
{
    ContentCoordinateRoundingMode_Auto = 0,
    ContentCoordinateRoundingMode_Floor = 1,
    ContentCoordinateRoundingMode_Round = 2,
    ContentCoordinateRoundingMode_Ceiling = 3,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Content.ContentLayoutDirection
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection
{
    ContentLayoutDirection_LeftToRight = 0,
    ContentLayoutDirection_RightToLeft = 1,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Struct Microsoft.UI.Content.ContentSizePolicy
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
enum __x_ABI_CMicrosoft_CUI_CContent_CContentSizePolicy
{
    ContentSizePolicy_None = 0,
    ContentSizePolicy_ResizeContentToParentWindow = 1,
    ContentSizePolicy_ResizeParentWindowToContent = 2,
};
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IChildSiteLink
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ChildSiteLink
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IChildSiteLink[] = L"Microsoft.UI.Content.IChildSiteLink";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ActualSize)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2* value);
    HRESULT (STDMETHODCALLTYPE* put_ActualSize)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2 value);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* get_LocalToParentTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* put_LocalToParentTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4 value);
    HRESULT (STDMETHODCALLTYPE* get_SiteView)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView** value);
    HRESULT (STDMETHODCALLTYPE* Connect)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* content);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_get_ActualSize(This, value) \
    ((This)->lpVtbl->get_ActualSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_put_ActualSize(This, value) \
    ((This)->lpVtbl->put_ActualSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_get_LocalToParentTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToParentTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_put_LocalToParentTransformMatrix(This, value) \
    ((This)->lpVtbl->put_LocalToParentTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_get_SiteView(This, value) \
    ((This)->lpVtbl->get_SiteView(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_Connect(This, content) \
    ((This)->lpVtbl->Connect(This, content))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IChildSiteLinkStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ChildSiteLink
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IChildSiteLinkStatics[] = L"Microsoft.UI.Content.IChildSiteLinkStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* parent,
        __x_ABI_CMicrosoft_CUI_CComposition_CIContainerVisual* placementVisual,
        __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink** result);
    HRESULT (STDMETHODCALLTYPE* CreateForSystemVisual)(__x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* parent,
        __x_ABI_CWindows_CUI_CComposition_CIContainerVisual* placementVisual,
        __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLink** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_Create(This, parent, placementVisual, result) \
    ((This)->lpVtbl->Create(This, parent, placementVisual, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_CreateForSystemVisual(This, parent, placementVisual, result) \
    ((This)->lpVtbl->CreateForSystemVisual(This, parent, placementVisual, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIChildSiteLinkStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentCoordinateConverter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentCoordinateConverter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentCoordinateConverter[] = L"Microsoft.UI.Content.IContentCoordinateConverter";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* ConvertLocalToScreenWithPoint)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        struct __x_ABI_CWindows_CFoundation_CPoint localPoint,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* result);
    HRESULT (STDMETHODCALLTYPE* ConvertLocalToScreenWithPoints)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        UINT32 localPointsLength,
        struct __x_ABI_CWindows_CFoundation_CPoint* localPoints,
        UINT32* resultLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32** result);
    HRESULT (STDMETHODCALLTYPE* ConvertLocalToScreenWithPointsAndRoundingMode)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        UINT32 localPointsLength,
        struct __x_ABI_CWindows_CFoundation_CPoint* localPoints,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentCoordinateRoundingMode roundingMode,
        UINT32* resultLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32** result);
    HRESULT (STDMETHODCALLTYPE* ConvertLocalToScreenWithRect)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        struct __x_ABI_CWindows_CFoundation_CRect localRect,
        struct __x_ABI_CWindows_CGraphics_CRectInt32* result);
    HRESULT (STDMETHODCALLTYPE* ConvertScreenToLocalWithPoint)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        struct __x_ABI_CWindows_CGraphics_CPointInt32 screenPoint,
        struct __x_ABI_CWindows_CFoundation_CPoint* result);
    HRESULT (STDMETHODCALLTYPE* ConvertScreenToLocalWithPoints)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        UINT32 screenPointsLength,
        struct __x_ABI_CWindows_CGraphics_CPointInt32* screenPoints,
        UINT32* resultLength,
        struct __x_ABI_CWindows_CFoundation_CPoint** result);
    HRESULT (STDMETHODCALLTYPE* ConvertScreenToLocalWithRect)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 screenRect,
        struct __x_ABI_CWindows_CFoundation_CRect* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertLocalToScreenWithPoint(This, localPoint, result) \
    ((This)->lpVtbl->ConvertLocalToScreenWithPoint(This, localPoint, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertLocalToScreenWithPoints(This, localPointsLength, localPoints, resultLength, result) \
    ((This)->lpVtbl->ConvertLocalToScreenWithPoints(This, localPointsLength, localPoints, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertLocalToScreenWithPointsAndRoundingMode(This, localPointsLength, localPoints, roundingMode, resultLength, result) \
    ((This)->lpVtbl->ConvertLocalToScreenWithPointsAndRoundingMode(This, localPointsLength, localPoints, roundingMode, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertLocalToScreenWithRect(This, localRect, result) \
    ((This)->lpVtbl->ConvertLocalToScreenWithRect(This, localRect, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertScreenToLocalWithPoint(This, screenPoint, result) \
    ((This)->lpVtbl->ConvertScreenToLocalWithPoint(This, screenPoint, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertScreenToLocalWithPoints(This, screenPointsLength, screenPoints, resultLength, result) \
    ((This)->lpVtbl->ConvertScreenToLocalWithPoints(This, screenPointsLength, screenPoints, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_ConvertScreenToLocalWithRect(This, screenRect, result) \
    ((This)->lpVtbl->ConvertScreenToLocalWithRect(This, screenRect, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentCoordinateConverterFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentCoordinateConverter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentCoordinateConverterFactory[] = L"Microsoft.UI.Content.IContentCoordinateConverterFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentCoordinateConverterStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentCoordinateConverter
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentCoordinateConverterStatics[] = L"Microsoft.UI.Content.IContentCoordinateConverterStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForWindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_CreateForWindowId(This, windowId, result) \
    ((This)->lpVtbl->CreateForWindowId(This, windowId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverterStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentDeferral
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentDeferral[] = L"Microsoft.UI.Content.IContentDeferral";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferralVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Complete)(__x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferralVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferralVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_Complete(This) \
    ((This)->lpVtbl->Complete(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentEnvironmentSettingChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentEnvironmentSettingChangedEventArgs[] = L"Microsoft.UI.Content.IContentEnvironmentSettingChangedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SettingName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_get_SettingName(This, value) \
    ((This)->lpVtbl->get_SettingName(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentSettingChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentEnvironmentStateChangedEventArgs[] = L"Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidAppWindowIdChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidDisplayIdChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_get_DidAppWindowIdChange(This, value) \
    ((This)->lpVtbl->get_DidAppWindowIdChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_get_DidDisplayIdChange(This, value) \
    ((This)->lpVtbl->get_DidDisplayIdChange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentEnvironmentStateChangedEventArgs2[] = L"Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidDisplayScaleChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_get_DidDisplayScaleChange(This, value) \
    ((This)->lpVtbl->get_DidDisplayScaleChange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentEnvironmentStateChangedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIsland
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIsland[] = L"Microsoft.UI.Content.IContentIsland";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ActualSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2* value);
    HRESULT (STDMETHODCALLTYPE* get_AppData)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* put_AppData)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        IInspectable* value);
    HRESULT (STDMETHODCALLTYPE* get_CoordinateConverter)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter** value);
    HRESULT (STDMETHODCALLTYPE* get_CustomProperties)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __x_ABI_CWindows_CFoundation_CCollections_CIPropertySet** value);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* get_Environment)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment** value);
    HRESULT (STDMETHODCALLTYPE* get_Id)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        UINT64* value);
    HRESULT (STDMETHODCALLTYPE* get_IsConnected)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsHitTestVisibleWhenTransparent)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsHitTestVisibleWhenTransparent)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsIslandEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsIslandEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsIslandVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsIslandVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsSiteEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsSiteVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_LayoutDirection)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_RasterizationScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* GetAutomationHostProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        IInspectable** result);
    HRESULT (STDMETHODCALLTYPE* GetStateChangeDeferral)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral** result);
    HRESULT (STDMETHODCALLTYPE* RequestSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2 size);
    HRESULT (STDMETHODCALLTYPE* add_AutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandAutomationProviderRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_AutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_StateChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIsland_Microsoft__CUI__CContent__CContentIslandStateChangedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_StateChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_ActualSize(This, value) \
    ((This)->lpVtbl->get_ActualSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_AppData(This, value) \
    ((This)->lpVtbl->get_AppData(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_put_AppData(This, value) \
    ((This)->lpVtbl->put_AppData(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_CoordinateConverter(This, value) \
    ((This)->lpVtbl->get_CoordinateConverter(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_CustomProperties(This, value) \
    ((This)->lpVtbl->get_CustomProperties(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_Environment(This, value) \
    ((This)->lpVtbl->get_Environment(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_Id(This, value) \
    ((This)->lpVtbl->get_Id(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_IsConnected(This, value) \
    ((This)->lpVtbl->get_IsConnected(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_IsHitTestVisibleWhenTransparent(This, value) \
    ((This)->lpVtbl->get_IsHitTestVisibleWhenTransparent(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_put_IsHitTestVisibleWhenTransparent(This, value) \
    ((This)->lpVtbl->put_IsHitTestVisibleWhenTransparent(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_IsIslandEnabled(This, value) \
    ((This)->lpVtbl->get_IsIslandEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_put_IsIslandEnabled(This, value) \
    ((This)->lpVtbl->put_IsIslandEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_IsIslandVisible(This, value) \
    ((This)->lpVtbl->get_IsIslandVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_put_IsIslandVisible(This, value) \
    ((This)->lpVtbl->put_IsIslandVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_IsSiteEnabled(This, value) \
    ((This)->lpVtbl->get_IsSiteEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_IsSiteVisible(This, value) \
    ((This)->lpVtbl->get_IsSiteVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_LayoutDirection(This, value) \
    ((This)->lpVtbl->get_LayoutDirection(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_get_RasterizationScale(This, value) \
    ((This)->lpVtbl->get_RasterizationScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_GetAutomationHostProvider(This, result) \
    ((This)->lpVtbl->GetAutomationHostProvider(This, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_GetStateChangeDeferral(This, result) \
    ((This)->lpVtbl->GetStateChangeDeferral(This, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_RequestSize(This, size) \
    ((This)->lpVtbl->RequestSize(This, size))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_add_AutomationProviderRequested(This, handler, token) \
    ((This)->lpVtbl->add_AutomationProviderRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_remove_AutomationProviderRequested(This, token) \
    ((This)->lpVtbl->remove_AutomationProviderRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_add_StateChanged(This, handler, token) \
    ((This)->lpVtbl->add_StateChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_remove_StateChanged(This, token) \
    ((This)->lpVtbl->remove_StateChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIsland;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIsland2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIsland2[] = L"Microsoft.UI.Content.IContentIsland2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Children)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        __FIIterable_1_Microsoft__CUI__CContent__CChildSiteLink** value);
    HRESULT (STDMETHODCALLTYPE* get_LocalToClientTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* get_LocalToParentTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* get_Popups)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        __FIIterable_1_Microsoft__CUI__CContent__CDesktopPopupSiteBridge** value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesKeyboardInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesPointerInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_get_Children(This, value) \
    ((This)->lpVtbl->get_Children(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_get_LocalToClientTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToClientTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_get_LocalToParentTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToParentTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_get_Popups(This, value) \
    ((This)->lpVtbl->get_Popups(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_get_ProcessesKeyboardInput(This, value) \
    ((This)->lpVtbl->get_ProcessesKeyboardInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_get_ProcessesPointerInput(This, value) \
    ((This)->lpVtbl->get_ProcessesPointerInput(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIsland2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandAutomation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandAutomation[] = L"Microsoft.UI.Content.IContentIslandAutomation";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AutomationOption)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions* value);
    HRESULT (STDMETHODCALLTYPE* get_FragmentRootAutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_NextSiblingAutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_ParentAutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* get_PreviousSiblingAutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation* This,
        IInspectable** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_get_AutomationOption(This, value) \
    ((This)->lpVtbl->get_AutomationOption(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_get_FragmentRootAutomationProvider(This, value) \
    ((This)->lpVtbl->get_FragmentRootAutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_get_NextSiblingAutomationProvider(This, value) \
    ((This)->lpVtbl->get_NextSiblingAutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_get_ParentAutomationProvider(This, value) \
    ((This)->lpVtbl->get_ParentAutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_get_PreviousSiblingAutomationProvider(This, value) \
    ((This)->lpVtbl->get_PreviousSiblingAutomationProvider(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.IContentIslandAutomationProviderRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* put_AutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        IInspectable* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_get_AutomationProvider(This, value) \
    ((This)->lpVtbl->get_AutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_put_AutomationProvider(This, value) \
    ((This)->lpVtbl->put_AutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandEnvironment[] = L"Microsoft.UI.Content.IContentIslandEnvironment";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AppWindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* get_DisplayId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId* value);
    HRESULT (STDMETHODCALLTYPE* add_SettingChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentSettingChangedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_SettingChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_StateChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentIslandEnvironment_Microsoft__CUI__CContent__CContentEnvironmentStateChangedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_StateChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_get_AppWindowId(This, value) \
    ((This)->lpVtbl->get_AppWindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_get_DisplayId(This, value) \
    ((This)->lpVtbl->get_DisplayId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_add_SettingChanged(This, handler, token) \
    ((This)->lpVtbl->add_SettingChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_remove_SettingChanged(This, token) \
    ((This)->lpVtbl->remove_SettingChanged(This, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_add_StateChanged(This, handler, token) \
    ((This)->lpVtbl->add_StateChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_remove_StateChanged(This, token) \
    ((This)->lpVtbl->remove_StateChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandEnvironment2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandEnvironment2[] = L"Microsoft.UI.Content.IContentIslandEnvironment2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DisplayScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_get_DisplayScale(This, value) \
    ((This)->lpVtbl->get_DisplayScale(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironment2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandEnvironmentFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandEnvironmentFactory[] = L"Microsoft.UI.Content.IContentIslandEnvironmentFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandEnvironmentFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandFactory[] = L"Microsoft.UI.Content.IContentIslandFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStateChangedEventArgs[] = L"Microsoft.UI.Content.IContentIslandStateChangedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidActualSizeChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidSiteEnabledChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidSiteVisibleChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidLayoutDirectionChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidRasterizationScaleChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_get_DidActualSizeChange(This, value) \
    ((This)->lpVtbl->get_DidActualSizeChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_get_DidSiteEnabledChange(This, value) \
    ((This)->lpVtbl->get_DidSiteEnabledChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_get_DidSiteVisibleChange(This, value) \
    ((This)->lpVtbl->get_DidSiteVisibleChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_get_DidLayoutDirectionChange(This, value) \
    ((This)->lpVtbl->get_DidLayoutDirectionChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_get_DidRasterizationScaleChange(This, value) \
    ((This)->lpVtbl->get_DidRasterizationScaleChange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStateChangedEventArgs2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIslandStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStateChangedEventArgs2[] = L"Microsoft.UI.Content.IContentIslandStateChangedEventArgs2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidLocalToClientTransformMatrixChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_DidLocalToParentTransformMatrixChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_get_DidLocalToClientTransformMatrixChange(This, value) \
    ((This)->lpVtbl->get_DidLocalToClientTransformMatrixChange(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_get_DidLocalToParentTransformMatrixChange(This, value) \
    ((This)->lpVtbl->get_DidLocalToParentTransformMatrixChange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStateChangedEventArgs2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStatics[] = L"Microsoft.UI.Content.IContentIslandStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* Root,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland** result);
    HRESULT (STDMETHODCALLTYPE* FindAllForCompositor)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland*** result);
    HRESULT (STDMETHODCALLTYPE* FindAllForCurrentThread)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland*** result);
    HRESULT (STDMETHODCALLTYPE* GetByVisual)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CIVisual* child,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland** result);
    HRESULT (STDMETHODCALLTYPE* GetFromId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics* This,
        UINT64 id,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_Create(This, Root, result) \
    ((This)->lpVtbl->Create(This, Root, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FindAllForCompositor(This, compositor, resultLength, result) \
    ((This)->lpVtbl->FindAllForCompositor(This, compositor, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_FindAllForCurrentThread(This, resultLength, result) \
    ((This)->lpVtbl->FindAllForCurrentThread(This, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_GetByVisual(This, child, result) \
    ((This)->lpVtbl->GetByVisual(This, child, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_GetFromId(This, id, result) \
    ((This)->lpVtbl->GetFromId(This, id, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentIslandStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentIsland
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentIslandStatics2[] = L"Microsoft.UI.Content.IContentIslandStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateForSystemVisual)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* queue,
        __x_ABI_CWindows_CUI_CComposition_CIVisual* root,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland** result);
    HRESULT (STDMETHODCALLTYPE* FindAllForSystemCompositor)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        __x_ABI_CWindows_CUI_CComposition_CICompositor* compositor,
        UINT32* resultLength,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland*** result);
    HRESULT (STDMETHODCALLTYPE* GetBySystemVisual)(__x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2* This,
        __x_ABI_CWindows_CUI_CComposition_CIVisual* child,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_CreateForSystemVisual(This, queue, root, result) \
    ((This)->lpVtbl->CreateForSystemVisual(This, queue, root, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_FindAllForSystemCompositor(This, compositor, resultLength, result) \
    ((This)->lpVtbl->FindAllForSystemCompositor(This, compositor, resultLength, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_GetBySystemVisual(This, child, result) \
    ((This)->lpVtbl->GetBySystemVisual(This, child, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentIslandStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSite
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSite
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSite[] = L"Microsoft.UI.Content.IContentSite";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ActualSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2* value);
    HRESULT (STDMETHODCALLTYPE* put_ActualSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2 value);
    HRESULT (STDMETHODCALLTYPE* get_ClientSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32* value);
    HRESULT (STDMETHODCALLTYPE* put_ClientSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32 value);
    HRESULT (STDMETHODCALLTYPE* get_CoordinateConverter)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter** value);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* get_Environment)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment** value);
    HRESULT (STDMETHODCALLTYPE* get_IsConnected)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsSiteEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsSiteEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_IsSiteVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_IsSiteVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_LayoutDirection)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection* value);
    HRESULT (STDMETHODCALLTYPE* put_LayoutDirection)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection value);
    HRESULT (STDMETHODCALLTYPE* get_OverrideScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_OverrideScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_ParentScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_ParentScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        FLOAT value);
    HRESULT (STDMETHODCALLTYPE* get_RasterizationScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_RequestedSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2* value);
    HRESULT (STDMETHODCALLTYPE* get_ShouldApplyRasterizationScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ShouldApplyRasterizationScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_View)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView** value);
    HRESULT (STDMETHODCALLTYPE* GetIslandStateChangeDeferral)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentDeferral** result);
    HRESULT (STDMETHODCALLTYPE* add_RequestedStateChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CContentSite_Microsoft__CUI__CContent__CContentSiteRequestedStateChangedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_RequestedStateChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSite
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_ActualSize(This, value) \
    ((This)->lpVtbl->get_ActualSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_ActualSize(This, value) \
    ((This)->lpVtbl->put_ActualSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_ClientSize(This, value) \
    ((This)->lpVtbl->get_ClientSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_ClientSize(This, value) \
    ((This)->lpVtbl->put_ClientSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_CoordinateConverter(This, value) \
    ((This)->lpVtbl->get_CoordinateConverter(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_Environment(This, value) \
    ((This)->lpVtbl->get_Environment(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_IsConnected(This, value) \
    ((This)->lpVtbl->get_IsConnected(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_IsSiteEnabled(This, value) \
    ((This)->lpVtbl->get_IsSiteEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_IsSiteEnabled(This, value) \
    ((This)->lpVtbl->put_IsSiteEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_IsSiteVisible(This, value) \
    ((This)->lpVtbl->get_IsSiteVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_IsSiteVisible(This, value) \
    ((This)->lpVtbl->put_IsSiteVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_LayoutDirection(This, value) \
    ((This)->lpVtbl->get_LayoutDirection(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_LayoutDirection(This, value) \
    ((This)->lpVtbl->put_LayoutDirection(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_OverrideScale(This, value) \
    ((This)->lpVtbl->get_OverrideScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_OverrideScale(This, value) \
    ((This)->lpVtbl->put_OverrideScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_ParentScale(This, value) \
    ((This)->lpVtbl->get_ParentScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_ParentScale(This, value) \
    ((This)->lpVtbl->put_ParentScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_RasterizationScale(This, value) \
    ((This)->lpVtbl->get_RasterizationScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_RequestedSize(This, value) \
    ((This)->lpVtbl->get_RequestedSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_ShouldApplyRasterizationScale(This, value) \
    ((This)->lpVtbl->get_ShouldApplyRasterizationScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_put_ShouldApplyRasterizationScale(This, value) \
    ((This)->lpVtbl->put_ShouldApplyRasterizationScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_get_View(This, value) \
    ((This)->lpVtbl->get_View(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_GetIslandStateChangeDeferral(This, result) \
    ((This)->lpVtbl->GetIslandStateChangeDeferral(This, result))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_add_RequestedStateChanged(This, handler, token) \
    ((This)->lpVtbl->add_RequestedStateChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite_remove_RequestedStateChanged(This, token) \
    ((This)->lpVtbl->remove_RequestedStateChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSite;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSite2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSite
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSite2[] = L"Microsoft.UI.Content.IContentSite2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_LocalToClientTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* get_LocalToParentTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* put_LocalToParentTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4 value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesKeyboardInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ProcessesKeyboardInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesPointerInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ProcessesPointerInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSite2* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_get_LocalToClientTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToClientTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_get_LocalToParentTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToParentTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_put_LocalToParentTransformMatrix(This, value) \
    ((This)->lpVtbl->put_LocalToParentTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_get_ProcessesKeyboardInput(This, value) \
    ((This)->lpVtbl->get_ProcessesKeyboardInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_put_ProcessesKeyboardInput(This, value) \
    ((This)->lpVtbl->put_ProcessesKeyboardInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_get_ProcessesPointerInput(This, value) \
    ((This)->lpVtbl->get_ProcessesPointerInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_put_ProcessesPointerInput(This, value) \
    ((This)->lpVtbl->put_ProcessesPointerInput(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSite2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSite2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteAutomation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteAutomation[] = L"Microsoft.UI.Content.IContentSiteAutomation";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AutomationOption)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions* value);
    HRESULT (STDMETHODCALLTYPE* put_AutomationOption)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions value);
    HRESULT (STDMETHODCALLTYPE* get_AutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* add_FragmentRootAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_FragmentRootAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_NextSiblingAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_NextSiblingAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_ParentAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ParentAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_PreviousSiblingAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        __FITypedEventHandler_2_Microsoft__CUI__CContent__CIContentSiteAutomation_Microsoft__CUI__CContent__CContentSiteAutomationProviderRequestedEventArgs* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_PreviousSiblingAutomationProviderRequested)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_get_AutomationOption(This, value) \
    ((This)->lpVtbl->get_AutomationOption(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_put_AutomationOption(This, value) \
    ((This)->lpVtbl->put_AutomationOption(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_get_AutomationProvider(This, value) \
    ((This)->lpVtbl->get_AutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_add_FragmentRootAutomationProviderRequested(This, handler, token) \
    ((This)->lpVtbl->add_FragmentRootAutomationProviderRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_remove_FragmentRootAutomationProviderRequested(This, token) \
    ((This)->lpVtbl->remove_FragmentRootAutomationProviderRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_add_NextSiblingAutomationProviderRequested(This, handler, token) \
    ((This)->lpVtbl->add_NextSiblingAutomationProviderRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_remove_NextSiblingAutomationProviderRequested(This, token) \
    ((This)->lpVtbl->remove_NextSiblingAutomationProviderRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_add_ParentAutomationProviderRequested(This, handler, token) \
    ((This)->lpVtbl->add_ParentAutomationProviderRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_remove_ParentAutomationProviderRequested(This, token) \
    ((This)->lpVtbl->remove_ParentAutomationProviderRequested(This, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_add_PreviousSiblingAutomationProviderRequested(This, handler, token) \
    ((This)->lpVtbl->add_PreviousSiblingAutomationProviderRequested(This, handler, token))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_remove_PreviousSiblingAutomationProviderRequested(This, token) \
    ((This)->lpVtbl->remove_PreviousSiblingAutomationProviderRequested(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.IContentSiteAutomationProviderRequestedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        IInspectable** value);
    HRESULT (STDMETHODCALLTYPE* put_AutomationProvider)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        IInspectable* value);
    HRESULT (STDMETHODCALLTYPE* get_Handled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_Handled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_get_AutomationProvider(This, value) \
    ((This)->lpVtbl->get_AutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_put_AutomationProvider(This, value) \
    ((This)->lpVtbl->put_AutomationProvider(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_get_Handled(This, value) \
    ((This)->lpVtbl->get_Handled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_put_Handled(This, value) \
    ((This)->lpVtbl->put_Handled(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Any object which implements this interface must also implement the following interfaces:
 *     Windows.Foundation.IClosable
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteBridge[] = L"Microsoft.UI.Content.IContentSiteBridge";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* get_LayoutDirectionOverride)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection** value);
    HRESULT (STDMETHODCALLTYPE* put_LayoutDirectionOverride)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        __FIReference_1_Microsoft__CUI__CContent__CContentLayoutDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_OverrideScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_OverrideScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge* This,
        FLOAT value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridgeVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_get_LayoutDirectionOverride(This, value) \
    ((This)->lpVtbl->get_LayoutDirectionOverride(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_put_LayoutDirectionOverride(This, value) \
    ((This)->lpVtbl->put_LayoutDirectionOverride(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_get_OverrideScale(This, value) \
    ((This)->lpVtbl->get_OverrideScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_put_OverrideScale(This, value) \
    ((This)->lpVtbl->put_OverrideScale(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironment[] = L"Microsoft.UI.Content.IContentSiteEnvironment";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AppWindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* put_AppWindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId value);
    HRESULT (STDMETHODCALLTYPE* get_DisplayId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId* value);
    HRESULT (STDMETHODCALLTYPE* put_DisplayId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId value);
    HRESULT (STDMETHODCALLTYPE* get_View)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView** value);
    HRESULT (STDMETHODCALLTYPE* NotifySettingChanged)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment* This,
        HSTRING setting);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_get_AppWindowId(This, value) \
    ((This)->lpVtbl->get_AppWindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_put_AppWindowId(This, value) \
    ((This)->lpVtbl->put_AppWindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_get_DisplayId(This, value) \
    ((This)->lpVtbl->get_DisplayId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_put_DisplayId(This, value) \
    ((This)->lpVtbl->put_DisplayId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_get_View(This, value) \
    ((This)->lpVtbl->get_View(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_NotifySettingChanged(This, setting) \
    ((This)->lpVtbl->NotifySettingChanged(This, setting))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironment2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironment2[] = L"Microsoft.UI.Content.IContentSiteEnvironment2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DisplayScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* put_DisplayScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2* This,
        FLOAT value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_get_DisplayScale(This, value) \
    ((This)->lpVtbl->get_DisplayScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_put_DisplayScale(This, value) \
    ((This)->lpVtbl->put_DisplayScale(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironment2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironment
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentFactory[] = L"Microsoft.UI.Content.IContentSiteEnvironmentFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentView[] = L"Microsoft.UI.Content.IContentSiteEnvironmentView";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AppWindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* get_DisplayId)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView* This,
        struct __x_ABI_CMicrosoft_CUI_CDisplayId* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_get_AppWindowId(This, value) \
    ((This)->lpVtbl->get_AppWindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_get_DisplayId(This, value) \
    ((This)->lpVtbl->get_DisplayId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentView2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentView2[] = L"Microsoft.UI.Content.IContentSiteEnvironmentView2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DisplayScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2* This,
        FLOAT* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_get_DisplayScale(This, value) \
    ((This)->lpVtbl->get_DisplayScale(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteEnvironmentViewFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteEnvironmentViewFactory[] = L"Microsoft.UI.Content.IContentSiteEnvironmentViewFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentViewFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSite
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteFactory[] = L"Microsoft.UI.Content.IContentSiteFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteInput
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteInput[] = L"Microsoft.UI.Content.IContentSiteInput";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInputVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesKeyboardInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ProcessesKeyboardInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesPointerInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_ProcessesPointerInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput* This,
        boolean value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInputVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInputVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_get_ProcessesKeyboardInput(This, value) \
    ((This)->lpVtbl->get_ProcessesKeyboardInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_put_ProcessesKeyboardInput(This, value) \
    ((This)->lpVtbl->put_ProcessesKeyboardInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_get_ProcessesPointerInput(This, value) \
    ((This)->lpVtbl->get_ProcessesPointerInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_put_ProcessesPointerInput(This, value) \
    ((This)->lpVtbl->put_ProcessesPointerInput(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteInput_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteLink
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteLink[] = L"Microsoft.UI.Content.IContentSiteLink";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLinkVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Parent)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLinkVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLinkVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_get_Parent(This, value) \
    ((This)->lpVtbl->get_Parent(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteLink_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteRequestedStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteRequestedStateChangedEventArgs[] = L"Microsoft.UI.Content.IContentSiteRequestedStateChangedEventArgs";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_DidRequestedSizeChange)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_get_DidRequestedSizeChange(This, value) \
    ((This)->lpVtbl->get_DidRequestedSizeChange(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteRequestedStateChangedEventArgs_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteView[] = L"Microsoft.UI.Content.IContentSiteView";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ActualSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2* value);
    HRESULT (STDMETHODCALLTYPE* get_ClientSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        struct __x_ABI_CWindows_CGraphics_CSizeInt32* value);
    HRESULT (STDMETHODCALLTYPE* get_CoordinateConverter)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentCoordinateConverter** value);
    HRESULT (STDMETHODCALLTYPE* get_DispatcherQueue)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue** value);
    HRESULT (STDMETHODCALLTYPE* get_EnvironmentView)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteEnvironmentView** value);
    HRESULT (STDMETHODCALLTYPE* get_IsConnected)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsSiteEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsSiteVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_LayoutDirection)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentLayoutDirection* value);
    HRESULT (STDMETHODCALLTYPE* get_OverrideScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_ParentScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_RasterizationScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        FLOAT* value);
    HRESULT (STDMETHODCALLTYPE* get_RequestedSize)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CVector2* value);
    HRESULT (STDMETHODCALLTYPE* get_ShouldApplyRasterizationScale)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_ActualSize(This, value) \
    ((This)->lpVtbl->get_ActualSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_ClientSize(This, value) \
    ((This)->lpVtbl->get_ClientSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_CoordinateConverter(This, value) \
    ((This)->lpVtbl->get_CoordinateConverter(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_DispatcherQueue(This, value) \
    ((This)->lpVtbl->get_DispatcherQueue(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_EnvironmentView(This, value) \
    ((This)->lpVtbl->get_EnvironmentView(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_IsConnected(This, value) \
    ((This)->lpVtbl->get_IsConnected(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_IsSiteEnabled(This, value) \
    ((This)->lpVtbl->get_IsSiteEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_IsSiteVisible(This, value) \
    ((This)->lpVtbl->get_IsSiteVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_LayoutDirection(This, value) \
    ((This)->lpVtbl->get_LayoutDirection(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_OverrideScale(This, value) \
    ((This)->lpVtbl->get_OverrideScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_ParentScale(This, value) \
    ((This)->lpVtbl->get_ParentScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_RasterizationScale(This, value) \
    ((This)->lpVtbl->get_RasterizationScale(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_RequestedSize(This, value) \
    ((This)->lpVtbl->get_RequestedSize(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_get_ShouldApplyRasterizationScale(This, value) \
    ((This)->lpVtbl->get_ShouldApplyRasterizationScale(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteView2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteView2[] = L"Microsoft.UI.Content.IContentSiteView2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_LocalToClientTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* get_LocalToParentTransformMatrix)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        struct __x_ABI_CWindows_CFoundation_CNumerics_CMatrix4x4* value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesKeyboardInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ProcessesPointerInput)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_get_LocalToClientTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToClientTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_get_LocalToParentTransformMatrix(This, value) \
    ((This)->lpVtbl->get_LocalToParentTransformMatrix(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_get_ProcessesKeyboardInput(This, value) \
    ((This)->lpVtbl->get_ProcessesKeyboardInput(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_get_ProcessesPointerInput(This, value) \
    ((This)->lpVtbl->get_ProcessesPointerInput(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteViewAutomation
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteViewAutomation[] = L"Microsoft.UI.Content.IContentSiteViewAutomation";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomationVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AutomationOption)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentAutomationOptions* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomationVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomationVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_get_AutomationOption(This, value) \
    ((This)->lpVtbl->get_AutomationOption(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewAutomation_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IContentSiteViewFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.ContentSiteView
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IContentSiteViewFactory[] = L"Microsoft.UI.Content.IContentSiteViewFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIContentSiteViewFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopAttachedSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopAttachedSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopAttachedSiteBridge[] = L"Microsoft.UI.Content.IDesktopAttachedSiteBridge";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SiteView)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView** value);
    HRESULT (STDMETHODCALLTYPE* get_WindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* Connect)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* content);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_get_SiteView(This, value) \
    ((This)->lpVtbl->get_SiteView(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_get_WindowId(This, value) \
    ((This)->lpVtbl->get_WindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_Connect(This, content) \
    ((This)->lpVtbl->Connect(This, content))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopAttachedSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopAttachedSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopAttachedSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopAttachedSiteBridgeStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateFromWindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* queue,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridge** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_CreateFromWindowId(This, queue, windowId, result) \
    ((This)->lpVtbl->CreateFromWindowId(This, queue, windowId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopAttachedSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopChildSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopChildSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopChildSiteBridge[] = L"Microsoft.UI.Content.IDesktopChildSiteBridge";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ResizePolicy)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentSizePolicy* value);
    HRESULT (STDMETHODCALLTYPE* put_ResizePolicy)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        enum __x_ABI_CMicrosoft_CUI_CContent_CContentSizePolicy value);
    HRESULT (STDMETHODCALLTYPE* get_SiteView)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_get_ResizePolicy(This, value) \
    ((This)->lpVtbl->get_ResizePolicy(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_put_ResizePolicy(This, value) \
    ((This)->lpVtbl->put_ResizePolicy(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_get_SiteView(This, value) \
    ((This)->lpVtbl->get_SiteView(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopChildSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopChildSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopChildSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopChildSiteBridgeStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics* This,
        __x_ABI_CMicrosoft_CUI_CComposition_CICompositor* compositor,
        struct __x_ABI_CMicrosoft_CUI_CWindowId parentWindowId,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_Create(This, compositor, parentWindowId, result) \
    ((This)->lpVtbl->Create(This, compositor, parentWindowId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopChildSiteBridgeStatics2
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopChildSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopChildSiteBridgeStatics2[] = L"Microsoft.UI.Content.IDesktopChildSiteBridgeStatics2";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2Vtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateWithDispatcherQueue)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2* This,
        __x_ABI_CMicrosoft_CUI_CDispatching_CIDispatcherQueue* queue,
        struct __x_ABI_CMicrosoft_CUI_CWindowId parentWindowId,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridge** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2Vtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2Vtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_CreateWithDispatcherQueue(This, queue, parentWindowId, result) \
    ((This)->lpVtbl->CreateWithDispatcherQueue(This, queue, parentWindowId, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopChildSiteBridgeStatics2_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopPopupSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopPopupSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopPopupSiteBridge[] = L"Microsoft.UI.Content.IDesktopPopupSiteBridge";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_SiteView)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentSiteView** value);
    HRESULT (STDMETHODCALLTYPE* get_WindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* Connect)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* content);
    HRESULT (STDMETHODCALLTYPE* Disable)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* Enable)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* Hide)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* MoveAndResize)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 rect);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderAtBottom)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderAtTop)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderBelow)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId);
    HRESULT (STDMETHODCALLTYPE* Show)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_get_IsEnabled(This, value) \
    ((This)->lpVtbl->get_IsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_get_IsVisible(This, value) \
    ((This)->lpVtbl->get_IsVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_get_SiteView(This, value) \
    ((This)->lpVtbl->get_SiteView(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_get_WindowId(This, value) \
    ((This)->lpVtbl->get_WindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_Connect(This, content) \
    ((This)->lpVtbl->Connect(This, content))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_Disable(This) \
    ((This)->lpVtbl->Disable(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_Enable(This) \
    ((This)->lpVtbl->Enable(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_Hide(This) \
    ((This)->lpVtbl->Hide(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_MoveAndResize(This, rect) \
    ((This)->lpVtbl->MoveAndResize(This, rect))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_MoveInZOrderAtBottom(This) \
    ((This)->lpVtbl->MoveInZOrderAtBottom(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_MoveInZOrderAtTop(This) \
    ((This)->lpVtbl->MoveInZOrderAtTop(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_MoveInZOrderBelow(This, windowId) \
    ((This)->lpVtbl->MoveInZOrderBelow(This, windowId))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_Show(This) \
    ((This)->lpVtbl->Show(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopPopupSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopPopupSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopPopupSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopPopupSiteBridgeStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Create)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* parent,
        __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridge** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_Create(This, parent, result) \
    ((This)->lpVtbl->Create(This, parent, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopPopupSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Interface Microsoft.UI.Content.IDesktopSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopSiteBridge[] = L"Microsoft.UI.Content.IDesktopSiteBridge";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsEnabled)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_IsVisible)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_WindowId)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId* value);
    HRESULT (STDMETHODCALLTYPE* Connect)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        __x_ABI_CMicrosoft_CUI_CContent_CIContentIsland* content);
    HRESULT (STDMETHODCALLTYPE* Disable)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* Enable)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* Hide)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* MoveAndResize)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        struct __x_ABI_CWindows_CGraphics_CRectInt32 rect);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderAtBottom)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderAtTop)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);
    HRESULT (STDMETHODCALLTYPE* MoveInZOrderBelow)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This,
        struct __x_ABI_CMicrosoft_CUI_CWindowId windowId);
    HRESULT (STDMETHODCALLTYPE* Show)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge* This);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_get_IsEnabled(This, value) \
    ((This)->lpVtbl->get_IsEnabled(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_get_IsVisible(This, value) \
    ((This)->lpVtbl->get_IsVisible(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_get_WindowId(This, value) \
    ((This)->lpVtbl->get_WindowId(This, value))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_Connect(This, content) \
    ((This)->lpVtbl->Connect(This, content))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_Disable(This) \
    ((This)->lpVtbl->Disable(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_Enable(This) \
    ((This)->lpVtbl->Enable(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_Hide(This) \
    ((This)->lpVtbl->Hide(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_MoveAndResize(This, rect) \
    ((This)->lpVtbl->MoveAndResize(This, rect))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_MoveInZOrderAtBottom(This) \
    ((This)->lpVtbl->MoveInZOrderAtBottom(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_MoveInZOrderAtTop(This) \
    ((This)->lpVtbl->MoveInZOrderAtTop(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_MoveInZOrderBelow(This, windowId) \
    ((This)->lpVtbl->MoveInZOrderBelow(This, windowId))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_Show(This) \
    ((This)->lpVtbl->Show(This))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridge_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopSiteBridgeFactory
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopSiteBridgeFactory[] = L"Microsoft.UI.Content.IDesktopSiteBridgeFactory";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactoryVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Interface Microsoft.UI.Content.IDesktopSiteBridgeStatics
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Interface is a part of the implementation of type Microsoft.UI.Content.DesktopSiteBridge
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#if !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_UI_Content_IDesktopSiteBridgeStatics[] = L"Microsoft.UI.Content.IDesktopSiteBridgeStatics";
typedef struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* IsSupported)(__x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics* This,
        boolean* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStaticsVtbl;

interface __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_IsSupported(This, result) \
    ((This)->lpVtbl->IsSupported(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CUI_CContent_CIDesktopSiteBridgeStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ChildSiteLink
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IChildSiteLinkStatics interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IChildSiteLink ** Default Interface **
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteAutomation
 *    Microsoft.UI.Content.IContentSiteInput
 *    Microsoft.UI.Content.IContentSiteLink
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ChildSiteLink_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ChildSiteLink_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ChildSiteLink[] = L"Microsoft.UI.Content.ChildSiteLink";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.ContentCoordinateConverter
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IContentCoordinateConverterStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentCoordinateConverter ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentCoordinateConverter_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentCoordinateConverter_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentCoordinateConverter[] = L"Microsoft.UI.Content.ContentCoordinateConverter";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentDeferral
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentDeferral ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentDeferral_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentDeferral_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentDeferral[] = L"Microsoft.UI.Content.ContentDeferral";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentEnvironmentSettingChangedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentSettingChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentSettingChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentEnvironmentSettingChangedEventArgs[] = L"Microsoft.UI.Content.ContentEnvironmentSettingChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs ** Default Interface **
 *    Microsoft.UI.Content.IContentEnvironmentStateChangedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentStateChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentEnvironmentStateChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentEnvironmentStateChangedEventArgs[] = L"Microsoft.UI.Content.ContentEnvironmentStateChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIsland
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IContentIslandStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Content.IContentIslandStatics2 interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIsland ** Default Interface **
 *    Microsoft.UI.Content.IContentIsland2
 *    Microsoft.UI.Content.IContentIslandAutomation
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Composition.ICompositionSupportsSystemBackdrop
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIsland_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIsland_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIsland[] = L"Microsoft.UI.Content.ContentIsland";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIslandAutomationProviderRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIslandAutomationProviderRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIslandAutomationProviderRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIslandAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.ContentIslandAutomationProviderRequestedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIslandEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIslandEnvironment ** Default Interface **
 *    Microsoft.UI.Content.IContentIslandEnvironment2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIslandEnvironment_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIslandEnvironment_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIslandEnvironment[] = L"Microsoft.UI.Content.ContentIslandEnvironment";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentIslandStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentIslandStateChangedEventArgs ** Default Interface **
 *    Microsoft.UI.Content.IContentIslandStateChangedEventArgs2
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentIslandStateChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentIslandStateChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentIslandStateChangedEventArgs[] = L"Microsoft.UI.Content.ContentIslandStateChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSite
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSite ** Default Interface **
 *    Microsoft.UI.Content.IContentSite2
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSite_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSite_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSite[] = L"Microsoft.UI.Content.ContentSite";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteAutomationProviderRequestedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteAutomationProviderRequestedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteAutomationProviderRequestedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteAutomationProviderRequestedEventArgs[] = L"Microsoft.UI.Content.ContentSiteAutomationProviderRequestedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.ContentSiteEnvironment
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteEnvironment ** Default Interface **
 *    Microsoft.UI.Content.IContentSiteEnvironment2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironment_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironment_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteEnvironment[] = L"Microsoft.UI.Content.ContentSiteEnvironment";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteEnvironmentView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteEnvironmentView ** Default Interface **
 *    Microsoft.UI.Content.IContentSiteEnvironmentView2
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironmentView_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteEnvironmentView_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteEnvironmentView[] = L"Microsoft.UI.Content.ContentSiteEnvironmentView";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteRequestedStateChangedEventArgs ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteRequestedStateChangedEventArgs_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteRequestedStateChangedEventArgs_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteRequestedStateChangedEventArgs[] = L"Microsoft.UI.Content.ContentSiteRequestedStateChangedEventArgs";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.ContentSiteView
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IContentSiteView ** Default Interface **
 *    Microsoft.UI.Content.IContentSiteView2
 *    Microsoft.UI.Content.IContentSiteViewAutomation
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_ContentSiteView_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_ContentSiteView_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_ContentSiteView[] = L"Microsoft.UI.Content.ContentSiteView";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.DesktopAttachedSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopAttachedSiteBridgeStatics interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopAttachedSiteBridge ** Default Interface **
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteBridge
 *    Microsoft.UI.Content.IContentSiteInput
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopAttachedSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopAttachedSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopAttachedSiteBridge[] = L"Microsoft.UI.Content.DesktopAttachedSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.DesktopChildSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopChildSiteBridgeStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopChildSiteBridgeStatics2 interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopChildSiteBridge ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopChildSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopChildSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopChildSiteBridge[] = L"Microsoft.UI.Content.DesktopChildSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

/*
 *
 * Class Microsoft.UI.Content.DesktopPopupSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.7
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopPopupSiteBridgeStatics interface starting with version 1.7 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopPopupSiteBridge ** Default Interface **
 *    Windows.Foundation.IClosable
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteAutomation
 *    Microsoft.UI.Content.IContentSiteBridge
 *    Microsoft.UI.Content.IContentSiteLink
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopPopupSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopPopupSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopPopupSiteBridge[] = L"Microsoft.UI.Content.DesktopPopupSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10007

/*
 *
 * Class Microsoft.UI.Content.DesktopSiteBridge
 *
 * Introduced to Microsoft.Foundation.WindowsAppSDKContract in version 1.4
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.UI.Content.IDesktopSiteBridgeStatics interface starting with version 1.4 of the Microsoft.Foundation.WindowsAppSDKContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.UI.Content.IDesktopSiteBridge ** Default Interface **
 *    Microsoft.UI.IClosableNotifier
 *    Microsoft.UI.Content.IContentSiteBridge
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004
#ifndef RUNTIMECLASS_Microsoft_UI_Content_DesktopSiteBridge_DEFINED
#define RUNTIMECLASS_Microsoft_UI_Content_DesktopSiteBridge_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_UI_Content_DesktopSiteBridge[] = L"Microsoft.UI.Content.DesktopSiteBridge";
#endif
#endif // MICROSOFT_FOUNDATION_WINDOWSAPPSDKCONTRACT_VERSION >= 0x10004

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Eui2Econtent_p_h__

#endif // __microsoft2Eui2Econtent_h__
