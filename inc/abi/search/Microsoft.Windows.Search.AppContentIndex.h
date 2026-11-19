
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
#ifndef __microsoft2Ewindows2Esearch2Eappcontentindex_h__
#define __microsoft2Ewindows2Esearch2Eappcontentindex_h__
#ifndef __microsoft2Ewindows2Esearch2Eappcontentindex_p_h__
#define __microsoft2Ewindows2Esearch2Eappcontentindex_p_h__


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
#if !defined(MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION)
#define MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION 0x30000
#endif // defined(MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)
#define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
#endif // defined(WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION)

#if !defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)
#define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x140000
#endif // defined(WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION)

#endif // defined(SPECIFIC_API_CONTRACT_DEFINITIONS)


// Header files for imported files
#include "inspectable.h"
#include "AsyncInfo.h"
#include "EventToken.h"
#include "windowscontracts.h"
#include "Windows.Foundation.h"
#include "Windows.Graphics.Imaging.h"
#include "Windows.Storage.Streams.h"
// Importing Collections header
#include <windows.foundation.collections.h>

#if defined(__cplusplus) && !defined(CINTERFACE)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppContentIndexListener;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexListener

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppContentIndexer;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexer

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppContentIndexerStatics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexerStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexContentRegion;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexContentRegionStatics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegionStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexImageQuery;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuery

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexImageQuerySession;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuerySession

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexImageQuerySessionStatics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuerySessionStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexQueryMatch

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexQueryMatchFactory;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexQueryMatchFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexTextQuery;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuery

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexTextQuerySession;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuerySession

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppIndexTextQuerySessionStatics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuerySessionStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppManagedImageQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedImageQueryMatch

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppManagedIndexableAppContent;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppManagedIndexableAppContentStatics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContentStatics

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppManagedOcrTextQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedOcrTextQueryMatch

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IAppManagedTextQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedTextQueryMatch

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IContentItemReader;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemReader

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IContentItemStatusResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IContentRegionImageOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionImageOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IContentRegionTextOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionTextOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IDeleteIndexResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult ABI::Microsoft::Windows::Search::AppContentIndex::IDeleteIndexResult

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IGetOrCreateIndexOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions ABI::Microsoft::Windows::Search::AppContentIndex::IGetOrCreateIndexOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IGetOrCreateIndexResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult ABI::Microsoft::Windows::Search::AppContentIndex::IGetOrCreateIndexResult

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IImageQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryMatch

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IImageQueryMatchFactory;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryMatchFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IImageQueryOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IImageQuerySessionResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult ABI::Microsoft::Windows::Search::AppContentIndex::IImageQuerySessionResult

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IIndexCapabilities;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilities

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IIndexCapabilitiesOfCurrentSystem;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilitiesOfCurrentSystem

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IIndexCapabilityState;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilityState

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IIndexStatistics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics ABI::Microsoft::Windows::Search::AppContentIndex::IIndexStatistics

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IIndexableAppContent;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent ABI::Microsoft::Windows::Search::AppContentIndex::IIndexableAppContent

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface IIndexableAppContentFactory;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory ABI::Microsoft::Windows::Search::AppContentIndex::IIndexableAppContentFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface ITextQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryMatch

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface ITextQueryMatchFactory;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryMatchFactory

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface ITextQueryOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryOptions

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_FWD_DEFINED__
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    interface ITextQuerySessionResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult ABI::Microsoft::Windows::Search::AppContentIndex::ITextQuerySessionResult

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_FWD_DEFINED__

// Parameterized interface forward declarations (C++)

// Collection interface definitions

#ifndef DEF___FIAsyncOperation_1_boolean_USE
#define DEF___FIAsyncOperation_1_boolean_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("cdb5efb3-5788-509d-9be1-71ccb8a3362a"))
IAsyncOperation<bool> : IAsyncOperation_impl<ABI::Windows::Foundation::Internal::AggregateType<bool, boolean>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperation`1<Boolean>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperation<bool> __FIAsyncOperation_1_boolean_t;
#define __FIAsyncOperation_1_boolean ABI::Windows::Foundation::__FIAsyncOperation_1_boolean_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperation_1_boolean_USE */



#ifndef DEF___FIAsyncOperationCompletedHandler_1_boolean_USE
#define DEF___FIAsyncOperationCompletedHandler_1_boolean_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("c1d3d1a2-ae17-5a5f-b5a2-bdcc8844889a"))
IAsyncOperationCompletedHandler<bool> : IAsyncOperationCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<bool, boolean>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationCompletedHandler`1<Boolean>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationCompletedHandler<bool> __FIAsyncOperationCompletedHandler_1_boolean_t;
#define __FIAsyncOperationCompletedHandler_1_boolean ABI::Windows::Foundation::__FIAsyncOperationCompletedHandler_1_boolean_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationCompletedHandler_1_boolean_USE */


namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class IndexCapabilities;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE
#define DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("e34c6a54-87ff-5ce9-bb27-4c27ab82a50f"))
IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, double> : IAsyncOperationWithProgressCompletedHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilities*>, double>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<Microsoft.Windows.Search.AppContentIndex.IndexCapabilities, Double>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgressCompletedHandler<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, double> __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_t;
#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double ABI::Windows::Foundation::__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE
#define DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("433b8a9d-4316-521a-8bc6-c024044d533e"))
IAsyncOperationWithProgress<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, double> : IAsyncOperationWithProgress_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilities*>, double>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IAsyncOperationWithProgress`2<Microsoft.Windows.Search.AppContentIndex.IndexCapabilities, Double>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationWithProgress<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, double> __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_t;
#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double ABI::Windows::Foundation::__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE
#define DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("12c7d92c-28c9-57cf-bde8-c98d36cc3c40"))
IAsyncOperationProgressHandler<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, double> : IAsyncOperationProgressHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilities*>, double>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.AsyncOperationProgressHandler`2<Microsoft.Windows.Search.AppContentIndex.IndexCapabilities, Double>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IAsyncOperationProgressHandler<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, double> __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_t;
#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double ABI::Windows::Foundation::__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppIndexContentRegion;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("c7ce71f5-a020-546d-8c56-9ef6ef73d7b2"))
IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*> __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_t;
#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("93160f4a-db23-5984-98ae-a90a61bc9866"))
IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*> __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_t;
#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ContentItemStatusResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ec075dc5-836b-5907-a18e-8f7e9993a825"))
IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*, ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("9ac44eef-9bc2-5b75-abdf-46a8747f7b84"))
IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*, ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ImageQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("5e398c6c-9c51-59a8-8930-b9777fa1554d"))
IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*, ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryMatch*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*> __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_t;
#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("1e567795-5ef1-509a-ac82-c2063968607a"))
IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*, ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryMatch*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*> __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_t;
#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum IndexCapability : int IndexCapability;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("58a2f3f6-2cb8-53ff-9dd7-9ce434e9ad6b"))
IIterator<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability> : IIterator_impl<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Search.AppContentIndex.IndexCapability>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability> __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_t;
#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("761f44fe-4c76-5245-9d4e-cdc9c4e5c962"))
IIterable<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability> : IIterable_impl<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Search.AppContentIndex.IndexCapability>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability> __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_t;
#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class TextQueryMatch;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE
#define DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e37c07cf-1a5a-5a9c-a615-fde85e1a9775"))
IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*> : IIterator_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*, ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryMatch*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Microsoft.Windows.Search.AppContentIndex.TextQueryMatch>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*> __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_t;
#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch ABI::Windows::Foundation::Collections::__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE
#define DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("7d5155be-affe-558e-95f5-70e3e19584f9"))
IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*> : IIterable_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*, ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryMatch*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Microsoft.Windows.Search.AppContentIndex.TextQueryMatch>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*> __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_t;
#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch ABI::Windows::Foundation::Collections::__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000


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


#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("df656fd0-6cf4-5eee-9ba6-209a63f696da"))
IKeyValuePair<HSTRING, ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> : IKeyValuePair_impl<HSTRING, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*, ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IKeyValuePair<HSTRING, ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("29293bcf-806b-5840-ba1b-b85f15d55522"))
IIterator<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*> : IIterator_impl<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterator`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterator<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*> __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("cefb4e92-be07-55f3-85b3-69473c767985"))
IIterable<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*> : IIterable_impl<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IIterable`1<Windows.Foundation.Collections.IKeyValuePair`2<String, Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IIterable<__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*> __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("e58aae44-572b-512a-8b9b-6693bb77d078"))
IMapView<HSTRING, ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> : IMapView_impl<HSTRING, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*, ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IMapView`2<String, Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IMapView<HSTRING, ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("ed469f87-8e3e-5602-87bb-1b4a22f7e2d5"))
IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexContentRegion*> __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_t;
#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("93bbb356-9fce-50c8-abfb-03fc67572fdb"))
IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*, ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatusResult*> __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("b5d4a088-e1a1-512d-80c7-b5ce8da6a6f6"))
IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*, ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryMatch*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::ImageQueryMatch*> __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_t;
#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("988a9604-8f1f-5057-8a61-067475b2e3e2"))
IVectorView<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability> : IVectorView_impl<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Search.AppContentIndex.IndexCapability>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<enum ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability> __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_t;
#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE
#define DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation { namespace Collections {
template <>
struct __declspec(uuid("a9766377-df07-5331-9a34-19fd55a02915"))
IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*> : IVectorView_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*, ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryMatch*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.Collections.IVectorView`1<Microsoft.Windows.Search.AppContentIndex.TextQueryMatch>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IVectorView<ABI::Microsoft::Windows::Search::AppContentIndex::TextQueryMatch*> __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_t;
#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch ABI::Windows::Foundation::Collections::__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_t
/* Collections */ } /* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000


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


namespace ABI {
    namespace Windows {
        namespace Foundation {
            typedef struct Rect Rect;
        } /* Foundation */
    } /* Windows */
} /* ABI */

#if WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION >= 0x10000

#ifndef DEF___FIReference_1_Windows__CFoundation__CRect_USE
#define DEF___FIReference_1_Windows__CFoundation__CRect_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("80423f11-054f-5eac-afd3-63b6ce15e77b"))
IReference<struct ABI::Windows::Foundation::Rect> : IReference_impl<struct ABI::Windows::Foundation::Rect>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.IReference`1<Windows.Foundation.Rect>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef IReference<struct ABI::Windows::Foundation::Rect> __FIReference_1_Windows__CFoundation__CRect_t;
#define __FIReference_1_Windows__CFoundation__CRect ABI::Windows::Foundation::__FIReference_1_Windows__CFoundation__CRect_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FIReference_1_Windows__CFoundation__CRect_USE */

#endif // WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppContentIndexer;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("836c723a-64c1-5085-b1c4-ff00df2fd0bd"))
ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexer*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*, ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilities*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.Search.AppContentIndex.AppContentIndexer, Microsoft.Windows.Search.AppContentIndex.IndexCapabilities>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilities*> __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class IndexStatistics;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("362f8b07-b78b-5f14-9b7d-7485f642c692"))
ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IndexStatistics*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexer*>, ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::IndexStatistics*, ABI::Microsoft::Windows::Search::AppContentIndex::IIndexStatistics*>>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.Search.AppContentIndex.AppContentIndexer, Microsoft.Windows.Search.AppContentIndex.IndexStatistics>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IndexStatistics*> __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("cc4f2e5d-5f66-514c-b224-1c02bd68950f"))
ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexer*>, __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.Search.AppContentIndex.AppContentIndexer, Windows.Foundation.Collections.IMapView`2<String, Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult>>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppContentIndexer*, __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult*> __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppIndexImageQuerySession;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("d49b6723-f16f-5942-9656-2094ffd01fc4"))
ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexImageQuerySession*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexImageQuerySession*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuerySession*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexImageQuerySession*, IInspectable*> __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppIndexTextQuerySession;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_USE
#define DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_USE
#if !defined(RO_NO_TEMPLATE_NAME)
namespace ABI { namespace Windows { namespace Foundation {
template <>
struct __declspec(uuid("64179e18-f369-5fde-afd3-1dad9c97bdf1"))
ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextQuerySession*, IInspectable*> : ITypedEventHandler_impl<ABI::Windows::Foundation::Internal::AggregateType<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextQuerySession*, ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuerySession*>, IInspectable*>
{
    static const wchar_t* z_get_rc_name_impl()
    {
        return L"Windows.Foundation.TypedEventHandler`2<Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession, Object>";
    }
};
// Define a typedef for the parameterized interface specialization's mangled name.
// This allows code which uses the mangled name for the parameterized interface to access the
// correct parameterized interface specialization.
typedef ITypedEventHandler<ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextQuerySession*, IInspectable*> __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_t;
#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable ABI::Windows::Foundation::__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_t
/* Foundation */ } /* Windows */ } /* ABI */ }

#endif // !defined(RO_NO_TEMPLATE_NAME)
#endif /* DEF___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_USE */

#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

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
            typedef struct TimeSpan TimeSpan;
        } /* Foundation */
    } /* Windows */
} /* ABI */

namespace ABI {
    namespace Windows {
        namespace Graphics {
            namespace Imaging {
                class SoftwareBitmap;
            } /* Imaging */
        } /* Graphics */
    } /* Windows */
} /* ABI */

#ifndef ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Graphics {
            namespace Imaging {
                interface ISoftwareBitmap;
            } /* Imaging */
        } /* Graphics */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap ABI::Windows::Graphics::Imaging::ISoftwareBitmap

#endif // ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_FWD_DEFINED__
namespace ABI {
    namespace Windows {
        namespace Storage {
            namespace Streams {
                interface IInputStream;
            } /* Streams */
        } /* Storage */
    } /* Windows */
} /* ABI */
#define __x_ABI_CWindows_CStorage_CStreams_CIInputStream ABI::Windows::Storage::Streams::IInputStream

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_FWD_DEFINED__

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum AppIndexTextStreamEncoding : int AppIndexTextStreamEncoding;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum ContentItemErrorDetail : int ContentItemErrorDetail;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum ContentItemReindexingStatus : int ContentItemReindexingStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum ContentItemStatus : int ContentItemStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum DeleteIndexStatus : int DeleteIndexStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum DeleteIndexWhileInUseBehavior : int DeleteIndexWhileInUseBehavior;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum GetOrCreateIndexStatus : int GetOrCreateIndexStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum ImageOcrIndexingOptions : int ImageOcrIndexingOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum IndexCapabilityInitializationStatus : int IndexCapabilityInitializationStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum IndexCapabilityLanguageStatus : int IndexCapabilityLanguageStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum IndexCapabilityOfCurrentSystemStatus : int IndexCapabilityOfCurrentSystemStatus;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum IndexCapabilityRequirement : int IndexCapabilityRequirement;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum QueryContentItemsFilterFlags : unsigned int QueryContentItemsFilterFlags;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum QueryMatchContentKind : int QueryMatchContentKind;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum QueryMatchScope : int QueryMatchScope;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum RegionContentKind : int RegionContentKind;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    typedef enum TextLexicalMatchType : int TextLexicalMatchType;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppContentIndexListener;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppIndexImageQuery;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppIndexTextQuery;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class AppManagedIndexableAppContent;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ContentItemReader;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ContentRegionImageOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ContentRegionTextOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class DeleteIndexResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class GetOrCreateIndexOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class GetOrCreateIndexResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ImageQueryOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class ImageQuerySessionResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class IndexCapabilitiesOfCurrentSystem;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class IndexCapabilityState;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class IndexableAppContent;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class TextQueryOptions;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    class TextQuerySessionResult;
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.AppIndexTextStreamEncoding
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum AppIndexTextStreamEncoding : int
                    {
                        AppIndexTextStreamEncoding_Utf8 = 0,
                        AppIndexTextStreamEncoding_Utf16_LE = 1,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ContentItemErrorDetail
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum ContentItemErrorDetail : int
                    {
                        ContentItemErrorDetail_NoError = 0,
                        ContentItemErrorDetail_UnknownFailure = 1,
                        ContentItemErrorDetail_UnknownContentId = 2,
                        ContentItemErrorDetail_ContentRegionErrors = 3,
                        ContentItemErrorDetail_IndexCorruption = 4,
                        ContentItemErrorDetail_InsufficientDiskSpace = 5,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ContentItemReindexingStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum ContentItemReindexingStatus : int
                    {
                        ContentItemReindexingStatus_None = 0,
                        ContentItemReindexingStatus_Unspecified = 1,
                        ContentItemReindexingStatus_SemanticModelChanged = 2,
                        ContentItemReindexingStatus_ContentUnavailable = 3,
                        ContentItemReindexingStatus_SchemaChanged = 4,
                        ContentItemReindexingStatus_IndexCorruption = 5,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ContentItemStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum ContentItemStatus : int
                    {
                        ContentItemStatus_NotStarted = 0,
                        ContentItemStatus_InProgress = 1,
                        ContentItemStatus_Completed = 2,
                        ContentItemStatus_CompletedWithSomeErrors = 3,
                        ContentItemStatus_Error = 4,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.DeleteIndexStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum DeleteIndexStatus : int
                    {
                        DeleteIndexStatus_Success = 0,
                        DeleteIndexStatus_IndexNotFound = 1,
                        DeleteIndexStatus_Deferred = 2,
                        DeleteIndexStatus_UnknownFailure = 100,
                        DeleteIndexStatus_IndexInUse = 101,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.DeleteIndexWhileInUseBehavior
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum DeleteIndexWhileInUseBehavior : int
                    {
                        DeleteIndexWhileInUseBehavior_FailIfInUse = 0,
                        DeleteIndexWhileInUseBehavior_DeferIfInUse = 1,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum GetOrCreateIndexStatus : int
                    {
                        GetOrCreateIndexStatus_CreatedNew = 0,
                        GetOrCreateIndexStatus_OpenedExisting = 1,
                        GetOrCreateIndexStatus_UnknownFailure = 100,
                        GetOrCreateIndexStatus_InvalidOptions = 101,
                        GetOrCreateIndexStatus_IncompatibleWithExistingOptions = 102,
                        GetOrCreateIndexStatus_UnsupportedDefaultLanguage = 103,
                        GetOrCreateIndexStatus_InvalidIndexName = 104,
                        GetOrCreateIndexStatus_DeferredDeletionFailed = 105,
                        GetOrCreateIndexStatus_LexicalModelsNotAvailable = 106,
                        GetOrCreateIndexStatus_SemanticModelsNotAvailable = 107,
                        GetOrCreateIndexStatus_OcrModelsNotAvailable = 108,
                        GetOrCreateIndexStatus_IndexIsPendingDeletion = 109,
                        GetOrCreateIndexStatus_SemanticTextIndexStoreFailure = 110,
                        GetOrCreateIndexStatus_SemanticOcrTextIndexStoreFailure = 111,
                        GetOrCreateIndexStatus_SemanticImageIndexStoreFailure = 112,
                        GetOrCreateIndexStatus_AppContentIndexerFileLockedError = 113,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ImageOcrIndexingOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum ImageOcrIndexingOptions : int
                    {
                        ImageOcrIndexingOptions_Default = 0,
                        ImageOcrIndexingOptions_SuppressSemanticIndexing = 1,
                        ImageOcrIndexingOptions_SuppressLexicalAndSemanticIndexing = 2,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapability
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum IndexCapability : int
                    {
                        IndexCapability_TextLexical = 0,
                        IndexCapability_TextSemantic = 1,
                        IndexCapability_ImageOcr = 2,
                        IndexCapability_ImageSemantic = 3,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityInitializationStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum IndexCapabilityInitializationStatus : int
                    {
                        IndexCapabilityInitializationStatus_Unknown = 0,
                        IndexCapabilityInitializationStatus_Initialized = 1,
                        IndexCapabilityInitializationStatus_Initializing = 2,
                        IndexCapabilityInitializationStatus_Suppressed = 3,
                        IndexCapabilityInitializationStatus_NotSupported = 4,
                        IndexCapabilityInitializationStatus_DisabledByPolicy = 5,
                        IndexCapabilityInitializationStatus_InitializationError = 100,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityLanguageStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum IndexCapabilityLanguageStatus : int
                    {
                        IndexCapabilityLanguageStatus_Supported = 0,
                        IndexCapabilityLanguageStatus_Partial = 1,
                        IndexCapabilityLanguageStatus_NotSupported = 2,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityOfCurrentSystemStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum IndexCapabilityOfCurrentSystemStatus : int
                    {
                        IndexCapabilityOfCurrentSystemStatus_Ready = 0,
                        IndexCapabilityOfCurrentSystemStatus_NotReady = 1,
                        IndexCapabilityOfCurrentSystemStatus_DisabledByPolicy = 2,
                        IndexCapabilityOfCurrentSystemStatus_NotSupported = 3,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityRequirement
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum IndexCapabilityRequirement : int
                    {
                        IndexCapabilityRequirement_Default = 0,
                        IndexCapabilityRequirement_Suppressed = 1,
                        IndexCapabilityRequirement_Required = 2,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.QueryContentItemsFilterFlags
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum QueryContentItemsFilterFlags : unsigned int
                    {
                        QueryContentItemsFilterFlags_NotStarted = 0x1,
                        QueryContentItemsFilterFlags_InProgress = 0x2,
                        QueryContentItemsFilterFlags_Completed = 0x4,
                        QueryContentItemsFilterFlags_WithErrors = 0x8,
                        QueryContentItemsFilterFlags_PendingDeletion = 0x10,
                        QueryContentItemsFilterFlags_RequiringReindexing = 0x20,
                    };

                    DEFINE_ENUM_FLAG_OPERATORS(QueryContentItemsFilterFlags)
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.QueryMatchContentKind
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum QueryMatchContentKind : int
                    {
                        QueryMatchContentKind_AppManagedText = 0,
                        QueryMatchContentKind_AppManagedImage = 1,
                        QueryMatchContentKind_AppManagedOcrText = 2,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.QueryMatchScope
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum QueryMatchScope : int
                    {
                        QueryMatchScope_Unconstrained = 0,
                        QueryMatchScope_Region = 1,
                        QueryMatchScope_ContentItem = 2,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.RegionContentKind
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum RegionContentKind : int
                    {
                        RegionContentKind_Text = 0,
                        RegionContentKind_Image = 1,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.TextLexicalMatchType
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    enum TextLexicalMatchType : int
                    {
                        TextLexicalMatchType_Fuzzy = 0,
                        TextLexicalMatchType_Exact = 1,
                    };
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppContentIndexListener
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppContentIndexListener
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppContentIndexListener[] = L"Microsoft.Windows.Search.AppContentIndex.IAppContentIndexListener";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("2ee89548-521d-510a-893a-1731c6fad619")
                    IAppContentIndexListener : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE add_IndexCapabilitiesChanged(
                            __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_IndexCapabilitiesChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_IndexStatisticsChanged(
                            __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_IndexStatisticsChanged(
                            EventRegistrationToken token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_ContentItemStatusChanged(
                            __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_ContentItemStatusChanged(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppContentIndexListener = _uuidof(IAppContentIndexListener);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppContentIndexer
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppContentIndexer
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppContentIndexer[] = L"Microsoft.Windows.Search.AppContentIndex.IAppContentIndexer";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("f246f681-eae8-503b-8723-b1984c8882b0")
                    IAppContentIndexer : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Listener(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexListener** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_IndexName(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetIndexCapabilities(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilities** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE WaitForIndexCapabilitiesAsync(
                            __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DefaultLanguage(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE IsContentKindSupported(
                            ABI::Microsoft::Windows::Search::AppContentIndex::RegionContentKind contentKind,
                            boolean* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE AddOrUpdate(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IIndexableAppContent* indexableContent
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateTextQuery(
                            HSTRING queryPhrase,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuery** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateTextQueryWithOptions(
                            HSTRING queryPhrase,
                            ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuery** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateImageQuery(
                            HSTRING queryPhrase,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuery** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateImageQueryWithOptions(
                            HSTRING queryPhrase,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuery** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateTextQuerySession(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexTextQuerySession** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateImageQuerySession(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexImageQuerySession** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveContentItem(
                            HSTRING contentId
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveContentItems(
                            __FIIterable_1_HSTRING* contentIds
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE RemoveAllContentItems(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE WaitForIndexingIdleAsync(
                            ABI::Windows::Foundation::TimeSpan timeout,
                            __FIAsyncOperation_1_boolean** operation
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetIndexStatistics(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IIndexStatistics** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContentItemStatus(
                            HSTRING contentId,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemStatusResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContentItemStatuses(
                            __FIIterable_1_HSTRING* contentIds,
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContentItemsRequiringReindexing(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemReader** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContentItems(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemReader** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetContentItemsWithFilter(
                            ABI::Microsoft::Windows::Search::AppContentIndex::QueryContentItemsFilterFlags filterFlags,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentItemReader** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppContentIndexer = _uuidof(IAppContentIndexer);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppContentIndexerStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppContentIndexer
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppContentIndexerStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppContentIndexerStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("a95dcaa2-4897-522d-a035-950bcb03e49f")
                    IAppContentIndexerStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetIndexCapabilitiesOfCurrentSystem(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilitiesOfCurrentSystem** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetOrCreateIndex(
                            HSTRING indexName,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IGetOrCreateIndexResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetOrCreateIndexWithOptions(
                            HSTRING indexName,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IGetOrCreateIndexOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IGetOrCreateIndexResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE DeleteIndex(
                            HSTRING indexName,
                            ABI::Microsoft::Windows::Search::AppContentIndex::DeleteIndexWhileInUseBehavior deleteIndexWhileInUseBehavior,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IDeleteIndexResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetExistingIndexes(
                            __FIVectorView_1_HSTRING** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppContentIndexerStatics = _uuidof(IAppContentIndexerStatics);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegion
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexContentRegion[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegion";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("b8f55ac8-35cb-5dec-b89e-39ed81907d23")
                    IAppIndexContentRegion : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RegionId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContentKind(
                            ABI::Microsoft::Windows::Search::AppContentIndex::RegionContentKind* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexContentRegion = _uuidof(IAppIndexContentRegion);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegionStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexContentRegionStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegionStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("9529149a-91a8-50df-acfe-756eeea82d4f")
                    IAppIndexContentRegionStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateFromString(
                            HSTRING regionId,
                            HSTRING text,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromString2(
                            HSTRING regionId,
                            HSTRING text,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionTextOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromTextStream(
                            HSTRING regionId,
                            INT32 contentByteCount,
                            ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextStreamEncoding encoding,
                            ABI::Windows::Storage::Streams::IInputStream* textStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromTextStream2(
                            HSTRING regionId,
                            INT32 contentByteCount,
                            ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextStreamEncoding encoding,
                            ABI::Windows::Storage::Streams::IInputStream* textStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionTextOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromBitmap(
                            HSTRING regionId,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* image,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromBitmapWithOptions(
                            HSTRING regionId,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* image,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionImageOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromImageStream(
                            HSTRING regionId,
                            INT32 contentByteCount,
                            ABI::Windows::Storage::Streams::IInputStream* imageStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromImageStreamWithOptions(
                            HSTRING regionId,
                            INT32 contentByteCount,
                            ABI::Windows::Storage::Streams::IInputStream* imageStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionImageOptions* options,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppIndexContentRegion** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexContentRegionStatics = _uuidof(IAppIndexContentRegionStatics);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuery
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexImageQuery[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuery";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("54642613-c596-5bc2-9d0e-7f542e07906f")
                    IAppIndexImageQuery : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_QueryPhrase(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetNextMatches(
                            INT32 maxCount,
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexImageQuery = _uuidof(IAppIndexImageQuery);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexImageQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySession";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("62ebf2f4-035b-55ba-8332-86c618cc0783")
                    IAppIndexImageQuerySession : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Start(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StartWithOptions(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryOptions* options
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StartWithOptionsAndQuery(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryOptions* options,
                            HSTRING firstQueryPhrase
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Stop(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StopWithChosenMatch(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryMatch* chosenMatch
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE UpdateQueryPhrase(
                            HSTRING newQueryPhrase
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredMatchesPerResult(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredMatchesPerResult(
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetResult(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IImageQuerySessionResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_ResultChanged(
                            __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_ResultChanged(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexImageQuerySession = _uuidof(IAppIndexImageQuerySession);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySessionStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexImageQuerySessionStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySessionStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("69c6d023-f4d9-5247-a9af-f6c400e22714")
                    IAppIndexImageQuerySessionStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_MaxMatchesPerResult(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexImageQuerySessionStatics = _uuidof(IAppIndexImageQuerySessionStatics);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatch";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("95fef777-eb2b-5b23-bcb6-b3b1908116fa")
                    IAppIndexQueryMatch : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ContentId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RegionId(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ContentKind(
                            ABI::Microsoft::Windows::Search::AppContentIndex::QueryMatchContentKind* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexQueryMatch = _uuidof(IAppIndexQueryMatch);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatchFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexQueryMatchFactory[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatchFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("1c79da3e-6ff0-503c-8934-6ca4baaf5d4e")
                    IAppIndexQueryMatchFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexQueryMatchFactory = _uuidof(IAppIndexQueryMatchFactory);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuery
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexTextQuery[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuery";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("b1993a02-80d1-5cea-97c8-166a60098154")
                    IAppIndexTextQuery : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_QueryPhrase(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetNextMatches(
                            INT32 maxCount,
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexTextQuery = _uuidof(IAppIndexTextQuery);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexTextQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySession";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("260cae8c-a16a-5c7d-b8ed-652087ce12ea")
                    IAppIndexTextQuerySession : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE Start(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StartWithOptions(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryOptions* options
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StartWithOptionsAndQuery(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryOptions* options,
                            HSTRING firstQueryPhrase
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE Stop(void) = 0;
                        virtual HRESULT STDMETHODCALLTYPE StopWithChosenMatch(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryMatch* chosenMatch
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE UpdateQueryPhrase(
                            HSTRING newQueryPhrase
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DesiredMatchesPerResult(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DesiredMatchesPerResult(
                            INT32 value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetResult(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ITextQuerySessionResult** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE add_ResultChanged(
                            __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable* handler,
                            EventRegistrationToken* token
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE remove_ResultChanged(
                            EventRegistrationToken token
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexTextQuerySession = _uuidof(IAppIndexTextQuerySession);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySessionStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexTextQuerySessionStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySessionStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("2cd6ae32-60d7-5642-84eb-3efd535ab3f0")
                    IAppIndexTextQuerySessionStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_MaxMatchesPerResult(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppIndexTextQuerySessionStatics = _uuidof(IAppIndexTextQuerySessionStatics);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedImageQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedImageQueryMatch";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("3ae41e0b-8968-5353-ae25-044a8450c41c")
                    IAppManagedImageQueryMatch : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_RegionOfInterest(
                            __FIReference_1_Windows__CFoundation__CRect** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppManagedImageQueryMatch = _uuidof(IAppManagedImageQueryMatch);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedIndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContent";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("39808fa8-95a5-5dd2-90e4-0159cc2252fa")
                    IAppManagedIndexableAppContent : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ContentRegions(
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppManagedIndexableAppContent = _uuidof(IAppManagedIndexableAppContent);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContentStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedIndexableAppContentStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContentStatics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("f21620e7-0d6a-56d5-b7a6-459a715e3cf7")
                    IAppManagedIndexableAppContentStatics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE CreateFromString(
                            HSTRING contentId,
                            HSTRING text,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromStringWithOptions(
                            HSTRING contentId,
                            HSTRING text,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionTextOptions* regionOptions,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromTextStream(
                            HSTRING contentId,
                            INT32 contentByteCount,
                            ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextStreamEncoding encoding,
                            ABI::Windows::Storage::Streams::IInputStream* textStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromTextStreamWithOptions(
                            HSTRING contentId,
                            INT32 contentByteCount,
                            ABI::Microsoft::Windows::Search::AppContentIndex::AppIndexTextStreamEncoding encoding,
                            ABI::Windows::Storage::Streams::IInputStream* textStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionTextOptions* regionOptions,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromImageStream(
                            HSTRING contentId,
                            INT32 contentByteCount,
                            ABI::Windows::Storage::Streams::IInputStream* imageStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromImageStreamWithOptions(
                            HSTRING contentId,
                            INT32 contentByteCount,
                            ABI::Windows::Storage::Streams::IInputStream* imageStream,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionImageOptions* regionOptions,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromBitmap(
                            HSTRING contentId,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* bitmapContent,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromBitmapWithOptions(
                            HSTRING contentId,
                            ABI::Windows::Graphics::Imaging::ISoftwareBitmap* bitmapContent,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IContentRegionImageOptions* regionOptions,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE CreateFromContentRegions(
                            HSTRING contentId,
                            __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* contentRegions,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppManagedIndexableAppContent** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppManagedIndexableAppContentStatics = _uuidof(IAppManagedIndexableAppContentStatics);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedOcrTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedOcrTextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedOcrTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedOcrTextQueryMatch";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("ef37c172-6677-5996-a75e-ce7e861a789c")
                    IAppManagedOcrTextQueryMatch : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Fragment(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Subregion(
                            __FIReference_1_Windows__CFoundation__CRect** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppManagedOcrTextQueryMatch = _uuidof(IAppManagedOcrTextQueryMatch);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedTextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedTextQueryMatch";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("c88506bb-1116-5719-bad1-611dce064e23")
                    IAppManagedTextQueryMatch : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_TextOffset(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextLength(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IAppManagedTextQueryMatch = _uuidof(IAppManagedTextQueryMatch);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentItemReader
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentItemReader
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentItemReader[] = L"Microsoft.Windows.Search.AppContentIndex.IContentItemReader";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("87b04a16-0c70-599a-b8f2-9ff19f9fbdba")
                    IContentItemReader : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetNextItems(
                            INT32 maxCount,
                            __FIVectorView_1_HSTRING** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IContentItemReader = _uuidof(IContentItemReader);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentItemStatusResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentItemStatusResult[] = L"Microsoft.Windows.Search.AppContentIndex.IContentItemStatusResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("3b78c653-ef36-5946-8fbe-a36ed97a509f")
                    IContentItemStatusResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorDetail(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemErrorDetail* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ReindexingStatus(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ContentItemReindexingStatus* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IContentItemStatusResult = _uuidof(IContentItemStatusResult);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentRegionImageOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentRegionImageOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentRegionImageOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IContentRegionImageOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("8f4cf4d2-a106-5251-918c-7603c5452cf8")
                    IContentRegionImageOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_SuppressImageSemanticIndexing(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuppressImageSemanticIndexing(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ImageOcrIndexingOptions(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ImageOcrIndexingOptions* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ImageOcrIndexingOptions(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ImageOcrIndexingOptions value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IContentRegionImageOptions = _uuidof(IContentRegionImageOptions);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentRegionTextOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentRegionTextOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentRegionTextOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IContentRegionTextOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("93b4e811-05fd-5cc3-bf33-414b3ab37854")
                    IContentRegionTextOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_AllowSemanticIndexing(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_AllowSemanticIndexing(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Language(
                            HSTRING value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IContentRegionTextOptions = _uuidof(IContentRegionTextOptions);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IDeleteIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.DeleteIndexResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IDeleteIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.IDeleteIndexResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("f2af9ca5-03a9-521a-8f41-6a14994664a7")
                    IDeleteIndexResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::Search::AppContentIndex::DeleteIndexStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Succeeded(
                            boolean* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IDeleteIndexResult = _uuidof(IDeleteIndexResult);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IGetOrCreateIndexOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("80b59bef-099a-54a1-a101-e6915b5b6bc1")
                    IGetOrCreateIndexOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_CreateAlways(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_CreateAlways(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_DefaultLanguage(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_DefaultLanguage(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextLexicalRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TextLexicalRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextSemanticRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TextSemanticRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ImageOcrRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ImageOcrRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ImageSemanticRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_ImageSemanticRequirement(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityRequirement value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IGetOrCreateIndexOptions = _uuidof(IGetOrCreateIndexOptions);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IGetOrCreateIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("ebf3f787-2d85-561a-939b-3ebbaf44cf96")
                    IGetOrCreateIndexResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Status(
                            ABI::Microsoft::Windows::Search::AppContentIndex::GetOrCreateIndexStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Succeeded(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Indexer(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IAppContentIndexer** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IGetOrCreateIndexResult = _uuidof(IGetOrCreateIndexResult);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQueryMatch";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("18e69c41-df0b-5c92-852a-4df5501b63c8")
                    IImageQueryMatch : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IImageQueryMatch = _uuidof(IImageQueryMatch);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQueryMatchFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQueryMatchFactory[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQueryMatchFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("5eb58ac9-085e-55a4-bbc7-5593f9d9af8c")
                    IImageQueryMatchFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IImageQueryMatchFactory = _uuidof(IImageQueryMatchFactory);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQueryOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQueryOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("8275e054-8ebf-5e50-abab-9bc7b0ce4912")
                    IImageQueryOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Language(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MatchScope(
                            ABI::Microsoft::Windows::Search::AppContentIndex::QueryMatchScope* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MatchScope(
                            ABI::Microsoft::Windows::Search::AppContentIndex::QueryMatchScope value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageQueryOptions = _uuidof(IImageQueryOptions);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQuerySessionResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQuerySessionResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("db6564f0-cb24-5cf6-afba-0d21ce25b8fa")
                    IImageQuerySessionResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsValid(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_QueryPhrase(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_QueryOptions(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IImageQueryOptions** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Matches(
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IImageQuerySessionResult = _uuidof(IImageQuerySessionResult);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexCapabilities
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexCapabilities
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexCapabilities[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexCapabilities";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("e3eb1595-3b80-5183-8eaa-2aa606e6b290")
                    IIndexCapabilities : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_HasCapabilitiesWithErrors(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCapabilityState(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability capability,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IIndexCapabilityState** result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetCapabilitiesWithErrors(
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability** result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IIndexCapabilities = _uuidof(IIndexCapabilities);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexCapabilitiesOfCurrentSystem
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexCapabilitiesOfCurrentSystem
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexCapabilitiesOfCurrentSystem[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexCapabilitiesOfCurrentSystem";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("92274a42-221c-57a0-ace1-711a56e16af0")
                    IIndexCapabilitiesOfCurrentSystem : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE GetIndexCapabilityStatus(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability capability,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityOfCurrentSystemStatus* result
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE GetLanguageStatusForIndexCapability(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability capability,
                            HSTRING language,
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityLanguageStatus* result
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IIndexCapabilitiesOfCurrentSystem = _uuidof(IIndexCapabilitiesOfCurrentSystem);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexCapabilityState
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexCapabilityState
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexCapabilityState[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexCapabilityState";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("c00c4dbd-e259-5930-bb4f-f1d8a8e8f7cb")
                    IIndexCapabilityState : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_Capability(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapability* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InitializationStatus(
                            ABI::Microsoft::Windows::Search::AppContentIndex::IndexCapabilityInitializationStatus* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ExtendedError(
                            HRESULT* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorMessage(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IIndexCapabilityState = _uuidof(IIndexCapabilityState);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexStatistics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexStatistics
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexStatistics[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexStatistics";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("16475c25-15a2-5e56-bd81-f7abae16993d")
                    IIndexStatistics : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IndexingInProgress(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ItemCount(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_CompletedCount(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_NotStartedCount(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_InProgressCount(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_ErrorsCount(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_PendingDeletionCount(
                            INT32* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_RequiringReindexingCount(
                            INT32* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IIndexStatistics = _uuidof(IIndexStatistics);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexableAppContent";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("8f8751ce-58a2-569c-a2d5-af9a795a005a")
                    IIndexableAppContent : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_ContentId(
                            HSTRING* value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_IIndexableAppContent = _uuidof(IIndexableAppContent);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexableAppContentFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexableAppContentFactory[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexableAppContentFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("44fbfe73-232c-593a-9f1b-3e5008ee9bef")
                    IIndexableAppContentFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_IIndexableAppContentFactory = _uuidof(IIndexableAppContentFactory);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQueryMatch";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("ab1db800-01d1-595f-af66-7a63746610cb")
                    ITextQueryMatch : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ITextQueryMatch = _uuidof(ITextQueryMatch);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQueryMatchFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQueryMatchFactory[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQueryMatchFactory";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("a2f24864-5094-5606-af67-96aee5564f8b")
                    ITextQueryMatchFactory : public IInspectable
                    {
                    public:
                    };

                    MIDL_CONST_ID IID& IID_ITextQueryMatchFactory = _uuidof(ITextQueryMatchFactory);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQueryOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQueryOptions";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("33641046-ee24-5ae1-9999-4f58dca7c1c2")
                    ITextQueryOptions : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_SuppressSemanticMatches(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_SuppressSemanticMatches(
                            boolean value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Language(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_Language(
                            HSTRING value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_MatchScope(
                            ABI::Microsoft::Windows::Search::AppContentIndex::QueryMatchScope* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_MatchScope(
                            ABI::Microsoft::Windows::Search::AppContentIndex::QueryMatchScope value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_TextMatchType(
                            ABI::Microsoft::Windows::Search::AppContentIndex::TextLexicalMatchType* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE put_TextMatchType(
                            ABI::Microsoft::Windows::Search::AppContentIndex::TextLexicalMatchType value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextQueryOptions = _uuidof(ITextQueryOptions);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQuerySessionResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQuerySessionResult";
namespace ABI {
    namespace Microsoft {
        namespace Windows {
            namespace Search {
                namespace AppContentIndex {
                    MIDL_INTERFACE("72b9da3b-b5a8-544e-880f-10998e8c0568")
                    ITextQuerySessionResult : public IInspectable
                    {
                    public:
                        virtual HRESULT STDMETHODCALLTYPE get_IsValid(
                            boolean* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_QueryPhrase(
                            HSTRING* value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_QueryOptions(
                            ABI::Microsoft::Windows::Search::AppContentIndex::ITextQueryOptions** value
                            ) = 0;
                        virtual HRESULT STDMETHODCALLTYPE get_Matches(
                            __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch** value
                            ) = 0;
                    };

                    MIDL_CONST_ID IID& IID_ITextQuerySessionResult = _uuidof(ITextQuerySessionResult);
                } /* AppContentIndex */
            } /* Search */
        } /* Windows */
    } /* Microsoft */
} /* ABI */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppContentIndexListener
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppContentIndexListener ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexListener_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexListener_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppContentIndexListener[] = L"Microsoft.Windows.Search.AppContentIndex.AppContentIndexListener";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppContentIndexer
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppContentIndexerStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppContentIndexer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppContentIndexer[] = L"Microsoft.Windows.Search.AppContentIndex.AppContentIndexer";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegionStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexContentRegion_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexContentRegion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexContentRegion[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuery ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuery_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuery_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuery[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuery";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySessionStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySession ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuerySession_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuerySession_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuery ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuery_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuery_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuery[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuery";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySessionStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySession ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuerySession_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuerySession_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedImageQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedImageQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedImageQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedImageQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContentStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContent ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedIndexableAppContent_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedIndexableAppContent_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedIndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedOcrTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedOcrTextQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedOcrTextQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedOcrTextQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedOcrTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedOcrTextQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedTextQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedTextQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedTextQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedTextQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentItemReader
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentItemReader ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<String>
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemReader_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemReader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentItemReader[] = L"Microsoft.Windows.Search.AppContentIndex.ContentItemReader";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentItemStatusResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemStatusResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemStatusResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentItemStatusResult[] = L"Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentRegionImageOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentRegionImageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionImageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionImageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentRegionImageOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ContentRegionImageOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentRegionTextOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentRegionTextOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionTextOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionTextOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentRegionTextOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ContentRegionTextOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.DeleteIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IDeleteIndexResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_DeleteIndexResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_DeleteIndexResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_DeleteIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.DeleteIndexResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexOptions[] = L"Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IImageQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ImageQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IImageQueryOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ImageQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ImageQueryOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ImageQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IImageQuerySessionResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQuerySessionResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQuerySessionResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ImageQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.ImageQuerySessionResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexCapabilities
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexCapabilities ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilities_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilities_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexCapabilities[] = L"Microsoft.Windows.Search.AppContentIndex.IndexCapabilities";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexCapabilitiesOfCurrentSystem
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexCapabilitiesOfCurrentSystem ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilitiesOfCurrentSystem_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilitiesOfCurrentSystem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexCapabilitiesOfCurrentSystem[] = L"Microsoft.Windows.Search.AppContentIndex.IndexCapabilitiesOfCurrentSystem";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexCapabilityState
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexCapabilityState ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilityState_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilityState_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexCapabilityState[] = L"Microsoft.Windows.Search.AppContentIndex.IndexCapabilityState";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexStatistics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexStatistics ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexStatistics_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexStatistics_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexStatistics[] = L"Microsoft.Windows.Search.AppContentIndex.IndexStatistics";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexableAppContent ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexableAppContent_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexableAppContent_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.IndexableAppContent";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.TextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.ITextQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_TextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.TextQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.TextQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.ITextQueryOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_TextQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.TextQueryOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.TextQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.ITextQuerySessionResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQuerySessionResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQuerySessionResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_TextQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.TextQuerySessionResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#else // !defined(__cplusplus)
/* Forward Declarations */
#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_FWD_DEFINED__

#ifndef ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_FWD_DEFINED__
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_FWD_DEFINED__
typedef interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult;

#endif // ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_FWD_DEFINED__

// Parameterized interface forward declarations (C)

// Collection interface definitions

typedef interface __FIAsyncOperationCompletedHandler_1_boolean __FIAsyncOperationCompletedHandler_1_boolean;

#if !defined(____FIAsyncOperation_1_boolean_INTERFACE_DEFINED__)
#define ____FIAsyncOperation_1_boolean_INTERFACE_DEFINED__

typedef interface __FIAsyncOperation_1_boolean __FIAsyncOperation_1_boolean;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperation_1_boolean;

typedef struct __FIAsyncOperation_1_booleanVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperation_1_boolean* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperation_1_boolean* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperation_1_boolean* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperation_1_boolean* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperation_1_boolean* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperation_1_boolean* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperation_1_boolean* This,
        __FIAsyncOperationCompletedHandler_1_boolean* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperation_1_boolean* This,
        __FIAsyncOperationCompletedHandler_1_boolean** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperation_1_boolean* This,
        boolean* result);

    END_INTERFACE
} __FIAsyncOperation_1_booleanVtbl;

interface __FIAsyncOperation_1_boolean
{
    CONST_VTBL struct __FIAsyncOperation_1_booleanVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperation_1_boolean_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperation_1_boolean_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperation_1_boolean_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperation_1_boolean_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperation_1_boolean_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperation_1_boolean_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperation_1_boolean_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperation_1_boolean_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperation_1_boolean_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperation_1_boolean_INTERFACE_DEFINED__

#if !defined(____FIAsyncOperationCompletedHandler_1_boolean_INTERFACE_DEFINED__)
#define ____FIAsyncOperationCompletedHandler_1_boolean_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationCompletedHandler_1_boolean __FIAsyncOperationCompletedHandler_1_boolean;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationCompletedHandler_1_boolean;

typedef struct __FIAsyncOperationCompletedHandler_1_booleanVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationCompletedHandler_1_boolean* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationCompletedHandler_1_boolean* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationCompletedHandler_1_boolean* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationCompletedHandler_1_boolean* This,
        __FIAsyncOperation_1_boolean* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationCompletedHandler_1_booleanVtbl;

interface __FIAsyncOperationCompletedHandler_1_boolean
{
    CONST_VTBL struct __FIAsyncOperationCompletedHandler_1_booleanVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationCompletedHandler_1_boolean_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationCompletedHandler_1_boolean_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationCompletedHandler_1_boolean_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationCompletedHandler_1_boolean_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationCompletedHandler_1_boolean_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

typedef struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* asyncInfo,
        AsyncStatus asyncStatus);

    END_INTERFACE
} __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl;

interface __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double
{
    CONST_VTBL struct __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_Invoke(This, asyncInfo, asyncStatus) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, asyncStatus))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__)
#define ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

typedef struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* put_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* handler);
    HRESULT (STDMETHODCALLTYPE* get_Progress)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double** result);
    HRESULT (STDMETHODCALLTYPE* put_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* handler);
    HRESULT (STDMETHODCALLTYPE* get_Completed)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __FIAsyncOperationWithProgressCompletedHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double** result);
    HRESULT (STDMETHODCALLTYPE* GetResults)(__FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities** result);

    END_INTERFACE
} __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl;

interface __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double
{
    CONST_VTBL struct __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_put_Progress(This, handler) \
    ((This)->lpVtbl->put_Progress(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_get_Progress(This, result) \
    ((This)->lpVtbl->get_Progress(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_put_Completed(This, handler) \
    ((This)->lpVtbl->put_Completed(This, handler))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_get_Completed(This, result) \
    ((This)->lpVtbl->get_Completed(This, result))

#define __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_GetResults(This, result) \
    ((This)->lpVtbl->GetResults(This, result))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__)
#define ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__

typedef interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double;

typedef struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double* asyncInfo,
        DOUBLE progressInfo);

    END_INTERFACE
} __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl;

interface __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double
{
    CONST_VTBL struct __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_doubleVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_Invoke(This, asyncInfo, progressInfo) \
    ((This)->lpVtbl->Invoke(This, asyncInfo, progressInfo))

#endif /* COBJMACROS */

#endif // ____FIAsyncOperationProgressHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion;

typedef struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl;

interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion;

typedef struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl;

interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch;

typedef struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl;

interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch;

typedef struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl;

interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability;

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability;

typedef struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability* result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        UINT32 itemsLength,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability* items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl;

interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability;

typedef struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl;

interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__)
#define ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__

typedef interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch;

typedef struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl;

interface __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch
{
    CONST_VTBL struct __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__)
#define ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__

typedef interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch;

typedef struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        __FIIterator_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch** result);

    END_INTERFACE
} __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl;

interface __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch
{
    CONST_VTBL struct __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

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

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Key)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* result);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** result);

    END_INTERFACE
} __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_Key(This, result) \
    ((This)->lpVtbl->get_Key(This, result))

#define __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Current)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** result);
    HRESULT (STDMETHODCALLTYPE* get_HasCurrent)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* MoveNext)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        UINT32 itemsLength,
        __FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** items,
        UINT32* result);

    END_INTERFACE
} __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_Current(This, result) \
    ((This)->lpVtbl->get_Current(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_HasCurrent(This, result) \
    ((This)->lpVtbl->get_HasCurrent(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_MoveNext(This, result) \
    ((This)->lpVtbl->MoveNext(This, result))

#define __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetMany(This, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* First)(__FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __FIIterator_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** result);

    END_INTERFACE
} __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_First(This, result) \
    ((This)->lpVtbl->First(This, result))

#endif /* COBJMACROS */

#endif // ____FIIterable_1___FIKeyValuePair_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

typedef interface __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Lookup)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING key,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* HasKey)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING key,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* Split)(__FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** first,
        __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** second);

    END_INTERFACE
} __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Lookup(This, key, result) \
    ((This)->lpVtbl->Lookup(This, key, result))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_HasKey(This, key, result) \
    ((This)->lpVtbl->HasKey(This, key, result))

#define __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Split(This, first, second) \
    ((This)->lpVtbl->Split(This, first, second))

#endif /* COBJMACROS */

#endif // ____FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion;

typedef struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch;

typedef struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability;

typedef struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        UINT32 index,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability* result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability* items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilityVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__)
#define ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__

typedef interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch;

typedef struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetAt)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        UINT32 index,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch** result);
    HRESULT (STDMETHODCALLTYPE* get_Size)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        UINT32* result);
    HRESULT (STDMETHODCALLTYPE* IndexOf)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* value,
        UINT32* index,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* GetMany)(__FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch* This,
        UINT32 startIndex,
        UINT32 itemsLength,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch** items,
        UINT32* result);

    END_INTERFACE
} __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl;

interface __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch
{
    CONST_VTBL struct __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetAt(This, index, result) \
    ((This)->lpVtbl->GetAt(This, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_get_Size(This, result) \
    ((This)->lpVtbl->get_Size(This, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_IndexOf(This, value, index, result) \
    ((This)->lpVtbl->IndexOf(This, value, index, result))

#define __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_GetMany(This, startIndex, itemsLength, items, result) \
    ((This)->lpVtbl->GetMany(This, startIndex, itemsLength, items, result))

#endif /* COBJMACROS */

#endif // ____FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

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

typedef struct __x_ABI_CWindows_CFoundation_CRect __x_ABI_CWindows_CFoundation_CRect;

#if WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION >= 0x10000
#if !defined(____FIReference_1_Windows__CFoundation__CRect_INTERFACE_DEFINED__)
#define ____FIReference_1_Windows__CFoundation__CRect_INTERFACE_DEFINED__

typedef interface __FIReference_1_Windows__CFoundation__CRect __FIReference_1_Windows__CFoundation__CRect;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FIReference_1_Windows__CFoundation__CRect;

typedef struct __FIReference_1_Windows__CFoundation__CRectVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FIReference_1_Windows__CFoundation__CRect* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FIReference_1_Windows__CFoundation__CRect* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FIReference_1_Windows__CFoundation__CRect* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__FIReference_1_Windows__CFoundation__CRect* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__FIReference_1_Windows__CFoundation__CRect* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__FIReference_1_Windows__CFoundation__CRect* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Value)(__FIReference_1_Windows__CFoundation__CRect* This,
        struct __x_ABI_CWindows_CFoundation_CRect* result);

    END_INTERFACE
} __FIReference_1_Windows__CFoundation__CRectVtbl;

interface __FIReference_1_Windows__CFoundation__CRect
{
    CONST_VTBL struct __FIReference_1_Windows__CFoundation__CRectVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FIReference_1_Windows__CFoundation__CRect_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FIReference_1_Windows__CFoundation__CRect_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FIReference_1_Windows__CFoundation__CRect_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FIReference_1_Windows__CFoundation__CRect_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __FIReference_1_Windows__CFoundation__CRect_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __FIReference_1_Windows__CFoundation__CRect_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __FIReference_1_Windows__CFoundation__CRect_get_Value(This, result) \
    ((This)->lpVtbl->get_Value(This, result))

#endif /* COBJMACROS */

#endif // ____FIReference_1_Windows__CFoundation__CRect_INTERFACE_DEFINED__
#endif // WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilitiesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* sender,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilitiesVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilitiesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatisticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* sender,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatisticsVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatisticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* sender,
        __FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_INTERFACE_DEFINED__)
#define ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_INTERFACE_DEFINED__

typedef interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable;

//  Declare the parameterized interface IID.
EXTERN_C const IID IID___FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable;

typedef struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectableVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable* This);
    ULONG (STDMETHODCALLTYPE* Release)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable* This);
    HRESULT (STDMETHODCALLTYPE* Invoke)(__FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* sender,
        IInspectable* args);

    END_INTERFACE
} __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectableVtbl;

interface __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable
{
    CONST_VTBL struct __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectableVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_Invoke(This, sender, args) \
    ((This)->lpVtbl->Invoke(This, sender, args))

#endif /* COBJMACROS */

#endif // ____FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable_INTERFACE_DEFINED__
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#ifndef ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIClosable __x_ABI_CWindows_CFoundation_CIClosable;

#endif // ____x_ABI_CWindows_CFoundation_CIClosable_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
#define ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CFoundation_CIPropertyValue __x_ABI_CWindows_CFoundation_CIPropertyValue;

#endif // ____x_ABI_CWindows_CFoundation_CIPropertyValue_FWD_DEFINED__

typedef struct __x_ABI_CWindows_CFoundation_CTimeSpan __x_ABI_CWindows_CFoundation_CTimeSpan;

#ifndef ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
#define ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap;

#endif // ____x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap_FWD_DEFINED__

#ifndef ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_FWD_DEFINED__
#define ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_FWD_DEFINED__
typedef interface __x_ABI_CWindows_CStorage_CStreams_CIInputStream __x_ABI_CWindows_CStorage_CStreams_CIInputStream;

#endif // ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_FWD_DEFINED__

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemErrorDetail __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemErrorDetail;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemReindexingStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemReindexingStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexWhileInUseBehavior __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexWhileInUseBehavior;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CGetOrCreateIndexStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CGetOrCreateIndexStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CImageOcrIndexingOptions __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CImageOcrIndexingOptions;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityInitializationStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityInitializationStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityLanguageStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityLanguageStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityOfCurrentSystemStatus __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityOfCurrentSystemStatus;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryContentItemsFilterFlags __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryContentItemsFilterFlags;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchContentKind __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchContentKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CRegionContentKind __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CRegionContentKind;

typedef enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CTextLexicalMatchType __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CTextLexicalMatchType;

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.AppIndexTextStreamEncoding
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding
{
    AppIndexTextStreamEncoding_Utf8 = 0,
    AppIndexTextStreamEncoding_Utf16_LE = 1,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ContentItemErrorDetail
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemErrorDetail
{
    ContentItemErrorDetail_NoError = 0,
    ContentItemErrorDetail_UnknownFailure = 1,
    ContentItemErrorDetail_UnknownContentId = 2,
    ContentItemErrorDetail_ContentRegionErrors = 3,
    ContentItemErrorDetail_IndexCorruption = 4,
    ContentItemErrorDetail_InsufficientDiskSpace = 5,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ContentItemReindexingStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemReindexingStatus
{
    ContentItemReindexingStatus_None = 0,
    ContentItemReindexingStatus_Unspecified = 1,
    ContentItemReindexingStatus_SemanticModelChanged = 2,
    ContentItemReindexingStatus_ContentUnavailable = 3,
    ContentItemReindexingStatus_SchemaChanged = 4,
    ContentItemReindexingStatus_IndexCorruption = 5,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ContentItemStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemStatus
{
    ContentItemStatus_NotStarted = 0,
    ContentItemStatus_InProgress = 1,
    ContentItemStatus_Completed = 2,
    ContentItemStatus_CompletedWithSomeErrors = 3,
    ContentItemStatus_Error = 4,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.DeleteIndexStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexStatus
{
    DeleteIndexStatus_Success = 0,
    DeleteIndexStatus_IndexNotFound = 1,
    DeleteIndexStatus_Deferred = 2,
    DeleteIndexStatus_UnknownFailure = 100,
    DeleteIndexStatus_IndexInUse = 101,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.DeleteIndexWhileInUseBehavior
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexWhileInUseBehavior
{
    DeleteIndexWhileInUseBehavior_FailIfInUse = 0,
    DeleteIndexWhileInUseBehavior_DeferIfInUse = 1,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CGetOrCreateIndexStatus
{
    GetOrCreateIndexStatus_CreatedNew = 0,
    GetOrCreateIndexStatus_OpenedExisting = 1,
    GetOrCreateIndexStatus_UnknownFailure = 100,
    GetOrCreateIndexStatus_InvalidOptions = 101,
    GetOrCreateIndexStatus_IncompatibleWithExistingOptions = 102,
    GetOrCreateIndexStatus_UnsupportedDefaultLanguage = 103,
    GetOrCreateIndexStatus_InvalidIndexName = 104,
    GetOrCreateIndexStatus_DeferredDeletionFailed = 105,
    GetOrCreateIndexStatus_LexicalModelsNotAvailable = 106,
    GetOrCreateIndexStatus_SemanticModelsNotAvailable = 107,
    GetOrCreateIndexStatus_OcrModelsNotAvailable = 108,
    GetOrCreateIndexStatus_IndexIsPendingDeletion = 109,
    GetOrCreateIndexStatus_SemanticTextIndexStoreFailure = 110,
    GetOrCreateIndexStatus_SemanticOcrTextIndexStoreFailure = 111,
    GetOrCreateIndexStatus_SemanticImageIndexStoreFailure = 112,
    GetOrCreateIndexStatus_AppContentIndexerFileLockedError = 113,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.ImageOcrIndexingOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CImageOcrIndexingOptions
{
    ImageOcrIndexingOptions_Default = 0,
    ImageOcrIndexingOptions_SuppressSemanticIndexing = 1,
    ImageOcrIndexingOptions_SuppressLexicalAndSemanticIndexing = 2,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapability
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability
{
    IndexCapability_TextLexical = 0,
    IndexCapability_TextSemantic = 1,
    IndexCapability_ImageOcr = 2,
    IndexCapability_ImageSemantic = 3,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityInitializationStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityInitializationStatus
{
    IndexCapabilityInitializationStatus_Unknown = 0,
    IndexCapabilityInitializationStatus_Initialized = 1,
    IndexCapabilityInitializationStatus_Initializing = 2,
    IndexCapabilityInitializationStatus_Suppressed = 3,
    IndexCapabilityInitializationStatus_NotSupported = 4,
    IndexCapabilityInitializationStatus_DisabledByPolicy = 5,
    IndexCapabilityInitializationStatus_InitializationError = 100,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityLanguageStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityLanguageStatus
{
    IndexCapabilityLanguageStatus_Supported = 0,
    IndexCapabilityLanguageStatus_Partial = 1,
    IndexCapabilityLanguageStatus_NotSupported = 2,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityOfCurrentSystemStatus
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityOfCurrentSystemStatus
{
    IndexCapabilityOfCurrentSystemStatus_Ready = 0,
    IndexCapabilityOfCurrentSystemStatus_NotReady = 1,
    IndexCapabilityOfCurrentSystemStatus_DisabledByPolicy = 2,
    IndexCapabilityOfCurrentSystemStatus_NotSupported = 3,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.IndexCapabilityRequirement
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement
{
    IndexCapabilityRequirement_Default = 0,
    IndexCapabilityRequirement_Suppressed = 1,
    IndexCapabilityRequirement_Required = 2,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.QueryContentItemsFilterFlags
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryContentItemsFilterFlags
{
    QueryContentItemsFilterFlags_NotStarted = 0x1,
    QueryContentItemsFilterFlags_InProgress = 0x2,
    QueryContentItemsFilterFlags_Completed = 0x4,
    QueryContentItemsFilterFlags_WithErrors = 0x8,
    QueryContentItemsFilterFlags_PendingDeletion = 0x10,
    QueryContentItemsFilterFlags_RequiringReindexing = 0x20,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.QueryMatchContentKind
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchContentKind
{
    QueryMatchContentKind_AppManagedText = 0,
    QueryMatchContentKind_AppManagedImage = 1,
    QueryMatchContentKind_AppManagedOcrText = 2,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.QueryMatchScope
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope
{
    QueryMatchScope_Unconstrained = 0,
    QueryMatchScope_Region = 1,
    QueryMatchScope_ContentItem = 2,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.RegionContentKind
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CRegionContentKind
{
    RegionContentKind_Text = 0,
    RegionContentKind_Image = 1,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Struct Microsoft.Windows.Search.AppContentIndex.TextLexicalMatchType
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CTextLexicalMatchType
{
    TextLexicalMatchType_Fuzzy = 0,
    TextLexicalMatchType_Exact = 1,
};
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppContentIndexListener
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppContentIndexListener
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppContentIndexListener[] = L"Microsoft.Windows.Search.AppContentIndex.IAppContentIndexListener";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListenerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* add_IndexCapabilitiesChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_IndexCapabilitiesChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_IndexStatisticsChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexStatistics* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_IndexStatisticsChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        EventRegistrationToken token);
    HRESULT (STDMETHODCALLTYPE* add_ContentItemStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppContentIndexer___FIMapView_2_HSTRING_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ContentItemStatusChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListenerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListenerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_add_IndexCapabilitiesChanged(This, handler, token) \
    ((This)->lpVtbl->add_IndexCapabilitiesChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_remove_IndexCapabilitiesChanged(This, token) \
    ((This)->lpVtbl->remove_IndexCapabilitiesChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_add_IndexStatisticsChanged(This, handler, token) \
    ((This)->lpVtbl->add_IndexStatisticsChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_remove_IndexStatisticsChanged(This, token) \
    ((This)->lpVtbl->remove_IndexStatisticsChanged(This, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_add_ContentItemStatusChanged(This, handler, token) \
    ((This)->lpVtbl->add_ContentItemStatusChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_remove_ContentItemStatusChanged(This, token) \
    ((This)->lpVtbl->remove_ContentItemStatusChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppContentIndexer
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppContentIndexer
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppContentIndexer[] = L"Microsoft.Windows.Search.AppContentIndex.IAppContentIndexer";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Listener)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexListener** value);
    HRESULT (STDMETHODCALLTYPE* get_IndexName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* GetIndexCapabilities)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities** result);
    HRESULT (STDMETHODCALLTYPE* WaitForIndexCapabilitiesAsync)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __FIAsyncOperationWithProgress_2_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapabilities_double** operation);
    HRESULT (STDMETHODCALLTYPE* get_DefaultLanguage)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* IsContentKindSupported)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CRegionContentKind contentKind,
        boolean* result);
    HRESULT (STDMETHODCALLTYPE* AddOrUpdate)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* indexableContent);
    HRESULT (STDMETHODCALLTYPE* CreateTextQuery)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING queryPhrase,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery** result);
    HRESULT (STDMETHODCALLTYPE* CreateTextQueryWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING queryPhrase,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery** result);
    HRESULT (STDMETHODCALLTYPE* CreateImageQuery)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING queryPhrase,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery** result);
    HRESULT (STDMETHODCALLTYPE* CreateImageQueryWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING queryPhrase,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery** result);
    HRESULT (STDMETHODCALLTYPE* CreateTextQuerySession)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession** result);
    HRESULT (STDMETHODCALLTYPE* CreateImageQuerySession)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession** result);
    HRESULT (STDMETHODCALLTYPE* RemoveContentItem)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING contentId);
    HRESULT (STDMETHODCALLTYPE* RemoveContentItems)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __FIIterable_1_HSTRING* contentIds);
    HRESULT (STDMETHODCALLTYPE* RemoveAllContentItems)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This);
    HRESULT (STDMETHODCALLTYPE* WaitForIndexingIdleAsync)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        struct __x_ABI_CWindows_CFoundation_CTimeSpan timeout,
        __FIAsyncOperation_1_boolean** operation);
    HRESULT (STDMETHODCALLTYPE* GetIndexStatistics)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics** result);
    HRESULT (STDMETHODCALLTYPE* GetContentItemStatus)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        HSTRING contentId,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult** result);
    HRESULT (STDMETHODCALLTYPE* GetContentItemStatuses)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __FIIterable_1_HSTRING* contentIds,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CContentItemStatusResult** result);
    HRESULT (STDMETHODCALLTYPE* GetContentItemsRequiringReindexing)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader** result);
    HRESULT (STDMETHODCALLTYPE* GetContentItems)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader** result);
    HRESULT (STDMETHODCALLTYPE* GetContentItemsWithFilter)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryContentItemsFilterFlags filterFlags,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_get_Listener(This, value) \
    ((This)->lpVtbl->get_Listener(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_get_IndexName(This, value) \
    ((This)->lpVtbl->get_IndexName(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetIndexCapabilities(This, result) \
    ((This)->lpVtbl->GetIndexCapabilities(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_WaitForIndexCapabilitiesAsync(This, operation) \
    ((This)->lpVtbl->WaitForIndexCapabilitiesAsync(This, operation))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_get_DefaultLanguage(This, value) \
    ((This)->lpVtbl->get_DefaultLanguage(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_IsContentKindSupported(This, contentKind, result) \
    ((This)->lpVtbl->IsContentKindSupported(This, contentKind, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_AddOrUpdate(This, indexableContent) \
    ((This)->lpVtbl->AddOrUpdate(This, indexableContent))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_CreateTextQuery(This, queryPhrase, result) \
    ((This)->lpVtbl->CreateTextQuery(This, queryPhrase, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_CreateTextQueryWithOptions(This, queryPhrase, options, result) \
    ((This)->lpVtbl->CreateTextQueryWithOptions(This, queryPhrase, options, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_CreateImageQuery(This, queryPhrase, result) \
    ((This)->lpVtbl->CreateImageQuery(This, queryPhrase, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_CreateImageQueryWithOptions(This, queryPhrase, options, result) \
    ((This)->lpVtbl->CreateImageQueryWithOptions(This, queryPhrase, options, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_CreateTextQuerySession(This, result) \
    ((This)->lpVtbl->CreateTextQuerySession(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_CreateImageQuerySession(This, result) \
    ((This)->lpVtbl->CreateImageQuerySession(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_RemoveContentItem(This, contentId) \
    ((This)->lpVtbl->RemoveContentItem(This, contentId))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_RemoveContentItems(This, contentIds) \
    ((This)->lpVtbl->RemoveContentItems(This, contentIds))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_RemoveAllContentItems(This) \
    ((This)->lpVtbl->RemoveAllContentItems(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_WaitForIndexingIdleAsync(This, timeout, operation) \
    ((This)->lpVtbl->WaitForIndexingIdleAsync(This, timeout, operation))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetIndexStatistics(This, result) \
    ((This)->lpVtbl->GetIndexStatistics(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetContentItemStatus(This, contentId, result) \
    ((This)->lpVtbl->GetContentItemStatus(This, contentId, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetContentItemStatuses(This, contentIds, result) \
    ((This)->lpVtbl->GetContentItemStatuses(This, contentIds, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetContentItemsRequiringReindexing(This, result) \
    ((This)->lpVtbl->GetContentItemsRequiringReindexing(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetContentItems(This, result) \
    ((This)->lpVtbl->GetContentItems(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_GetContentItemsWithFilter(This, filterFlags, result) \
    ((This)->lpVtbl->GetContentItemsWithFilter(This, filterFlags, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppContentIndexerStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppContentIndexer
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppContentIndexerStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppContentIndexerStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetIndexCapabilitiesOfCurrentSystem)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem** result);
    HRESULT (STDMETHODCALLTYPE* GetOrCreateIndex)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        HSTRING indexName,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult** result);
    HRESULT (STDMETHODCALLTYPE* GetOrCreateIndexWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        HSTRING indexName,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult** result);
    HRESULT (STDMETHODCALLTYPE* DeleteIndex)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        HSTRING indexName,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexWhileInUseBehavior deleteIndexWhileInUseBehavior,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult** result);
    HRESULT (STDMETHODCALLTYPE* GetExistingIndexes)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics* This,
        __FIVectorView_1_HSTRING** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetIndexCapabilitiesOfCurrentSystem(This, result) \
    ((This)->lpVtbl->GetIndexCapabilitiesOfCurrentSystem(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetOrCreateIndex(This, indexName, result) \
    ((This)->lpVtbl->GetOrCreateIndex(This, indexName, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetOrCreateIndexWithOptions(This, indexName, options, result) \
    ((This)->lpVtbl->GetOrCreateIndexWithOptions(This, indexName, options, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_DeleteIndex(This, indexName, deleteIndexWhileInUseBehavior, result) \
    ((This)->lpVtbl->DeleteIndex(This, indexName, deleteIndexWhileInUseBehavior, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_GetExistingIndexes(This, result) \
    ((This)->lpVtbl->GetExistingIndexes(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexerStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegion
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexContentRegion[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegion";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RegionId)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ContentKind)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CRegionContentKind* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_get_RegionId(This, value) \
    ((This)->lpVtbl->get_RegionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_get_ContentKind(This, value) \
    ((This)->lpVtbl->get_ContentKind(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegionStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexContentRegionStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegionStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateFromString)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromString2)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromTextStream)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        INT32 contentByteCount,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding encoding,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* textStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromTextStream2)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        INT32 contentByteCount,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding encoding,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* textStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromBitmap)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* image,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromBitmapWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* image,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromImageStream)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        INT32 contentByteCount,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* imageStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromImageStreamWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics* This,
        HSTRING regionId,
        INT32 contentByteCount,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* imageStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* options,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegion** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromString(This, regionId, text, result) \
    ((This)->lpVtbl->CreateFromString(This, regionId, text, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromString2(This, regionId, text, options, result) \
    ((This)->lpVtbl->CreateFromString2(This, regionId, text, options, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromTextStream(This, regionId, contentByteCount, encoding, textStream, result) \
    ((This)->lpVtbl->CreateFromTextStream(This, regionId, contentByteCount, encoding, textStream, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromTextStream2(This, regionId, contentByteCount, encoding, textStream, options, result) \
    ((This)->lpVtbl->CreateFromTextStream2(This, regionId, contentByteCount, encoding, textStream, options, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromBitmap(This, regionId, image, result) \
    ((This)->lpVtbl->CreateFromBitmap(This, regionId, image, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromBitmapWithOptions(This, regionId, image, options, result) \
    ((This)->lpVtbl->CreateFromBitmapWithOptions(This, regionId, image, options, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromImageStream(This, regionId, contentByteCount, imageStream, result) \
    ((This)->lpVtbl->CreateFromImageStream(This, regionId, contentByteCount, imageStream, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_CreateFromImageStreamWithOptions(This, regionId, contentByteCount, imageStream, options, result) \
    ((This)->lpVtbl->CreateFromImageStreamWithOptions(This, regionId, contentByteCount, imageStream, options, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexContentRegionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuery
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexImageQuery[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuery";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQueryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_QueryPhrase)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* GetNextMatches)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery* This,
        INT32 maxCount,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQueryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQueryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_get_QueryPhrase(This, value) \
    ((This)->lpVtbl->get_QueryPhrase(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_GetNextMatches(This, maxCount, result) \
    ((This)->lpVtbl->GetNextMatches(This, maxCount, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuery_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexImageQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySession";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Start)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This);
    HRESULT (STDMETHODCALLTYPE* StartWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* options);
    HRESULT (STDMETHODCALLTYPE* StartWithOptionsAndQuery)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* options,
        HSTRING firstQueryPhrase);
    HRESULT (STDMETHODCALLTYPE* Stop)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This);
    HRESULT (STDMETHODCALLTYPE* StopWithChosenMatch)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* chosenMatch);
    HRESULT (STDMETHODCALLTYPE* UpdateQueryPhrase)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        HSTRING newQueryPhrase);
    HRESULT (STDMETHODCALLTYPE* get_DesiredMatchesPerResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredMatchesPerResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* GetResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult** result);
    HRESULT (STDMETHODCALLTYPE* add_ResultChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexImageQuerySession_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ResultChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_Start(This) \
    ((This)->lpVtbl->Start(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_StartWithOptions(This, options) \
    ((This)->lpVtbl->StartWithOptions(This, options))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_StartWithOptionsAndQuery(This, options, firstQueryPhrase) \
    ((This)->lpVtbl->StartWithOptionsAndQuery(This, options, firstQueryPhrase))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_Stop(This) \
    ((This)->lpVtbl->Stop(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_StopWithChosenMatch(This, chosenMatch) \
    ((This)->lpVtbl->StopWithChosenMatch(This, chosenMatch))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_UpdateQueryPhrase(This, newQueryPhrase) \
    ((This)->lpVtbl->UpdateQueryPhrase(This, newQueryPhrase))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_get_DesiredMatchesPerResult(This, value) \
    ((This)->lpVtbl->get_DesiredMatchesPerResult(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_put_DesiredMatchesPerResult(This, value) \
    ((This)->lpVtbl->put_DesiredMatchesPerResult(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_GetResult(This, result) \
    ((This)->lpVtbl->GetResult(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_add_ResultChanged(This, handler, token) \
    ((This)->lpVtbl->add_ResultChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_remove_ResultChanged(This, token) \
    ((This)->lpVtbl->remove_ResultChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySession_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySessionStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexImageQuerySessionStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySessionStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_MaxMatchesPerResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_get_MaxMatchesPerResult(This, value) \
    ((This)->lpVtbl->get_MaxMatchesPerResult(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexImageQuerySessionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatch";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ContentId)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_RegionId)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_ContentKind)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchContentKind* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_get_ContentId(This, value) \
    ((This)->lpVtbl->get_ContentId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_get_RegionId(This, value) \
    ((This)->lpVtbl->get_RegionId(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_get_ContentKind(This, value) \
    ((This)->lpVtbl->get_ContentKind(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatchFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexQueryMatchFactory[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatchFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexQueryMatchFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuery
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexTextQuery[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuery";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQueryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_QueryPhrase)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* GetNextMatches)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery* This,
        INT32 maxCount,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQueryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQueryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_get_QueryPhrase(This, value) \
    ((This)->lpVtbl->get_QueryPhrase(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_GetNextMatches(This, maxCount, result) \
    ((This)->lpVtbl->GetNextMatches(This, maxCount, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuery_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexTextQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySession";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* Start)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This);
    HRESULT (STDMETHODCALLTYPE* StartWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* options);
    HRESULT (STDMETHODCALLTYPE* StartWithOptionsAndQuery)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* options,
        HSTRING firstQueryPhrase);
    HRESULT (STDMETHODCALLTYPE* Stop)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This);
    HRESULT (STDMETHODCALLTYPE* StopWithChosenMatch)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* chosenMatch);
    HRESULT (STDMETHODCALLTYPE* UpdateQueryPhrase)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        HSTRING newQueryPhrase);
    HRESULT (STDMETHODCALLTYPE* get_DesiredMatchesPerResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* put_DesiredMatchesPerResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        INT32 value);
    HRESULT (STDMETHODCALLTYPE* GetResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult** result);
    HRESULT (STDMETHODCALLTYPE* add_ResultChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        __FITypedEventHandler_2_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexTextQuerySession_IInspectable* handler,
        EventRegistrationToken* token);
    HRESULT (STDMETHODCALLTYPE* remove_ResultChanged)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession* This,
        EventRegistrationToken token);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_Start(This) \
    ((This)->lpVtbl->Start(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_StartWithOptions(This, options) \
    ((This)->lpVtbl->StartWithOptions(This, options))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_StartWithOptionsAndQuery(This, options, firstQueryPhrase) \
    ((This)->lpVtbl->StartWithOptionsAndQuery(This, options, firstQueryPhrase))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_Stop(This) \
    ((This)->lpVtbl->Stop(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_StopWithChosenMatch(This, chosenMatch) \
    ((This)->lpVtbl->StopWithChosenMatch(This, chosenMatch))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_UpdateQueryPhrase(This, newQueryPhrase) \
    ((This)->lpVtbl->UpdateQueryPhrase(This, newQueryPhrase))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_get_DesiredMatchesPerResult(This, value) \
    ((This)->lpVtbl->get_DesiredMatchesPerResult(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_put_DesiredMatchesPerResult(This, value) \
    ((This)->lpVtbl->put_DesiredMatchesPerResult(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_GetResult(This, result) \
    ((This)->lpVtbl->GetResult(This, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_add_ResultChanged(This, handler, token) \
    ((This)->lpVtbl->add_ResultChanged(This, handler, token))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_remove_ResultChanged(This, token) \
    ((This)->lpVtbl->remove_ResultChanged(This, token))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySession_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySessionStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppIndexTextQuerySessionStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySessionStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_MaxMatchesPerResult)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_get_MaxMatchesPerResult(This, value) \
    ((This)->lpVtbl->get_MaxMatchesPerResult(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppIndexTextQuerySessionStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedImageQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedImageQueryMatch";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_RegionOfInterest)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch* This,
        __FIReference_1_Windows__CFoundation__CRect** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatchVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_get_RegionOfInterest(This, value) \
    ((This)->lpVtbl->get_RegionOfInterest(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedImageQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedIndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContent";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ContentRegions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent* This,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_get_ContentRegions(This, value) \
    ((This)->lpVtbl->get_ContentRegions(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContentStatics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedIndexableAppContentStatics[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContentStatics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStaticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* CreateFromString)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromStringWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        HSTRING text,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* regionOptions,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromTextStream)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        INT32 contentByteCount,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding encoding,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* textStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromTextStreamWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        INT32 contentByteCount,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CAppIndexTextStreamEncoding encoding,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* textStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* regionOptions,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromImageStream)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        INT32 contentByteCount,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* imageStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromImageStreamWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        INT32 contentByteCount,
        __x_ABI_CWindows_CStorage_CStreams_CIInputStream* imageStream,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* regionOptions,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromBitmap)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* bitmapContent,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromBitmapWithOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        __x_ABI_CWindows_CGraphics_CImaging_CISoftwareBitmap* bitmapContent,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* regionOptions,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);
    HRESULT (STDMETHODCALLTYPE* CreateFromContentRegions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics* This,
        HSTRING contentId,
        __FIIterable_1_Microsoft__CWindows__CSearch__CAppContentIndex__CAppIndexContentRegion* contentRegions,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContent** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStaticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStaticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromString(This, contentId, text, result) \
    ((This)->lpVtbl->CreateFromString(This, contentId, text, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromStringWithOptions(This, contentId, text, regionOptions, result) \
    ((This)->lpVtbl->CreateFromStringWithOptions(This, contentId, text, regionOptions, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromTextStream(This, contentId, contentByteCount, encoding, textStream, result) \
    ((This)->lpVtbl->CreateFromTextStream(This, contentId, contentByteCount, encoding, textStream, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromTextStreamWithOptions(This, contentId, contentByteCount, encoding, textStream, regionOptions, result) \
    ((This)->lpVtbl->CreateFromTextStreamWithOptions(This, contentId, contentByteCount, encoding, textStream, regionOptions, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromImageStream(This, contentId, contentByteCount, imageStream, result) \
    ((This)->lpVtbl->CreateFromImageStream(This, contentId, contentByteCount, imageStream, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromImageStreamWithOptions(This, contentId, contentByteCount, imageStream, regionOptions, result) \
    ((This)->lpVtbl->CreateFromImageStreamWithOptions(This, contentId, contentByteCount, imageStream, regionOptions, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromBitmap(This, contentId, bitmapContent, result) \
    ((This)->lpVtbl->CreateFromBitmap(This, contentId, bitmapContent, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromBitmapWithOptions(This, contentId, bitmapContent, regionOptions, result) \
    ((This)->lpVtbl->CreateFromBitmapWithOptions(This, contentId, bitmapContent, regionOptions, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_CreateFromContentRegions(This, contentId, contentRegions, result) \
    ((This)->lpVtbl->CreateFromContentRegions(This, contentId, contentRegions, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedIndexableAppContentStatics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedOcrTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedOcrTextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedOcrTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedOcrTextQueryMatch";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Fragment)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_Subregion)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch* This,
        __FIReference_1_Windows__CFoundation__CRect** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatchVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_get_Fragment(This, value) \
    ((This)->lpVtbl->get_Fragment(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_get_Subregion(This, value) \
    ((This)->lpVtbl->get_Subregion(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedOcrTextQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IAppManagedTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.AppManagedTextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IAppManagedTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IAppManagedTextQueryMatch";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_TextOffset)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_TextLength)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatchVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_get_TextOffset(This, value) \
    ((This)->lpVtbl->get_TextOffset(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_get_TextLength(This, value) \
    ((This)->lpVtbl->get_TextLength(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppManagedTextQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentItemReader
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentItemReader
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentItemReader[] = L"Microsoft.Windows.Search.AppContentIndex.IContentItemReader";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReaderVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetNextItems)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader* This,
        INT32 maxCount,
        __FIVectorView_1_HSTRING** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReaderVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReaderVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_GetNextItems(This, maxCount, result) \
    ((This)->lpVtbl->GetNextItems(This, maxCount, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemReader_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentItemStatusResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentItemStatusResult[] = L"Microsoft.Windows.Search.AppContentIndex.IContentItemStatusResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorDetail)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemErrorDetail* value);
    HRESULT (STDMETHODCALLTYPE* get_ReindexingStatus)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CContentItemReindexingStatus* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_get_ErrorDetail(This, value) \
    ((This)->lpVtbl->get_ErrorDetail(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_get_ReindexingStatus(This, value) \
    ((This)->lpVtbl->get_ReindexingStatus(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentItemStatusResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentRegionImageOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentRegionImageOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentRegionImageOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IContentRegionImageOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SuppressImageSemanticIndexing)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_SuppressImageSemanticIndexing)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_ImageOcrIndexingOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CImageOcrIndexingOptions* value);
    HRESULT (STDMETHODCALLTYPE* put_ImageOcrIndexingOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CImageOcrIndexingOptions value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_get_SuppressImageSemanticIndexing(This, value) \
    ((This)->lpVtbl->get_SuppressImageSemanticIndexing(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_put_SuppressImageSemanticIndexing(This, value) \
    ((This)->lpVtbl->put_SuppressImageSemanticIndexing(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_get_ImageOcrIndexingOptions(This, value) \
    ((This)->lpVtbl->get_ImageOcrIndexingOptions(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_put_ImageOcrIndexingOptions(This, value) \
    ((This)->lpVtbl->put_ImageOcrIndexingOptions(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionImageOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IContentRegionTextOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ContentRegionTextOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IContentRegionTextOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IContentRegionTextOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_AllowSemanticIndexing)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_AllowSemanticIndexing)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions* This,
        HSTRING value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_get_AllowSemanticIndexing(This, value) \
    ((This)->lpVtbl->get_AllowSemanticIndexing(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_put_AllowSemanticIndexing(This, value) \
    ((This)->lpVtbl->put_AllowSemanticIndexing(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_put_Language(This, value) \
    ((This)->lpVtbl->put_Language(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIContentRegionTextOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IDeleteIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.DeleteIndexResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IDeleteIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.IDeleteIndexResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CDeleteIndexStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_Succeeded)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult* This,
        boolean* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_get_Succeeded(This, value) \
    ((This)->lpVtbl->get_Succeeded(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIDeleteIndexResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IGetOrCreateIndexOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_CreateAlways)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_CreateAlways)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_DefaultLanguage)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_DefaultLanguage)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_TextLexicalRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement* value);
    HRESULT (STDMETHODCALLTYPE* put_TextLexicalRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement value);
    HRESULT (STDMETHODCALLTYPE* get_TextSemanticRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement* value);
    HRESULT (STDMETHODCALLTYPE* put_TextSemanticRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement value);
    HRESULT (STDMETHODCALLTYPE* get_ImageOcrRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement* value);
    HRESULT (STDMETHODCALLTYPE* put_ImageOcrRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement value);
    HRESULT (STDMETHODCALLTYPE* get_ImageSemanticRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement* value);
    HRESULT (STDMETHODCALLTYPE* put_ImageSemanticRequirement)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityRequirement value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_get_CreateAlways(This, value) \
    ((This)->lpVtbl->get_CreateAlways(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_put_CreateAlways(This, value) \
    ((This)->lpVtbl->put_CreateAlways(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_get_DefaultLanguage(This, value) \
    ((This)->lpVtbl->get_DefaultLanguage(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_put_DefaultLanguage(This, value) \
    ((This)->lpVtbl->put_DefaultLanguage(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_get_TextLexicalRequirement(This, value) \
    ((This)->lpVtbl->get_TextLexicalRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_put_TextLexicalRequirement(This, value) \
    ((This)->lpVtbl->put_TextLexicalRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_get_TextSemanticRequirement(This, value) \
    ((This)->lpVtbl->get_TextSemanticRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_put_TextSemanticRequirement(This, value) \
    ((This)->lpVtbl->put_TextSemanticRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_get_ImageOcrRequirement(This, value) \
    ((This)->lpVtbl->get_ImageOcrRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_put_ImageOcrRequirement(This, value) \
    ((This)->lpVtbl->put_ImageOcrRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_get_ImageSemanticRequirement(This, value) \
    ((This)->lpVtbl->get_ImageSemanticRequirement(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_put_ImageSemanticRequirement(This, value) \
    ((This)->lpVtbl->put_ImageSemanticRequirement(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IGetOrCreateIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Status)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CGetOrCreateIndexStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_Succeeded)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_Indexer)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIAppContentIndexer** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_get_Status(This, value) \
    ((This)->lpVtbl->get_Status(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_get_Succeeded(This, value) \
    ((This)->lpVtbl->get_Succeeded(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_get_Indexer(This, value) \
    ((This)->lpVtbl->get_Indexer(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIGetOrCreateIndexResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQueryMatch";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQueryMatchFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQueryMatchFactory[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQueryMatchFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryMatchFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQueryOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQueryOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_MatchScope)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope* value);
    HRESULT (STDMETHODCALLTYPE* put_MatchScope)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_put_Language(This, value) \
    ((This)->lpVtbl->put_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_get_MatchScope(This, value) \
    ((This)->lpVtbl->get_MatchScope(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_put_MatchScope(This, value) \
    ((This)->lpVtbl->put_MatchScope(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IImageQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.ImageQuerySessionResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IImageQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.IImageQuerySessionResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsValid)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_QueryPhrase)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_QueryOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQueryOptions** value);
    HRESULT (STDMETHODCALLTYPE* get_Matches)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult* This,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CImageQueryMatch** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_get_IsValid(This, value) \
    ((This)->lpVtbl->get_IsValid(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_get_QueryPhrase(This, value) \
    ((This)->lpVtbl->get_QueryPhrase(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_get_QueryOptions(This, value) \
    ((This)->lpVtbl->get_QueryOptions(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_get_Matches(This, value) \
    ((This)->lpVtbl->get_Matches(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIImageQuerySessionResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexCapabilities
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexCapabilities
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexCapabilities[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexCapabilities";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_HasCapabilitiesWithErrors)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* GetCapabilityState)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability capability,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState** result);
    HRESULT (STDMETHODCALLTYPE* GetCapabilitiesWithErrors)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities* This,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CIndexCapability** result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_get_HasCapabilitiesWithErrors(This, value) \
    ((This)->lpVtbl->get_HasCapabilitiesWithErrors(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_GetCapabilityState(This, capability, result) \
    ((This)->lpVtbl->GetCapabilityState(This, capability, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_GetCapabilitiesWithErrors(This, result) \
    ((This)->lpVtbl->GetCapabilitiesWithErrors(This, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilities_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexCapabilitiesOfCurrentSystem
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexCapabilitiesOfCurrentSystem
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexCapabilitiesOfCurrentSystem[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexCapabilitiesOfCurrentSystem";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystemVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* GetIndexCapabilityStatus)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability capability,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityOfCurrentSystemStatus* result);
    HRESULT (STDMETHODCALLTYPE* GetLanguageStatusForIndexCapability)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability capability,
        HSTRING language,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityLanguageStatus* result);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystemVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystemVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_GetIndexCapabilityStatus(This, capability, result) \
    ((This)->lpVtbl->GetIndexCapabilityStatus(This, capability, result))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_GetLanguageStatusForIndexCapability(This, capability, language, result) \
    ((This)->lpVtbl->GetLanguageStatusForIndexCapability(This, capability, language, result))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilitiesOfCurrentSystem_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexCapabilityState
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexCapabilityState
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexCapabilityState[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexCapabilityState";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityStateVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_Capability)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapability* value);
    HRESULT (STDMETHODCALLTYPE* get_InitializationStatus)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIndexCapabilityInitializationStatus* value);
    HRESULT (STDMETHODCALLTYPE* get_ExtendedError)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        HRESULT* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorMessage)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityStateVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityStateVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_get_Capability(This, value) \
    ((This)->lpVtbl->get_Capability(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_get_InitializationStatus(This, value) \
    ((This)->lpVtbl->get_InitializationStatus(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_get_ExtendedError(This, value) \
    ((This)->lpVtbl->get_ExtendedError(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_get_ErrorMessage(This, value) \
    ((This)->lpVtbl->get_ErrorMessage(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexCapabilityState_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexStatistics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexStatistics
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexStatistics[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexStatistics";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatisticsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IndexingInProgress)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_ItemCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_CompletedCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_NotStartedCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_InProgressCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_ErrorsCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_PendingDeletionCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);
    HRESULT (STDMETHODCALLTYPE* get_RequiringReindexingCount)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics* This,
        INT32* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatisticsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatisticsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_IndexingInProgress(This, value) \
    ((This)->lpVtbl->get_IndexingInProgress(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_ItemCount(This, value) \
    ((This)->lpVtbl->get_ItemCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_CompletedCount(This, value) \
    ((This)->lpVtbl->get_CompletedCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_NotStartedCount(This, value) \
    ((This)->lpVtbl->get_NotStartedCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_InProgressCount(This, value) \
    ((This)->lpVtbl->get_InProgressCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_ErrorsCount(This, value) \
    ((This)->lpVtbl->get_ErrorsCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_PendingDeletionCount(This, value) \
    ((This)->lpVtbl->get_PendingDeletionCount(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_get_RequiringReindexingCount(This, value) \
    ((This)->lpVtbl->get_RequiringReindexingCount(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexStatistics_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexableAppContent";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_ContentId)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent* This,
        HSTRING* value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_get_ContentId(This, value) \
    ((This)->lpVtbl->get_ContentId(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContent_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.IIndexableAppContentFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.IndexableAppContent
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_IIndexableAppContentFactory[] = L"Microsoft.Windows.Search.AppContentIndex.IIndexableAppContentFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CIIndexableAppContentFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQueryMatch";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatch_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQueryMatchFactory
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQueryMatch
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQueryMatchFactory[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQueryMatchFactory";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactoryVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory* This,
        TrustLevel* trustLevel);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactoryVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryMatchFactory_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQueryOptions
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQueryOptions";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptionsVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_SuppressSemanticMatches)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* put_SuppressSemanticMatches)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        boolean value);
    HRESULT (STDMETHODCALLTYPE* get_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* put_Language)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        HSTRING value);
    HRESULT (STDMETHODCALLTYPE* get_MatchScope)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope* value);
    HRESULT (STDMETHODCALLTYPE* put_MatchScope)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CQueryMatchScope value);
    HRESULT (STDMETHODCALLTYPE* get_TextMatchType)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CTextLexicalMatchType* value);
    HRESULT (STDMETHODCALLTYPE* put_TextMatchType)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions* This,
        enum __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CTextLexicalMatchType value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptionsVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptionsVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_get_SuppressSemanticMatches(This, value) \
    ((This)->lpVtbl->get_SuppressSemanticMatches(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_put_SuppressSemanticMatches(This, value) \
    ((This)->lpVtbl->put_SuppressSemanticMatches(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_get_Language(This, value) \
    ((This)->lpVtbl->get_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_put_Language(This, value) \
    ((This)->lpVtbl->put_Language(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_get_MatchScope(This, value) \
    ((This)->lpVtbl->get_MatchScope(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_put_MatchScope(This, value) \
    ((This)->lpVtbl->put_MatchScope(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_get_TextMatchType(This, value) \
    ((This)->lpVtbl->get_TextMatchType(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_put_TextMatchType(This, value) \
    ((This)->lpVtbl->put_TextMatchType(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Interface Microsoft.Windows.Search.AppContentIndex.ITextQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Interface is a part of the implementation of type Microsoft.Windows.Search.AppContentIndex.TextQuerySessionResult
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#if !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_INTERFACE_DEFINED__)
#define ____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_INTERFACE_DEFINED__
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_Microsoft_Windows_Search_AppContentIndex_ITextQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.ITextQuerySessionResult";
typedef struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResultVtbl
{
    BEGIN_INTERFACE

    HRESULT (STDMETHODCALLTYPE* QueryInterface)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        REFIID riid,
        void** ppvObject);
    ULONG (STDMETHODCALLTYPE* AddRef)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This);
    ULONG (STDMETHODCALLTYPE* Release)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This);
    HRESULT (STDMETHODCALLTYPE* GetIids)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        ULONG* iidCount,
        IID** iids);
    HRESULT (STDMETHODCALLTYPE* GetRuntimeClassName)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        HSTRING* className);
    HRESULT (STDMETHODCALLTYPE* GetTrustLevel)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        TrustLevel* trustLevel);
    HRESULT (STDMETHODCALLTYPE* get_IsValid)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        boolean* value);
    HRESULT (STDMETHODCALLTYPE* get_QueryPhrase)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        HSTRING* value);
    HRESULT (STDMETHODCALLTYPE* get_QueryOptions)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQueryOptions** value);
    HRESULT (STDMETHODCALLTYPE* get_Matches)(__x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult* This,
        __FIVectorView_1_Microsoft__CWindows__CSearch__CAppContentIndex__CTextQueryMatch** value);

    END_INTERFACE
} __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResultVtbl;

interface __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult
{
    CONST_VTBL struct __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResultVtbl* lpVtbl;
};

#ifdef COBJMACROS

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_QueryInterface(This, riid, ppvObject) \
    ((This)->lpVtbl->QueryInterface(This, riid, ppvObject))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_Release(This) \
    ((This)->lpVtbl->Release(This))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_GetIids(This, iidCount, iids) \
    ((This)->lpVtbl->GetIids(This, iidCount, iids))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_GetRuntimeClassName(This, className) \
    ((This)->lpVtbl->GetRuntimeClassName(This, className))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_GetTrustLevel(This, trustLevel) \
    ((This)->lpVtbl->GetTrustLevel(This, trustLevel))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_get_IsValid(This, value) \
    ((This)->lpVtbl->get_IsValid(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_get_QueryPhrase(This, value) \
    ((This)->lpVtbl->get_QueryPhrase(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_get_QueryOptions(This, value) \
    ((This)->lpVtbl->get_QueryOptions(This, value))

#define __x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_get_Matches(This, value) \
    ((This)->lpVtbl->get_Matches(This, value))

#endif /* COBJMACROS */

EXTERN_C const IID IID___x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult;
#endif /* !defined(____x_ABI_CMicrosoft_CWindows_CSearch_CAppContentIndex_CITextQuerySessionResult_INTERFACE_DEFINED__) */
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppContentIndexListener
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppContentIndexListener ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexListener_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexListener_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppContentIndexListener[] = L"Microsoft.Windows.Search.AppContentIndex.AppContentIndexListener";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppContentIndexer
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppContentIndexerStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppContentIndexer ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexer_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppContentIndexer_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppContentIndexer[] = L"Microsoft.Windows.Search.AppContentIndex.AppContentIndexer";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegionStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexContentRegion ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexContentRegion_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexContentRegion_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexContentRegion[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexContentRegion";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuery ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuery_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuery_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuery[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuery";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySessionStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexImageQuerySession ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuerySession_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuerySession_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexImageQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexImageQuerySession";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuery
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuery ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuery_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuery_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuery[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuery";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySessionStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppIndexTextQuerySession ** Default Interface **
 *    Windows.Foundation.IClosable
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuerySession_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuerySession_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppIndexTextQuerySession[] = L"Microsoft.Windows.Search.AppContentIndex.AppIndexTextQuerySession";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedImageQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedImageQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedImageQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedImageQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass contains static methods.
 *   Static Methods exist on the Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContentStatics interface starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedIndexableAppContent ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedIndexableAppContent_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedIndexableAppContent_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedIndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedIndexableAppContent";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedOcrTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedOcrTextQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedOcrTextQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedOcrTextQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedOcrTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedOcrTextQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.AppManagedTextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IAppManagedTextQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedTextQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_AppManagedTextQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_AppManagedTextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.AppManagedTextQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentItemReader
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentItemReader ** Default Interface **
 *    Windows.Foundation.Collections.IIterable`1<String>
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemReader_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemReader_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentItemReader[] = L"Microsoft.Windows.Search.AppContentIndex.ContentItemReader";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentItemStatusResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemStatusResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentItemStatusResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentItemStatusResult[] = L"Microsoft.Windows.Search.AppContentIndex.ContentItemStatusResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentRegionImageOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentRegionImageOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionImageOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionImageOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentRegionImageOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ContentRegionImageOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ContentRegionTextOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IContentRegionTextOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionTextOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ContentRegionTextOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ContentRegionTextOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ContentRegionTextOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.DeleteIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IDeleteIndexResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_DeleteIndexResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_DeleteIndexResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_DeleteIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.DeleteIndexResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexOptions[] = L"Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IGetOrCreateIndexResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_GetOrCreateIndexResult[] = L"Microsoft.Windows.Search.AppContentIndex.GetOrCreateIndexResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IImageQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ImageQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.ImageQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ImageQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IImageQueryOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQueryOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ImageQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.ImageQueryOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.ImageQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IImageQuerySessionResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQuerySessionResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_ImageQuerySessionResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_ImageQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.ImageQuerySessionResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexCapabilities
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexCapabilities ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilities_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilities_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexCapabilities[] = L"Microsoft.Windows.Search.AppContentIndex.IndexCapabilities";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexCapabilitiesOfCurrentSystem
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexCapabilitiesOfCurrentSystem ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilitiesOfCurrentSystem_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilitiesOfCurrentSystem_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexCapabilitiesOfCurrentSystem[] = L"Microsoft.Windows.Search.AppContentIndex.IndexCapabilitiesOfCurrentSystem";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexCapabilityState
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexCapabilityState ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilityState_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexCapabilityState_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexCapabilityState[] = L"Microsoft.Windows.Search.AppContentIndex.IndexCapabilityState";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexStatistics
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexStatistics ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexStatistics_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexStatistics_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexStatistics[] = L"Microsoft.Windows.Search.AppContentIndex.IndexStatistics";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.IndexableAppContent
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.IIndexableAppContent ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexableAppContent_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_IndexableAppContent_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_IndexableAppContent[] = L"Microsoft.Windows.Search.AppContentIndex.IndexableAppContent";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.TextQueryMatch
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.ITextQueryMatch ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryMatch_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryMatch_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_TextQueryMatch[] = L"Microsoft.Windows.Search.AppContentIndex.TextQueryMatch";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.TextQueryOptions
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * RuntimeClass can be activated.
 *   Type can be activated via RoActivateInstance starting with version 1.0 of the Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract API contract
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.ITextQueryOptions ** Default Interface **
 *
 * Class Threading Model:  Both Single and Multi Threaded Apartment
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryOptions_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQueryOptions_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_TextQueryOptions[] = L"Microsoft.Windows.Search.AppContentIndex.TextQueryOptions";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

/*
 *
 * Class Microsoft.Windows.Search.AppContentIndex.TextQuerySessionResult
 *
 * Introduced to Microsoft.Windows.Search.AppContentIndex.AppContentIndexContract in version 1.0
 *
 * Class implements the following interfaces:
 *    Microsoft.Windows.Search.AppContentIndex.ITextQuerySessionResult ** Default Interface **
 *
 * Class Marshaling Behavior:  Agile - Class is agile
 *
 */
#if MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000
#ifndef RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQuerySessionResult_DEFINED
#define RUNTIMECLASS_Microsoft_Windows_Search_AppContentIndex_TextQuerySessionResult_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_Microsoft_Windows_Search_AppContentIndex_TextQuerySessionResult[] = L"Microsoft.Windows.Search.AppContentIndex.TextQuerySessionResult";
#endif
#endif // MICROSOFT_WINDOWS_SEARCH_APPCONTENTINDEX_APPCONTENTINDEXCONTRACT_VERSION >= 0x10000

#endif // defined(__cplusplus)
#pragma pop_macro("MIDL_CONST_ID")
#endif // __microsoft2Ewindows2Esearch2Eappcontentindex_p_h__

#endif // __microsoft2Ewindows2Esearch2Eappcontentindex_h__
